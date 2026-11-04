#pragma once
#include <QString>

class CommonUnils { //用于"配置文件"的读和写
public:
	static void writeIni(QString inipath, QString keystr, QString value); //将配置信息写入磁盘
	static QString readIni(QString inipath, QString keystr); //将配置信息从磁盘读取出来
};

