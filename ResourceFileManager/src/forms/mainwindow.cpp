#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QDebug>

#include "../utilities/resourcefilemanager.h"

#define ASSETS_FOLDER "assets"
#define RESOURCE_FILEPATH "resourcefile"
#define IMAGE_FILE "knight.png"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ResourceFileManager resourceFileManager(ASSETS_FOLDER);

    /* TODO - add some string to pass as argument */
    QByteArray buffer = resourceFileManager.loadFrom("archives/Ar1.zip", "knight.png");
      // QByteArray possesses the following operator
      //     QByteArray operator==(const char *a1, const QByteArray &a2)
      // thus the following code is valid as it compares nullptr (const char*)
      // to a QByteArray argument:
      //     if (nullptr == buffer) {
      // It is still better to just use buffer.isEmpty()

    if (buffer.isEmpty()) {
        qDebug() << IMAGE_FILE << "not found";
    }
    else {
        QPixmap pixmap;
        pixmap.loadFromData(buffer);

        quint32 labelWidth = ui->label->width();
        quint32 labelHeight = ui->label->height();
        qDebug() << "labelWidth:" << labelWidth << ", labelHeight:" << labelHeight;

        quint32 pixmapWidth = pixmap.width();
        quint32 pixmapHeight = pixmap.height();
        qDebug() << "pixmapWidth:" << pixmapWidth << ", pixmapHeight:" << pixmapHeight;

        quint32 newWidth = 0;
        quint32 newHeight = 0;

        if (labelWidth < pixmapWidth) {
            qreal ratio = static_cast<qreal>(labelWidth) / pixmapWidth;
            qDebug() << "Width ratio:" << ratio;

            newWidth = labelWidth;
            newHeight = pixmapHeight * ratio;
        }
        else {
            newWidth = pixmapWidth;
            newHeight = pixmapHeight;
        }

        if (labelHeight < newHeight) {
            qreal ratio = static_cast<qreal>(labelHeight) / newHeight;
            qDebug() << "Height ratio:" << ratio;

            newWidth = newWidth * ratio;
            newHeight = labelHeight;
        }

        qDebug() << "newWidth:" << newWidth << ", newHeight:" << newHeight;

        pixmap = pixmap.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(pixmap);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
