#include "system.h"

int  systemRedShift;
int  systemGreenShift;
int  systemBlueShift;
int  systemColorDepth;
int  systemVerbose;
int  systemSaveUpdateCounter;
int  systemFrameSkip;
u32  systemColorMap32[0x10000];
u16  systemColorMap16[0x10000];
u16  systemGbPalette[24];


int  emulating;
int  RGB_LOW_BITS_MASK;
extern Window * w;
Window * GUI() {
    return w;
}

void systemMessage(int _iId, const char * _csFormat, ...)
{
    qDebug() << "TODO:: systemMessage" << _csFormat;
    //  va_list args;
    //  va_start(args, _csFormat);

    //  GUI()->vPopupErrorV(_(_csFormat), args);

    //  va_end(args);
}

void debuggerBreakOnWrite(u32 address, u32 oldvalue, u32 value, int size, int t)
{
}

void log(const char *defaultMsg, ...)
{
    qDebug() << "TODO:: log";

    //  static FILE *out = NULL;

    //  if(out == NULL) {
    //    out = fopen("trace.log","w");
    //  }

    //  va_list valist;

    //  va_start(valist, defaultMsg);
    //  vfprintf(out, defaultMsg, valist);
    //  va_end(valist);
}

int systemGetSensorX()
{
    return 0;
}

int systemGetSensorY()
{
    return 0;
}

void debuggerOutput(const char *, u32)
{
}

void debuggerSignal(int, int)
{
}

void (*dbgOutput)(const char *, u32) = debuggerOutput;
void (*dbgSignal)(int, int) = debuggerSignal;

bool systemCanChangeSoundQuality()
{
    return true;
}

SoundDriver * systemSoundInit()
{
    soundShutdown();

    return new SoundSDL();
    // I tried to use QAudioOutput. It still has problem in confinement. There is a pluseaudio server that might solve the problem. Waiting for it to publish.
    // Anyway, currently just not have sound in this version.
//    return new SoundQt();
}

void systemOnSoundShutdown()
{
}

//int missingSound = 0;
//char * emptySound = 0;
//int emptySoundLength = 0;
//extern SoundDriver * soundDriver;
void systemOnWriteDataToSoundBuffer(const u16 * finalWave, int length)
{
//    if (emptySoundLength != 0 && emptySoundLength != length) {
//        delete emptySound;
//        emptySound = 0;
//    }
//    if (emptySound == 0) {
//        emptySound = new char[length];
//        emptySoundLength = length;
//        memset(emptySound, 0, emptySoundLength);
//    }
//    while (missingSound > 0) {
//        soundDriver->write((u16 *)emptySound, emptySoundLength);
//        missingSound --;
//    }
}

bool systemReadJoypads()
{
    return true;
}

u32 systemReadJoypad(int joy)
{
    return inputReadJoypad(joy);
}

u32 systemGetClock()
{
    return QTime::currentTime().msecsSinceStartOfDay();
}

bool systemPauseOnFrame()
{
    return false;
}

void systemFrame()
{
}

void system10Frames(int _iRate)
{
    GUI()->vComputeFrameskip(_iRate);
//    missingSound += systemFrameSkip;
}

void systemShowSpeed(int _iSpeed)
{
    GUI()->setspeed(_iSpeed);
}

void systemUpdateMotionSensor()
{
}

void systemScreenCapture(int _iNum)
{
    qDebug() << "TODO::systemScreenCapture";
    //  GUI()->vCaptureScreen(_iNum);
}

void systemDrawScreen()
{
    GUI()->vDrawScreen();
}

void systemGbBorderOn()
{
}


void systemScreenMessage(const char *msg) {
    qDebug() << "TODO:: systemScreenMessage " << msg;
}
