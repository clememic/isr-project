#ifndef MYFRAME_H_
#define MYFRAME_H_

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QFrame>
#include <QGroupBox>
#include <QPixmap>

#include "opencv2/highgui/highgui.hpp"

#include "FeatureBasedMatcher.h"

class MyFrame: public QWidget {
Q_OBJECT

public:
	MyFrame();

private:
	QRadioButton *siftRadioButton;
	QRadioButton *surfRadioButton;
	QLineEdit *imgLineEdit1;
	QLineEdit *imgLineEdit2;
	QPushButton *browseImgButton1;
	QPushButton *browseImgButton2;
	QPushButton *featureBasedMatchingButton;
	QLabel *matchesLabel;

public slots:
	void updateImgLineEdit1();
	void updateImgLineEdit2();
	void featureBasedMatching();
};

#endif /* MYFRAME_H_ */
