#pragma once
#include <QWidget>
#include <QPushButton>
#include <QAbstractNativeEventFilter>
#include "CVideoWidgetTopWidget.h"

//视频播放窗口
class VideoWidget : public QWidget, public QAbstractNativeEventFilter 
{
	Q_OBJECT

public:
	VideoWidget(QWidget* p = NULL);
	~VideoWidget();

	void showTopWidget(bool show); //显示/隐藏中间及侧边按钮
	void showTopWidgetOpenfilesButton(bool show); // 显示/隐藏中间打开文件按钮
	void setPlayStatus(bool play); //同步播放状态给窗口

private:
	QPoint m_dPos;   //VideoWidget相对于父窗口的位置
	CVideoWidgetTopWidget* m_pTopWidget = nullptr;
	bool m_isPlay = false; //是否正在播放视频

protected:
	void resizeEvent(QResizeEvent* event) override; 
	bool nativeEventFilter(const QByteArray& eventType, void* message, qintptr* result) override; 

signals:
	void sig_OpenFile(const QStringList& fileList);
	void sig_OpenUrl(const QString& url);
	void sig_OpenFloder(QString path);
	void sig_OpenPlaylist();
	void sig_Totalms(const qint64& duration);  //视频总时长
	void sig_VideoPositionChanged(const qint64& pos);   //视频播放位置变化
	void sig_SliderMoved(int value); //进度条滑动

};