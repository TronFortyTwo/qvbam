#include <QObject>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QDebug>
class FilesModel : public QObject{
    Q_OBJECT
    Q_PROPERTY(QStringList files READ files NOTIFY filesChanged)
public:
    QStringList files();
    Q_INVOKABLE void importFiles(QString fullPath);
    Q_INVOKABLE void removeFile(QString fileName);
signals:
    void filesChanged();
};
