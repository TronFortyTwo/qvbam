#include <QObject>

#ifndef QGAMESLOT
#define QGAMESLOT
class QGameSlot : public QObject{
    Q_OBJECT
    Q_PROPERTY(bool isEmpty READ isEmpty WRITE setIsEmpty NOTIFY isEmptyChanged)
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)
public:
    bool isEmpty();
    void setIsEmpty(bool);
    QString time();
    void setTime(QString);
signals:
    void isEmptyChanged();
    void timeChanged();
private:
    bool m_isEmpty;
    QString m_time;
};
#endif
