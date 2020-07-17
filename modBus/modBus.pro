QT += core quick gui serialbus serialport qml widgets

LIBS += -lasound -lmodbus

TARGET = modTest
TEMPLATE = app
CONFIG += c++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += qml.qrc

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    myGlobal.cpp \
    myStyle.cpp \
    backlight.cpp \
    gpiocontroller.cpp \
    gpiopin.cpp \
    network.cpp \
    serialcontroller.cpp \
    system.cpp \
    translator.cpp \
    modb.cpp \
    writeregistermodel.cpp

HEADERS += \
    backlight.h \
    common.h \
    gpiocontroller.h \
    gpiopin.h \
    i2c-dev.h \
    myGlobal.h \
    myStyle.h \
    network.h \
    serialcontroller.h \
    sound.h \
    system.h \
    translator.h \
    modb.h \
    writeregistermodel.h

DISTFILES +=
