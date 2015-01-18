#-------------------------------------------------
#
# Project created by QtCreator 2014-09-19T18:19:24
#
#-------------------------------------------------


    QMAKE_CXXFLAGS = -std=c++11


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_ResourceFileManager
TEMPLATE = app

gcc {
    DESTDIR = ../__build-output/gcc
}
clang {
    DESTDIR = ../__build-output/clang
}
msvc {
    DESTDIR = ../__build-output/msvc
}


SOURCES += \
    examples/src/main.cpp \
    examples/src/forms/mainwindow.cpp \
    src/resourcefilemanager.cpp \
    src/zfile/miniz.c \
    src/zfile/zfile.c

HEADERS  += \
    examples/src/forms/mainwindow.h \
    src/resourcefilemanager.h \
    src/zfile/zfile.h

FORMS    += \
    examples/src/forms/mainwindow.ui

RESOURCES += \
    examples/res/resources.qrc


# Build deployment
CONFIG += copy_dir_files # Enables the install rule to also copy directories, not just files
CONFIG += no_check_exist

assets.path = $$DESTDIR/../assets
assets.files += $$files(examples/assets/*.*)
INSTALLS += assets

assets_archives.path = $$DESTDIR/../assets/archives
assets_archives.files += $$files(examples/assets/archives/*.*)
INSTALLS += assets_archives

assets_images.path = $$DESTDIR/../assets/images
assets_images.files += $$files(examples/assets/images/*.*)
INSTALLS += assets_images
