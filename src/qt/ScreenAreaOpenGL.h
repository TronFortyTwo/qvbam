#ifndef SQUIRCLE_H
#define SQUIRCLE_H

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QSGSimpleRectNode>
#include <QSGSimpleTextureNode>
class Squircle : public QQuickItem
{
    Q_OBJECT

public:
    Squircle();
    virtual QSGNode * updatePaintNode(QSGNode *node, UpdatePaintNodeData *);

};

#endif // SQUIRCLE_H
