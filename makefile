CC=g++
CFLAGS=-Wall
INCLUDES=-I/usr/include/opencv2 -I/usr/include/qt4 -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtCore
SOURCES=src/main.cpp src/FeatureBasedMatcher.cpp
EXECUTABLE=isr
LIBS=-lopencv_core -lopencv_highgui -lopencv_features2d -lopencv_flann -lQtGui -lQtCore

all:
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(EXECUTABLE) $(LIBS)