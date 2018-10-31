#include <QDebug>
#include <QBuffer>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QThread>
#include <QMutex>
#include <QSemaphore>
#include "../common/SoundDriver.h"
#include "../common/Types.h"
#include "../common/ringbuffer.h"
#include "../gba/Sound.h"
#include "../common/SoundSDL.h"
#include "../sdl/inputSDL.h"

class SoundBuffer : public QIODevice {
public:
    SoundBuffer(int samples);
    virtual qint64 readData(char*, qint64);
    virtual qint64 writeData(const char*, qint64);
private:
    const float _delay = 0.11f;

    RingBuffer<Uint16> _rbuf;
};

class SoundQt : public QObject, public SoundDriver {
    Q_OBJECT
public:
    virtual bool init(long sampleRate);
    virtual void pause();
    virtual void reset();
    virtual void resume();
    virtual void write(Uint16 * finalWave, int length);

//public slots:
//    void  handleStateChanged(QAudio::State);
private:
    QAudioOutput * audio;
    SoundBuffer * buffer;
};
