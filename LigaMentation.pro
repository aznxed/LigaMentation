TEMPLATE = app

QT += qml quick
QT += serialport
QT += charts

CONFIG += c++11

SOURCES += main.cpp \
    datasource.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Untitled.png \
    IMG_7038.JPG \
    Images/padels.png

HEADERS += \
    datasource.h
