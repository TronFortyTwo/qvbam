#ifndef QVBAM_QT_CONFIG
#define QVBAM_QT_CONFIG

#include <QObject>

class Config : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool mute READ mute WRITE setMute NOTIFY muteChanged)
public:
    bool mute();
    void setMute(bool);
signals:
    void muteChanged();
private:
    bool m_mute;
};
#endif
