#include <QtQuick/QQuickView>
#include <QDebug>
#include "window.h"
class CustomQQuickView : public QQuickView {
public:
    bool event(QEvent * e);
};
