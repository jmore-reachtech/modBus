#include <QIODevice>
#include <QTextStream>
#include <QMap>
#include <QDebug>

#include "translator.h"
#include "common.h"
#include "myStyle.h"
#include "myGlobal.h"
#include <string>


extern StyleValues MyStyle;
extern GlobalValues MyGlobal;

Translator::Translator(QObject * parent): QObject(parent), m_settings(APP_SETTINGS_PATH, QSettings::NativeFormat) {
  qDebug() << "Translator constructor --";
  m_settings.beginGroup("Translate");
  m_translateFile.setFileName(m_settings.value("translate_file").value < QString > ());
  m_settings.endGroup();
}

Translator::~Translator() {
  if (m_translateFile.isOpen()) {
    m_translateFile.close();
  }
}


QStringList Translator::translateGui(QString msg) {
  QStringList list = msg.split("=");
  return list;
}

QStringList Translator::translateSerial(QString msg) {
  QStringList split = msg.split("=");

  if (split.length() != 2)  {
    if(( msg.compare("\r") != 0)) {
        qDebug() << "ERROR - Message in wrong format, missing equals -- " << msg ;
    }
    return split;
  }

  QString valu = split[1].toLocal8Bit();
    valu.remove("\r");
//  qDebug() << "Data = " << split[0] << " " << valu;

  if (MyStyle.contains(split[0])) {
    QVariant myType = MyStyle.value(split[0]);  //find the type of variable stored
    int theType = myType.type();

    if (theType == 1) //Bool
    {
//      qDebug() << "BOOL";
      bool b = (strcmp("true", valu.toLocal8Bit()) == 0) ? true : false;
      MyStyle.insert(split[0], b);
    } else if (theType == 2) //Int
    {
//      qDebug() << "INT";
      MyStyle.insert(split[0], valu.toInt());
    } else if (theType == 6) //Double
    {
//     qDebug() << "DOUBLE";
      MyStyle.insert(split[0], valu.toDouble());
    } else if (theType == 10) //String
    {
//    qDebug() << "STRING";
      MyStyle.insert(split[0], valu);
    } else {
      qDebug() << "ERROR - Did not find a valid match for Type " << theType;
    }

//    qDebug() << "Set S Var" << split[0] << "to" << MyStyle.value(split[0]);
  } else if (MyGlobal.contains(split[0])) {
//    qDebug() << "myGlobal = " << split[0];
    QVariant myType = MyGlobal.value(split[0]);
    int theType = myType.type();

    if (theType == 1) //Bool
    {
//      qDebug() << "@@@@ Bool data  " << split[0] << " | " << valu ;
      bool b = (QString::compare("true", valu) == 0) ? true : false;
      MyGlobal.insert(split[0], b);
    } else if (theType == 2) //Int
    {
//      qDebug() << "@@@@ Int data  " << split[0];
      MyGlobal.insert(split[0], valu.toInt());
    } else if (theType == 6) //Double
    {
//        qDebug() << "@@@@ Double data  " << split[0];
      MyGlobal.insert(split[0], valu.toDouble());
    } else if (theType == 10) //String
    {
//        qDebug() << "@@@@ String data  " << split[0];
      MyGlobal.insert(split[0], valu);
    } else if (theType == 12) //QByteArray
    {
//      qDebug() << "@@@@ QByteArray data  " << split[0] << " data -- " << valu << " " << sizeof(valu);
      //QString foo = split[1];
      QByteArray ba =  QByteArray::fromHex(valu.toUtf8());
      qDebug() << "QByteArray " << ba.toHex();
      MyGlobal.insert(split[0], ba);
    } else {
      qDebug() << "ERROR - Did not find a valid match for Type " << theType;
    }
  } else {
    qDebug() << "ERROR No item " << split[0] << " found in Style or Global";
  }

  QStringList lst;
  return lst;
}
