import QtQuick 2.7
import QtCharts 2.1

Item {

    anchors.fill: parent


    Rectangle {
        id: banner
        anchors.top: parent.top
        width: parent.width
        height: 200

        Image {
            id: image
            y: 8
            height: 200
            anchors.horizontalCenterOffset: 0
            width:600
            source: "Images/LigaMentationLogo.png"
            anchors.centerIn: banner.center
            anchors.horizontalCenter: banner.horizontalCenter

        }
    }

    ChartView {
        id:view
        //anchors.fill: parent
        title: "Force vs. Displacement"
        //animationOptions: ChartView.SeriesAnimations
        animationOptions: ChartView.NoAnimation;
        theme: ChartView.ChartThemeBlueIcy
        antialiasing: true
        width: parent.width
        anchors.top: banner.bottom
        anchors.bottom: parent.bottom


        ValueAxis {
                id: xAxis
                min: 0
                max: 1024
                tickCount: 1
                labelFormat: "%.0f"
                labelsVisible: true
                titleText: "Angle"
        }

        ValueAxis {
                id: yAxis
                min: 0
                max: 4
                tickCount: 1
                labelFormat: "%.0f"
                labelsVisible: true
                titleText: "Force"

        }

        SplineSeries {
            //useOpenGL: true
            axisX: xAxis
            axisY: yAxis


        }

        Timer {
                id: refreshTimer
                interval: 1 / 60 * 1000 // 60 Hz
                running: true
                repeat: true
                onTriggered: {
                    dataSource.update(view.series(0));
                    dataSource.update(view.series(1));
                }
        }

        //var myAxisX = chartView.axisX(view);
        //var myAxisY = chartView.axisY(view);
    }



}
