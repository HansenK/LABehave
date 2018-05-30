#-------------------------------------------------
#
# Project created by QtCreator 2018-04-30T13:53:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCC
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
    tools.cpp


INCLUDEPATH += C:/TCC/OpenCV/install/include

LIBS += -LC:\\TCC\\OpenCV\\bin \
    libopencv_core341d \
    libopencv_calib3d341d \
    libopencv_features2d341d \
    libopencv_flann341d \
    libopencv_highgui341d \
    libopencv_imgcodecs341d \
    libopencv_imgproc341d \
    libopencv_ml341d \
    libopencv_objdetect341d \
    libopencv_photo341d \
    libopencv_shape341d \
    libopencv_stitching341d \
    libopencv_superres341d \
    libopencv_video341d \
    libopencv_videoio341d \

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui
