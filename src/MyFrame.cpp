#include "MyFrame.h"

MyFrame::MyFrame() :
		QWidget() {

	/* Initialize widgets */
	this->siftRadioButton = new QRadioButton("SIFT");
	this->siftRadioButton->setChecked(true);
	this->surfRadioButton = new QRadioButton("SURF");
	this->imgLineEdit1 = new QLineEdit();
	this->imgLineEdit1->setFixedWidth(400);
	this->imgLineEdit2 = new QLineEdit();
	this->imgLineEdit2->setFixedWidth(400);
	this->browseImgButton1 = new QPushButton("Browse...");
	this->browseImgButton2 = new QPushButton("Browse...");
	this->featureBasedMatchingButton = new QPushButton(
			"Perform feature-based matching!");
	this->matchesLabel = new QLabel();

	/* Position widgets */
	QGroupBox *featureExtractionGroupBox = new QGroupBox;
	QVBoxLayout *featureExtractionLayout = new QVBoxLayout;
	featureExtractionLayout->addWidget(siftRadioButton);
	featureExtractionLayout->addWidget(surfRadioButton);
	featureExtractionGroupBox->setLayout(featureExtractionLayout);
	QGroupBox *imageSamplesGroupBox = new QGroupBox("Image samples");
	QGridLayout *imageSamplesGridLayout = new QGridLayout;
	imageSamplesGridLayout->addWidget(imgLineEdit1, 0, 0);
	imageSamplesGridLayout->addWidget(browseImgButton1, 0, 1);
	imageSamplesGridLayout->addWidget(imgLineEdit2, 1, 0);
	imageSamplesGridLayout->addWidget(browseImgButton2, 1, 1);
	imageSamplesGroupBox->setLayout(imageSamplesGridLayout);
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(imageSamplesGroupBox, 0, 0);
	mainLayout->addWidget(featureExtractionGroupBox, 0, 1);
	mainLayout->addWidget(featureBasedMatchingButton, 1, 0, 1, 3);
	mainLayout->addWidget(matchesLabel, 2, 0, 1, 3);
	this->setLayout(mainLayout);

	/* Connect signals to custom slots */
	QObject::connect(browseImgButton1, SIGNAL(clicked()), this,
			SLOT(updateImgLineEdit1()));
	QObject::connect(browseImgButton2, SIGNAL(clicked()), this,
			SLOT(updateImgLineEdit2()));
	QObject::connect(featureBasedMatchingButton, SIGNAL(clicked()), this,
			SLOT(featureBasedMatching()));

}

void MyFrame::updateImgLineEdit1() {
	QString path = QFileDialog::getOpenFileName(this, "Choose sample image",
			"./samples", "Images (*.png *.gif *.jpg *.jpeg)");
	this->imgLineEdit1->setText(path);
}

void MyFrame::updateImgLineEdit2() {
	QString path = QFileDialog::getOpenFileName(this, "Ouvrir un fichier",
			"./samples", "Images (*.png *.gif *.jpg *.jpeg)");
	this->imgLineEdit2->setText(path);
}

void MyFrame::featureBasedMatching() {

	/* Load sample images */
	cv::Mat image1 = cv::imread(this->imgLineEdit1->text().toStdString());
	cv::Mat image2 = cv::imread(this->imgLineEdit2->text().toStdString());
	if (!image1.data || !image2.data) {
		QMessageBox::critical(this, "Error",
				"Please select valid image sample paths");
	}

	/* Perform feature-based matching */
	else {
		std::vector<cv::KeyPoint> keyPoints1, keyPoints2;
		cv::Mat descriptors1, descriptors2;

		/* Extract features using SIFT of SURF */
		if (this->siftRadioButton->isChecked()) {
			keyPoints1 = FeatureBasedMatcher::getSiftFeatures(image1);
			descriptors1 = FeatureBasedMatcher::getSiftFeaturesDescriptions(
					image1, keyPoints1);
			keyPoints2 = FeatureBasedMatcher::getSiftFeatures(image2);
			descriptors2 = FeatureBasedMatcher::getSiftFeaturesDescriptions(
					image2, keyPoints2);
		} else if (this->surfRadioButton->isChecked()) {
			keyPoints1 = FeatureBasedMatcher::getSurfFeatures(image1, 400);
			descriptors1 = FeatureBasedMatcher::getSurfFeaturesDescriptions(
					image1, keyPoints1);
			keyPoints2 = FeatureBasedMatcher::getSurfFeatures(image2);
			descriptors2 = FeatureBasedMatcher::getSurfFeaturesDescriptions(
					image2, keyPoints2);
		}

		/* Perform Flann matching */
		cv::Mat matches = FeatureBasedMatcher::getFlannMatches(image1,
				keyPoints1, descriptors1, image2, keyPoints2, descriptors2);

		/* Display matches on QLabel */
		IplImage imageMatchesIpl = matches;
		IplImage *ipl = &imageMatchesIpl;
		QImage image(ipl->width, ipl->height, QImage::Format_RGB32);
		uchar* pBits = image.bits();
		int nBytesPerLine = image.bytesPerLine();
		for (int n = 0; n < ipl->height; n++) {
			for (int m = 0; m < ipl->width; m++) {
				CvScalar s = cvGet2D(ipl, n, m);
				QRgb value = qRgb((uchar) s.val[2], (uchar) s.val[1],
						(uchar) s.val[0]);
				uchar* scanLine = pBits + n * nBytesPerLine;
				((uint*) scanLine)[m] = value;
			}
		}
		this->matchesLabel->setPixmap(QPixmap::fromImage(image));
		this->adjustSize();
	}

}
