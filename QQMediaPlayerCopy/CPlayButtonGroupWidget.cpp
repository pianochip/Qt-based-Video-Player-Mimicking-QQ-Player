#include "CPlayButtonGroupWidget.h"
#include <QHBoxLayout>

CPlayButtonGroupWidget::CPlayButtonGroupWidget(QWidget* parent)
	:QWidget(parent)
{	///设置样式
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_StyledBackground);
	//实例化按钮
	m_pStopButton = new QPushButton(this);
	m_pStopButton->setText("");
	m_pStopButton->setFixedSize(32, 32);
	m_pStopButton->setStyleSheet("QPushButton{background-image:url(:/playCtrlBar/resources/playctrlBar/stop.svg);border:none;}"
		"QPushButton:hover{background-color:rgb(99, 99, 99);background-image:url(:/playCtrlBar/resources/playctrlBar/stop_hover.svg);border:none;}"
		"QPushButton:pressed{background-image:url(:/playCtrlBar/resources/playctrlBar/stop.svg);border:none;}");
	
	m_pPreButton = new QPushButton(this);
	m_pPreButton->setText("");
	m_pPreButton->setFixedSize(32, 32);
	m_pPreButton->setStyleSheet("QPushButton{background-image:url(:/playCtrlBar/resources/playctrlBar/pre.svg);border:none;}"
		"QPushButton:hover{background-color:rgb(99, 99, 99);background-image:url(:/playCtrlBar/resources/playctrlBar/pre_hover.svg);border:none;}"
		"QPushButton:pressed{background-image:url(:/playCtrlBar/resources/playctrlBar/pre.svg);border:none;}");
	
	m_pPlayButton = new QPushButton(this);
	m_pPlayButton->setText("");
	m_pPlayButton->setFixedSize(48, 48);
	m_pPlayButton->setStyleSheet("QPushButton{background-image:url(:/playCtrlBar/resources/playctrlBar/play.svg);border:none;}"
		"QPushButton:hover{background-color:rgb(99, 99, 99);background-image:url(:/playCtrlBar/resources/playctrlBar/play_hover.svg);border:none;}"
		"QPushButton:pressed{background-image:url(:/playCtrlBar/resources/playctrlBar/play.svg);border:none;}");

	m_pNextButton = new QPushButton(this);
	m_pNextButton->setText("");
	m_pNextButton->setFixedSize(32, 32);
	m_pNextButton->setStyleSheet("QPushButton{background-image:url(:/playCtrlBar/resources/playctrlBar/next.svg);border:none;}"
		"QPushButton:hover{background-color:rgb(99, 99, 99);background-image:url(:/playCtrlBar/resources/playctrlBar/next_hover.svg);border:none;}"
		"QPushButton:pressed{background-image:url(:/playCtrlBar/resources/playctrlBar/next.svg);border:none;}");

	m_pVolumeButton = new CVolumeButton(this);

	//设置水平布局
	QHBoxLayout* pHLay = new QHBoxLayout(this);
	pHLay->setSpacing(8);
	pHLay->addWidget(m_pStopButton);
	pHLay->addWidget(m_pPreButton);
	pHLay->addWidget(m_pPlayButton);
	pHLay->addWidget(m_pNextButton);
	pHLay->addWidget(m_pVolumeButton);

	pHLay->setContentsMargins(1, 1, 1, 1);

	//设置底部控制栏的大小
	setFixedSize(32 * 4 + 48 + 4 * 8 + 20, 50);
	
	//连接信号和槽
	connect(m_pStopButton, &QPushButton::clicked, this, &CPlayButtonGroupWidget::sig_stop);
	connect(m_pPreButton, &QPushButton::clicked, this, &CPlayButtonGroupWidget::sig_pre);
	connect(m_pPlayButton, &QPushButton::clicked, this, &CPlayButtonGroupWidget::sig_play);
	connect(m_pNextButton, &QPushButton::clicked, this, &CPlayButtonGroupWidget::sig_next);
	connect(m_pVolumeButton, &CVolumeButton::sig_VolumeValue, this, &CPlayButtonGroupWidget::sig_VolumeChanged);
}

CPlayButtonGroupWidget::~CPlayButtonGroupWidget()
{
}