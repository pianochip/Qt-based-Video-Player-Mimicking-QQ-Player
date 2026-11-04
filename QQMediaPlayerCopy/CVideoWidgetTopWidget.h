#pragma once
#include <QWidget>
#include <QPushButton>
#include "COpenFileButton.h"
#include <QSlider>

//屏幕中央及右侧控件
class CVideoWidgetTopWidget : public QWidget
{
	Q_OBJECT

public:
	CVideoWidgetTopWidget(QWidget* p = nullptr);
	~CVideoWidgetTopWidget();

	void showRightBtn(bool flag); // 显示/隐藏侧边栏按钮
	void showOpenFileBtn(bool flag); // 显示/隐藏中央按钮组
	void setPlayStatus(bool play) //设置播放状态
	{ 
		m_isPlay = play; 
	} 

private:
	COpenFileButton* m_pOpenFileButton; //屏幕中央选择文件按钮组
	QPushButton* m_pOpenrRightlistButton; //屏幕右侧打开侧边栏按钮 
	bool m_isPlay = false; //播放状态

protected:
	void resizeEvent(QResizeEvent* event) override;

signals:
	void sig_OpenFile(const QStringList& fileList);
	void sig_OpenUrl(const QString& url);
	void sig_OpenPlaylist();
};