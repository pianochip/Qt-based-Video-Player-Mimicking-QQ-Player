#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include "CPlayButtonGroupWidget.h"
#include "CTimeSlider.h"

//底部播放控制栏,组装CPlayButtonGroupWidget和CTimeSlider
class CPlayCtrlBar : public QWidget 
{
	Q_OBJECT
public:
	CPlayCtrlBar(QWidget* parent = nullptr);
	~CPlayCtrlBar();

	void showTimeLabel(bool isShow); // 显示/隐藏时间标签
	void showSlider(bool flag);      // 显示/隐藏进度条
	
	void setCurPlayTime(const QString& curPlaytime); //设置最新的时间文字
	void setTimeSliderRange(qint64 value); //设置视频的总时长
	void setSliderValue(qint64 value); //设置进度条的值
	
private:
	CTimeSlider* m_pTimeSlider = nullptr; //进度条
	CPlayButtonGroupWidget* m_pPlayButtonGroupWidget = nullptr; //按键组
	QPushButton* m_pSpeedButton = nullptr; //倍速
	QPushButton* m_pFullscreenButton = nullptr; //全屏
	QLabel* m_pCurPlayTimeLabel = nullptr; //时间标签

	void InitData(); //初始化上述五个对象
	void RestoreUI(); //排版

	void resizeEvent(QResizeEvent* event) override; //管理用户拉伸界面时，界面UI的显示
	bool eventFilter(QObject* watched, QEvent* event) override; //事件过滤器

private slots:
	void onSliderMoved(int position);

signals:
	void sig_stop();
	void sig_pre();
	void sig_play();
	void sig_next();
	void sig_VolumeChanged(int value);

	void sig_fullScreen(); 
	void sig_playRate(double rate); 
	void sig_SliderMove(int value); 
};