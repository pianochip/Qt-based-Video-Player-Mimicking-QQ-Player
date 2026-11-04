#pragma once
#include <QWidget>
#include "CVolumeButton.h"

//把5个按钮（停止、上一集、播放、下一集、音量）拼装成一排，并对外统一提供控制接口
class CPlayButtonGroupWidget : public QWidget 
{	
	Q_OBJECT
public:
	CPlayButtonGroupWidget(QWidget* parent = nullptr);
	~CPlayButtonGroupWidget();

private:
	//五个按钮
	QPushButton* m_pStopButton = nullptr; //停止按钮
	QPushButton* m_pPreButton = nullptr; //上一集
	QPushButton* m_pPlayButton = nullptr; //播放
	QPushButton* m_pNextButton = nullptr; //下一集
	CVolumeButton* m_pVolumeButton = nullptr; // 音量

signals:
	void sig_stop();
	void sig_pre();
	void sig_play();
	void sig_next();
	void sig_VolumeChanged(int value);
};