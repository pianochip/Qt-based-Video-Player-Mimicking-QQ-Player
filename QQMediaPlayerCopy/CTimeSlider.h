#pragma once
#include <QSlider>

//视频进度条
class CTimeSlider : public QSlider 
{
	Q_OBJECT
public:
	//定义构造函数和析构函数
	explicit CTimeSlider(QWidget* p = nullptr);
	~CTimeSlider();
	
	//设置进度条范围
	void setTimeSliderRange(qint64 value);
	//设置进度条的值
	void setSliderValue(qint64 value);

protected:
	//定义事件过滤器
	bool eventFilter(QObject* slider, QEvent* event) override;

private:
	//实现点击进度条后， 跳往对应位置
	void slider_mouseLButtonPress(QObject* slider, QEvent* event);

signals:
	void sig_SliderMove(int value);

private slots:
	void onSliderMoved(int position);

private:
	int m_bSliderPressed = false;
	int m_SliderHeight = 15;
};
