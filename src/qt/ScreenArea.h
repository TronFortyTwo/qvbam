#include <QQuickPaintedItem>
#include <QDebug>
#include <QPainter>
#include "../common/Types.h"
#include "window.h"
class ScreenArea : public QQuickPaintedItem {
    Q_OBJECT
public:
    ScreenArea();
    ~ScreenArea();
    void paint(QPainter *painter);

private:
    QImage * m_image;
    QRectF * m_sourceTarget;
};
