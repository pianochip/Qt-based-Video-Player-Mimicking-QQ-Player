#include "VideoWidget.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QDebug>
#include <qt_windows.h>
#include <QApplication>
#include <QMessageBox>
#include <iostream>
using namespace std;

VideoWidget::VideoWidget(QWidget* p)
	:QWidget(p)
{	
	this->setAttribute(Qt::WA_StyledBackground);  
	this->setAttribute(Qt::WA_OpaquePaintEvent);
	qApp->installNativeEventFilter(this);
	setMouseTracking(true);
	this->setStyleSheet("QWidget{\
                       background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #09115C, stop:1 #000000 );\
                        font-family:Microsoft YaHei\
                         }");
	this->setMinimumSize(800, 450);

	m_pTopWidget = new CVideoWidgetTopWidget(this);
	connect(m_pTopWidget, &CVideoWidgetTopWidget::sig_OpenFile, this, &VideoWidget::sig_OpenFile);
	connect(m_pTopWidget, &CVideoWidgetTopWidget::sig_OpenUrl, this, &VideoWidget::sig_OpenUrl);
	connect(m_pTopWidget, &CVideoWidgetTopWidget::sig_OpenPlaylist, this, &VideoWidget::sig_OpenPlaylist);
}
VideoWidget::~VideoWidget() {}

//显示/隐藏中间及侧边按钮
void VideoWidget::showTopWidget(bool show) {
	if (show) {
		m_pTopWidget->show();
		m_pTopWidget->showOpenFileBtn(false);
	}
	else {
		m_pTopWidget->hide();
	}
}

// 显示/隐藏中间打开文件按钮
void VideoWidget::showTopWidgetOpenfilesButton(bool show) {
		m_pTopWidget->showOpenFileBtn(show);
}

//同步播放状态给黑板
void VideoWidget::setPlayStatus(bool play) {
	m_isPlay = play;
}

//当视频播放窗口变化时，让装着打开文件按钮和侧边栏按钮的界面跟着变化
void VideoWidget::resizeEvent(QResizeEvent* event) {
	m_dPos = this->pos();

	QPoint pos = this->mapToGlobal(QPoint(0, 0));
	m_pTopWidget->resize(this->width(), this->height());
	m_pTopWidget->move(pos);
	m_pTopWidget->show();
}

bool VideoWidget::nativeEventFilter(const QByteArray& eventType, void* message, qintptr* result) {
	if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
	{
		MSG* pMsg = reinterpret_cast<MSG*>(message);
		if (pMsg->message == 1025 || pMsg->message == 512)
		{
			QPoint pos = this->window()->mapToGlobal(QPoint(0, 0));
			m_pTopWidget->move(pos + m_dPos);
		}
	}

	return false;
}

