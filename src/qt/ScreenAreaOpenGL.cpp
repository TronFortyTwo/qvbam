#include "ScreenAreaOpenGL.h"
#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>
#include "../common/Types.h"
#include "CustomQQuickView.h"
#define NOISE_SIZE 160
extern CustomQQuickView * view;
extern Uint8 * pix;
extern Window * w;
Squircle::Squircle()
{
    setFlag(ItemHasContents, true);
}

QSGNode * Squircle::updatePaintNode(QSGNode * oldnode, UpdatePaintNodeData *){
    QSGSimpleTextureNode *node= static_cast<QSGSimpleTextureNode *>(oldnode);
    if(!node) {
        node = new QSGSimpleTextureNode();
        node->setRect(boundingRect());
    }
    QImage image(pix, 241, NOISE_SIZE, QImage::Format_RGB32);
    QSGTexture * t = view->createTextureFromImage(image);
    node->setTexture(t);
    return node;
}
