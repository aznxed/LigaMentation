/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "datasource.h"
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QtMath>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QSerialPort>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

DataSource::DataSource(QQuickView *appViewer, QObject *parent) :
    QObject(parent),
    m_appViewer(appViewer),
    m_index(-1)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();

    generateData(0, 1, 4000);
}

void DataSource::update(QAbstractSeries *series)
{
    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        m_index++;
        if (m_index > m_data.count() - 1)
            m_index = 0;

        QVector<QPointF> points = m_data.at(m_index);
        // Use replace instead of clear + append, it's optimized for performance
        xySeries->replace(points);
    }
}

void DataSource::generateData(int type, int rowCount, int colCount)
{

    /*
    QSerialPort serial;
    serial.setPortName("COM8");
    serial.setBaudRate(115200);
    qDebug("Attempting");
    if (serial.open(QIODevice::ReadWrite)) {

        qDebug("Connected");
        if (serial.waitForReadyRead(5000)){
            QByteArray responseData = serial.readAll();
            qDebug(responseData);
            qDebug("Hello");
            serial.close();
        }

    }*/

    // Remove previous data
    foreach (QVector<QPointF> row, m_data)
        row.clear();
    m_data.clear();

    int numSamples = 0;
    QFile file(":/Specimen_RawData_1.csv");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }

    QString line = file.readLine();
    QStringList packets = line.split('X');
    packets.pop_back();
    numSamples = packets.size();
    qDebug() << numSamples;
    //QStringList values = packets[0].split(' ');
    qDebug() << packets[0];
    qDebug() << packets[1];
    qDebug() << packets[2];
    //qDebug() << values[0];


    // Append the new data depending on the type
    for (int i(0); i < rowCount; i++) {
        QVector<QPointF> points;
        points.reserve(colCount);

        for (int j(0); j < colCount; j++) {
        //for (int j(0); j < colCount; j++) {
            //QString line = file.readLine();
            //QStringList packets = line.split(',');
            //numSamples = packets.size();

            qreal x(0);
            qreal y(0);
            switch (type) {
            case 0:
                // data with sin + random component
                //x = j;
                //y = qSin(3.14159265358979 / 50 * j) + 0.5 + (qreal) rand() / (qreal) RAND_MAX;
                x = packets[0].toDouble();
                y = packets[1].toDouble();// + (qreal) rand() / (qreal) RAND_MAX;
                //qDebug() << x;
                break;
            case 1:
                // linear data
                //x = j;
                //y = (qreal) i / 10;
                x = packets[0].toDouble();
                y = packets[2].toDouble();
                break;
            default:
                // unknown, do nothing
                break;
            }
            points.append(QPointF(x, y));
        }
        m_data.append(points);
    }
}
