#include "../common/SoundDriver.h"
#include <QDebug>
#include <QBuffer>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QThread>
#include <QMutex>
#include <QSemaphore>
#include "../common/RingBuffer.h"
class SoundBuffer : public QIODevice {
public:
    SoundBuffer(int samples);
    virtual qint64 readData(char*, qint64);
    virtual qint64 writeData(const char*, qint64);
private:
    const float _delay = 0.11f;

    RingBuffer<u16> _rbuf;
};

class SoundQt : public QObject, public SoundDriver {
    Q_OBJECT
public:
    virtual bool init(long sampleRate);
    virtual void pause();
    virtual void reset();
    virtual void resume();
    virtual void write(u16 * finalWave, int length);

//public slots:
//    void  handleStateChanged(QAudio::State);
private:
    QAudioOutput * audio;
    SoundBuffer * buffer;
};
