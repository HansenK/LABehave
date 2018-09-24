#-------------------------------------------------
#
# Project created by QtCreator 2018-08-06T23:28:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LaBehave
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    background.cpp

INCLUDEPATH += C:/TCC/OpenCV/install/include

LIBS += -LC:\\TCC\\OpenCV\\bin \
    libopencv_core400d \
    libopencv_calib3d400d \
    libopencv_highgui400d \
    libopencv_imgcodecs400d \
    libopencv_imgproc400d \
    libopencv_ml400d \
    libopencv_objdetect400d \
    libopencv_shape400d \
    libopencv_stitching400d \
    libopencv_superres400d \
    libopencv_video400d \
    libopencv_videoio400d \

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    style.qss

RESOURCES += \
    resources.qrc
