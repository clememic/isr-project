######################################################################
# Automatically generated by qmake (2.01a) Wed Jan 23 23:52:58 2013
######################################################################

TEMPLATE = app
TARGET = FeatureBasedMatcher
DEPENDPATH += . src
INCLUDEPATH += . src
INCLUDEPATH += /usr/include/opencv2
LIBS += -lopencv_core -lopencv_highgui -lopencv_features2d -lopencv_flann

OBJECTS_DIR = obj
MOC_DIR = moc

# Input
HEADERS += src/FeatureBasedMatcher.h src/MyFrame.h
SOURCES += src/FeatureBasedMatcher.cpp src/main.cpp src/MyFrame.cpp
