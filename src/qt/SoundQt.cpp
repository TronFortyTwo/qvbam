#include "SoundQt.h"

extern int emulating;
extern bool speedup;
// Hold up to 100 ms of data in the ring buffer

SoundBuffer::SoundBuffer(int samples) {
    _rbuf.reset(samples * 2 * _delay);
}

qint64 SoundBuffer::readData(char *data, qint64 length) {
    u16 * stream = (u16 *)data;
    int readLength = std::min(static_cast<std::size_t>(length) / 2, _rbuf.used());
    _rbuf.read(stream, readLength);
    return readLength * 2;
}

qint64 SoundBuffer::writeData(const char* data, qint64 length) {
    u16 *finalWave = (u16 *)data;
    int writeLength = std::min(static_cast<std::size_t>(length) / 2, _rbuf.avail());
    _rbuf.write(finalWave, writeLength);
    return writeLength * 2;
}

bool SoundQt::init(long sampleRate) {
    buffer = new SoundBuffer(sampleRate);
    buffer->open(QBuffer::ReadWrite);

    QAudioFormat format;
    format.setSampleRate(sampleRate);
    format.setCodec("audio/pcm");
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return false;
    }
    audio = new QAudioOutput(format);
    audio->start(buffer);
    return true;
}

void SoundQt::pause() {
    audio->suspend();
}

void SoundQt::reset() {
}

void SoundQt::resume() {
    audio->resume();
}

void SoundQt::write(u16 * finalWave, int length) {
   buffer->write((char *)finalWave, length);
}
