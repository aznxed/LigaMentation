#include <QtWidgets/QApplication>
#include <QQmlApplicationEngine>
#include <QtSerialPort>
#include <QtQuick/QQuickView>
#include <QFile>
#include <QStringList>
#include <QtQml/QQmlContext>
#include "datasource.h"

QT_USE_NAMESPACE

int main(int argc, char *argv[]){

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQuickView viewer;


    const auto infos = QSerialPortInfo::availablePorts();
    QSerialPort serial;
    serial.setPortName("COM7");
    serial.setBaudRate(19200);
    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug("Can't connect");
    }

/*
    if (serial.waitForReadyRead(10)) {
        qDebug() << "Hello";
        QByteArray responseData = serial.readAll();
        while (serial.waitForReadyRead(10)){
            responseData += serial.readAll();
        }
        QString response(responseData);
    }*/


    QFile file(":/forceData.csv");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }

    QStringList wordList;
    while (!file.atEnd()) {
        wordList.append(file.readLine());
        break;
    }

    qDebug() << wordList;

    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);
    DataSource dataSource(&viewer);


    viewer.setTitle(QStringLiteral("LigaMentation"));
    viewer.rootContext()->setContextProperty("dataSource", &dataSource);
    viewer.setSource(QUrl("qrc:/main.qml"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.show();


    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();

    //return 0;

}
