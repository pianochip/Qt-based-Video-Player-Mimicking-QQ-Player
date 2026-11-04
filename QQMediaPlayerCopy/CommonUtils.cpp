#include "CommonUtils.h"
#include <QSettings>

void CommonUnils::writeIni(QString inipath, QString keystr, QString value) {
	QSettings config(inipath, QSettings::IniFormat); 
	config.setValue(keystr, value);
}

QString CommonUnils::readIni(QString inipath, QString keystr) {
	QSettings config(inipath, QSettings::IniFormat);
	return config.value(keystr).toString(); //QVariant QSettings::value() 所以要转为字符串
}

