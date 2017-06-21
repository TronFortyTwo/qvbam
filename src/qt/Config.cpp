#include "Config.h"
bool Config::mute() {
    return m_mute;
}
void Config::setMute(bool v) {
    m_mute = v;
    emit muteChanged();
}
