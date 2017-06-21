#include <QDebug>
#include <QObject>
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <csignal>
#include "ScreenArea.h"
#include "window.h"
#include "CustomQQuickView.h"
#include "ScreenAreaOpenGL.h"
#include "FilesModel.h"
#include "QGameSlot.h"
Window * w;
CustomQQuickView * view;

void sig_handler(int sig) {
        qDebug() << "SIGINT CAUGHT";
	w->vOnFileClose();
        exit(0);
}
int main(int argc, char ** argv) {
    signal(SIGINT, sig_handler);
    signal(SIGKILL, sig_handler);
    signal(SIGTERM, sig_handler);
    QGuiApplication a(argc, argv);
    view = new CustomQQuickView();

    w = new Window();
    FilesModel romsModel;
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->engine()->rootContext()->setContextProperty("romsModel", &romsModel);
    view->engine()->rootContext()->setContextProperty("iwindow", w);
    qmlRegisterType<ScreenArea>("QVBA", 0, 1, "ScreenArea");
    qmlRegisterUncreatableType<Window>("QVBA", 0, 1, "WINDOW", "hehe");
    qmlRegisterUncreatableType<QGameSlot>("QVBA", 0, 1, "QGameSlot", "hehe");


    view->setSource(QUrl::fromLocalFile("qml/main.qml"));
    view->show();
    return a.exec();
}
