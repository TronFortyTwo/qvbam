#include "ScreenArea.h"

extern u8 *pix;
extern Window * w;

ScreenArea::ScreenArea() {
    m_image = new QImage(pix, 241, 160, QImage::Format_RGB32);
    m_sourceTarget = new QRectF (0, 0, 241, 160);
}

ScreenArea::~ScreenArea() {
    delete m_image;
    delete m_sourceTarget;
}

void ScreenArea::paint(QPainter *painter) {
    QRectF target(0, 0, this->width(),  this->height());
    painter->drawImage(target, *m_image, *m_sourceTarget);
}
