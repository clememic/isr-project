#include <QApplication>
#include <QGroupBox>
#include <QRadioButton>

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QWidget window;
	QGroupBox *groupbox = new QGroupBox("Feature extraction method", &window);
	QRadioButton *sift = new QRadioButton("SIFT");
	QRadioButton *surf = new QRadioButton("SURF");
	return app.exec();
}
