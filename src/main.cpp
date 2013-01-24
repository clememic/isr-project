#include <QApplication>
#include "MyFrame.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	MyFrame frame;
	frame.show();
	return app.exec();
}

