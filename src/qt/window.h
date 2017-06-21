#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QAbstractEventDispatcher>
#include <QString>
#include <QDir>
#include <QDateTime>
#include <QFileInfo>
#include <QQmlListProperty>

#include "../gba/Sound.h"
#include "../Util.h"
#include "../gba/GBA.h"
#include "../gb/gbGlobals.h"
#include "../sdl/inputSDL.h"
#include <SDL_keysym.h>
#include <pwd.h>
#include "Config.h"
#include "QGameSlot.h"

#ifndef WINDOW
#define WINDOW
class Window : public QObject {
    Q_OBJECT
    Q_PROPERTY(QObject * config READ config)
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(int frameSkip READ frameSkip NOTIFY frameSkipChanged)
    Q_PROPERTY(bool paused READ paused WRITE setPaused NOTIFY pausedChanged)
    Q_PROPERTY(QQmlListProperty<QGameSlot> gameSlot READ gameSlot NOTIFY gameSlotChanged)
    struct SGameSlot
    {
      bool        m_bEmpty;
      std::string m_sFile;
      time_t      m_uiTime;
    };

public:

    int m_iScreenWidth;
    int m_iScreenHeight;

    enum ECartridge
    {
      CartridgeNone,
      CartridgeGB,
      CartridgeGBA
    };

    enum EColorFormat
    {
      ColorFormatRGB,
      ColorFormatBGR
    };

    Window();
    ~Window();
    bool bLoadROM(const std::string & _rsFile);
    void vDrawScreen();

    Q_INVOKABLE bool bLoadRomInQML(QString fileName);
    Q_INVOKABLE bool on_key_press_event(Qt::Key key);
    Q_INVOKABLE bool on_key_release_event(Qt::Key key);
    void vComputeFrameskip(int);
    Q_INVOKABLE void vOnFileClose();
    Q_INVOKABLE void vOnSaveGame(int _iSlot);
    Q_INVOKABLE void vOnLoadGame(int _iSlot);

    //qml get set function
    QObject * config();
    int speed();
    void setspeed(int);
    bool paused();
    void setPaused(bool);
    int frameSkip();
    QQmlListProperty<QGameSlot> gameSlot();


public slots:
    bool bOnEmuIdle();
    void vApplyConfigMute();

signals:
    void sDrawScreen();

    //qmlsignals
    void speedChanged();
    void pausedChanged();
    void frameSkipChanged();
    void gameSlotChanged();

private:
    int m_iFrameCount;

    const int m_iGBAScreenWidth;
    const int m_iGBAScreenHeight;

    std::string     m_sUserDataDir;

    std::string     m_sRomFile;
    ECartridge      m_eCartridge;
    EmulatedSystem  m_stEmulator;
    bool            m_bWasEmulating;
    bool            m_bAutoFrameskip;
    SGameSlot       m_astGameSlot[10];

    QTimer idleTimer;
    Config * m_config;
    int m_speed;
    bool m_idleTimerRunning;
    bool m_bPaused;
    QList<QGameSlot *> m_qGameSlotList;

    void vStopEmu();
    void vApplyPerGameConfig();
    void vLoadBattery();
    void vUpdateScreen();
    void vStartEmu();
    void vInitSystem();
    void vInitSDL();
    void vSDLPollEvents();
    void vApplyConfigScreenArea();
    void vInitColors(EColorFormat _eColorFormat);
    void vSaveBattery();
    void vApplyConfigFrameskip();
    void vOnFilePauseToggled();
    void vUpdateGameSlots();
    void vApplyConfigSoundSampleRate();

};
#endif
