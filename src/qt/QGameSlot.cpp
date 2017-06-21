#include "QGameSlot.h"

bool QGameSlot::isEmpty() {
    return m_isEmpty;
}

void QGameSlot::setIsEmpty(bool v) {
    m_isEmpty = v;
    emit isEmptyChanged();
}

QString QGameSlot::time() {
    return m_time;
}

void QGameSlot::setTime(QString t) {
    m_time = t;
    emit timeChanged();
}
