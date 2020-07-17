#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QQmlContext>
#include <QLoggingCategory>
#include <QQuickWindow>
#include <QVariant>
#include <QScreen>

#include "signal.h"
#include "common.h"
#include "mainwindow.h"
#include "serialcontroller.h"
#include "translator.h"
#include "network.h"
//#include "beeper.h"
#include "gpiopin.h"
#include "backlight.h"
#include "system.h"
#include "myStyle.h"
#include "myGlobal.h"
#include "modb.h"

StyleValues MyStyle;
GlobalValues MyGlobal;


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("MyStyle", & MyStyle);
    engine.rootContext()->setContextProperty("MyGlobal", & MyGlobal);
    qDebug() << "The global count is => " << MyGlobal.count();
    qDebug() << "The style count is => " << MyStyle.count();

    SerialController serialController;
    ModB modB;

    /* Need to register before the MainviewController is instantiated */
    qmlRegisterType < Network > ("net.reachtech", 1, 0, "Network");
//    qmlRegisterType < Beeper > ("sound.reachtech", 1, 0, "Beeper");
    qmlRegisterType < GpioPin > ("gpio.reachtech", 1, 0, "GpioPin");
    qmlRegisterType < Backlight > ("backlight.reachtech", 1, 0, "Backlight");
    qmlRegisterType < System > ("system.reachtech", 1, 0, "System");

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    MyGlobal.insert("screenWidth", screenGeometry.width());
    MyGlobal.insert("screenHeight", screenGeometry.height());
    MyGlobal.insert("screenFactor", screenGeometry.height());
    qDebug() << "Screen Size is"  << MyGlobal.value("screenWidth").toInt() << "x" <<  MyGlobal.value("screenHeight").toInt();


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
      return -1;

    qDebug() << "Engine LOAD complete";

    QObject * topLevel = engine.rootObjects().value(0);
    QQuickWindow * theWindow = qobject_cast < QQuickWindow * > (topLevel);

    if (theWindow == nullptr) {
      qDebug() << "Can't instantiate window";
    }

    qDebug() << "Screen Factor is"  << MyGlobal.value("screenFactor").toInt();


    bool success = QObject::connect(theWindow, SIGNAL(submitTextField(QString)), &serialController, SLOT(send(QString)));
    Q_ASSERT(success);
    success = QObject::connect(&modB, SIGNAL(submitTextField(QString)), &serialController, SLOT(send(QString)));
    Q_ASSERT(success);
    success = QObject::connect(&modB, SIGNAL(setConsole(QVariant)),theWindow, SLOT(setConsole(QVariant)));
    Q_ASSERT(success);
    success = QObject::connect(theWindow, SIGNAL(processConnect()), &modB, SLOT(onDoConnectChanged()));
    Q_ASSERT(success);
    success = QObject::connect(theWindow, SIGNAL(processDisconnect()), &modB, SLOT(onDoDisconnectChanged()));
    Q_ASSERT(success);
    success = QObject::connect(theWindow, SIGNAL(connTypeChanged()), &modB, SLOT(onModConnectTypeTCPChanged()));
    Q_ASSERT(success);
    success = QObject::connect(theWindow, SIGNAL(read() ), &modB, SLOT(read()));
    Q_ASSERT(success);
    success = QObject::connect(theWindow, SIGNAL(write() ), &modB, SLOT(write()));
    Q_ASSERT(success);

    qDebug() << "App EXEC ";
    return app.exec();
    qDebug() << "App EXEC is DONE";

}


