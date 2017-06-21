#include "CustomQQuickView.h"

extern Window * w;
bool CustomQQuickView::event(QEvent *e) {
    if (e->type() == QEvent::Close) {
        qDebug() << "Close event";
        delete w;
    }
    return QQuickView::event(e);
}
