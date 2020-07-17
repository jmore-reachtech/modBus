#include "myStyle.h"
#include <QDebug>

StyleValues::StyleValues(QObject * parent): QQmlPropertyMap(this, parent) {
  setObjectName("style");
  insert("statusBarHeight", QVariant::fromValue(40));

  insert("columnSpacing", QVariant::fromValue(102));
  insert("rowSpacing", QVariant::fromValue(40));

  insert("themeDark", true);
  insert("backColor", QVariant::fromValue(QString("gray")));
  insert("textColor", QVariant::fromValue(QString("white")));
  insert("statusBackColor", QVariant::fromValue(QString("white")));
  insert("statusTextColor", QVariant::fromValue(QString("gray")));

  insert("clrOff", QVariant::fromValue(QString("gray")));
  insert("clrNormal", QVariant::fromValue(QString("green")));
  insert("clrWarning", QVariant::fromValue(QString("goldenrod")));
  insert("clrFault", QVariant::fromValue(QString("#ff3434")));
  insert("clrError", QVariant::fromValue(QString("red")));

  insert("backColorLt", QVariant::fromValue(QString("white")));
  insert("textColorLt", QVariant::fromValue(QString("black")));
  insert("statusBackColorLt", QVariant::fromValue(QString("lightGrey")));
  insert("statusTextColorLt", QVariant::fromValue(QString("black")));

  insert("clrOffLt", QVariant::fromValue(QString("darkGray")));
  insert("clrNormalLt", QVariant::fromValue(QString("darkGreen")));
  insert("clrWarningLt", QVariant::fromValue(QString("yellow")));
  insert("clrFaultLt", QVariant::fromValue(QString("red")));
  insert("clrErrorLt", QVariant::fromValue(QString("darkRed")));

  insert("backColorDk", QVariant::fromValue(QString("black")));
  insert("textColorDk", QVariant::fromValue(QString("white")));
  insert("statusBackColorDk", QVariant::fromValue(QString("darkCyan")));
  insert("statusTextColorDk", QVariant::fromValue(QString("white")));

  insert("clrOffDk", QVariant::fromValue(QString("lightGray")));
  insert("clrNormalDk", QVariant::fromValue(QString("lightGreen")));
  insert("clrWarningDk", QVariant::fromValue(QString("lightYellow")));
  insert("clrFaultDk", QVariant::fromValue(QString("tomato")));
  insert("clrErrorDk", QVariant::fromValue(QString("lightRed")));

  insert("fontName", QVariant::fromValue(QString("Source Sans Pro")));
  insert("fontSize", QVariant::fromValue(17));
/*
  insert("strOff", QVariant::fromValue(QString("System Off")));
  insert("strNormal", QVariant::fromValue(QString("System Normal")));
  insert("strWarning", QVariant::fromValue(QString("System Warning")));
  insert("strFault", QVariant::fromValue(QString("System Fault")));
  insert("strError", QVariant::fromValue(QString("System Error")));

  insert("imgOff", QVariant::fromValue(QString("Images/led_off_40.png")));
  insert("imgNormal", QVariant::fromValue(QString("Images/led_normal_40.png")));
  insert("imgWarning", QVariant::fromValue(QString("Images/led_warning_40.png")));
  insert("imgFault", QVariant::fromValue(QString("Images/led_fault_40.png")));
  insert("imgError", QVariant::fromValue(QString("Images/led_error_40.png")));
*/

  insert("imgLogo", QVariant::fromValue(QString("Images/reach_logo_color_30.png")));
  insert("borderWidth", QVariant::fromValue(1));
  insert("borderColor", QVariant::fromValue(QString("lightGray")));

  insert("dialWidth", QVariant::fromValue(150));
  insert("dialHeight", QVariant::fromValue(200));
  insert("dialBarWidth", QVariant::fromValue(15));
  insert("dialTicksOn", QVariant::fromValue(true));

  insert("componentX", QVariant::fromValue(130));
  insert("componentY", QVariant::fromValue(160));
  insert("iconSize", QVariant::fromValue(100));

  insert("textY", QVariant::fromValue(90));
  insert("imgX", QVariant::fromValue(QString("Images/X_100.png")));



  insert("clrConnBox", QVariant::fromValue(QString("tan")));

  insert("connectedText",QVariant::fromValue(QString( "Connect") ));
  insert("clrConnect", QVariant::fromValue(QString("gray")));
  insert("clrBtnConn", QVariant::fromValue(QString("lightGray")));
  insert("connectedFontColor", QVariant::fromValue(QString("black")));

  insert("clrStatus", QVariant::fromValue(QString("white")));
  insert("clrNonStatus", QVariant::fromValue(QString("green")));
  insert("clrSerial", QVariant::fromValue(QString("white")));
  insert("clrTCP", QVariant::fromValue(QString("green")));



}

void StyleValues::startEngine() {
  qDebug() << "Start ENGINE STYLE " << Q_FUNC_INFO;
}

QString StyleValues::getColor(const QString name) {
  QVariant tempColor = value(name);
  return tempColor.value < QString > ();
}
