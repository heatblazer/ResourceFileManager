#-------------------------------------------------
#
# Project created by QtCreator 2014-09-19T18:19:24
#
#-------------------------------------------------
QMAKE_CXXFLAGS = -std=c++11
gcc {
    QMAKE_CXXFLAGS = -std=c++11
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_ResourceFileManager
TEMPLATE = app

DESTDIR = ../__build-output


SOURCES += src/main.cpp\
    src/forms/mainwindow.cpp \
    src/utilities/resourcefilemanager.cpp \
    src/utilities/miniz.c \
    src/utilities/Archiver.c

HEADERS  += src/forms/mainwindow.h \
    src/utilities/resourcefilemanager.h \
    src/utilities/Archiver.h

FORMS    += src/forms/mainwindow.ui

RESOURCES += \
    res/resources.qrc


# Build deployment
CONFIG += copy_dir_files # Enables the install rule to also copy directories, not just files
CONFIG += no_check_exist

assets.path = $$DESTDIR/assets
assets.files += $$files(assets/*.*)
INSTALLS += assets

assets_archives.path = $$DESTDIR/assets/archives
assets_archives.files += $$files(assets/archives/*.*)
INSTALLS += assets_archives

assets_images.path = $$DESTDIR/assets/images
assets_images.files += $$files(assets/images/*.*)
INSTALLS += assets_images
