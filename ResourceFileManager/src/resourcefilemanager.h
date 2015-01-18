#ifndef RESOURCEFILEMANAGER_H
#define RESOURCEFILEMANAGER_H

#include <QtCore/QByteArray>
#include <QtCore/QObject>
#include <QtCore/QString>


class ResourceFileManager : public QObject
{
    Q_OBJECT
public:
    explicit ResourceFileManager(QString resourceFolderPath, QObject* parent = 0);

public:
    QByteArray loadFrom(const QString& resourceFileName, const QString& fileName);

private:
    QByteArray loadFromFolder(const QString& folderPath, const QString& fileName);
QByteArray loadFromResourceFile(const QString& resourceFilePath, const QString& fileName);

private:
    QString _resourceFolderPath;
};

#endif // RESOURCEFILEMANAGER_H
