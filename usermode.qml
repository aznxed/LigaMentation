import QtQuick 2.5
import QtQuick.Window 2.2

Item {
    id: main
    visible: true
    width: 1000
    height: 600

    Rectangle{
        id: background
        visible: true
        width: parent.width
        height: parent.height
        color: "black"
    }

    Image {
        id: tensor
        source: "Images/padels.png"
        x: -70
        width: parent.width
        height: parent.height

        Image {
            id: leftlight_green
            source: "Images/green.png"
            x: tensor.width * (1/2.5) + 45
            y: tensor.height * (1/3) - 30
            visible: true
        }

        Image {
            id: leftlight_red
            source: "Images/red.png"
            visible: false
        }

        Image {
            id: rightlight_green
            source: "Images/green.png"
            visible: false
        }

        Image {
            id: rightlight_red
            source: "Images/red.png"
            visible: false
        }

    }




}
