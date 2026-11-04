#include "CTitleBar.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QMenu>
#include <QMouseEvent>
#include "qss.h"
#include <Windows.h>
#include <QMessageBox>
#include <QSettings>
#include <QStandardPaths>
#include <QFileDialog>
#include "CNetStreamDlg.h"

#include <qt_windows.h>
#pragma comment(lib, "user32.lib")

CTitleBar::CTitleBar(QWidget* parent)
	: QWidget(parent)
{
	this->setAttribute(Qt::WA_DeleteOnClose);
	setMouseTracking(true);
	InitData();
}
CTitleBar::~CTitleBar() {}

//初始化
void CTitleBar::InitData() {
	//设置标题栏
	setAttribute(Qt::WA_StyledBackground);
	int w = 20;
	int h = 20;
	int margin = 5;
	this->setFixedHeight(h + margin * 2);
	this->setStyleSheet("background-color:rgb(54,54,54)");

	//主菜单按钮及菜单
	m_pLogoBtn = new QPushButton(this);
	m_pLogoBtn->setFixedWidth(120);
	m_pLogoBtn->setText(tr("Media Player"));
	m_pLogoBtn->setStyleSheet(logo_button_qss);

	QMenu* pMenu = new QMenu(this);
	pMenu->setStyleSheet(menu_qss);
	m_pLogoBtn->setMenu(pMenu);
	QAction* pAc1 = new QAction(tr("open file"), this);
	QAction* pAc2 = new QAction(tr("open floder"), this);
	QAction* pAc3 = new QAction(tr("open net stream"), this);
	QAction* pAc4 = new QAction(tr("exit"), this);
	pMenu->addAction(pAc1);
	pMenu->addAction(pAc2);
	pMenu->addAction(pAc3);
	pMenu->addAction(pAc4);
	connect(pAc1, &QAction::triggered, this, &CTitleBar::openFile);
	connect(pAc2, &QAction::triggered, this, &CTitleBar::openFloder);
	connect(pAc3, &QAction::triggered, this, &CTitleBar::openNetStream);
	connect(pAc4, &QAction::triggered, this, &CTitleBar::exit);

	//小窗、置顶、最小化、最大化/复原、关闭
	m_pMinimodeBtn = new QPushButton(this);
	m_pMinimodeBtn->setObjectName("m_pMinimodeBtn");
	m_pMinimodeBtn->setText("");
	m_pMinimodeBtn->setFixedSize(w, h);
	m_pMinimodeBtn->setStyleSheet(minimode_qss);

	m_pSettopBtn = new QPushButton(this);
	m_pSettopBtn->setObjectName("m_pSettopBtn");
	m_pSettopBtn->setText("");
	m_pSettopBtn->setToolTip(tr("set to top window"));
	m_pSettopBtn->setFixedSize(w, h);
	m_pSettopBtn->setStyleSheet(settop_qss);

	m_pMinBtn = new QPushButton(this);
	m_pMinBtn->setObjectName("m_pMinBtn");
	m_pMinBtn->setText("");
	m_pMinBtn->setFixedSize(w, h);
	m_pMinBtn->setStyleSheet(min_qss);

	m_pMaxBtn = new QPushButton(this);
	m_pMaxBtn->setObjectName("m_pMaxBtn");
	m_pMaxBtn->setText("");
	m_pMaxBtn->setFixedSize(w, h);
	m_pMaxBtn->setStyleSheet(max_normal_qss);
	
	m_pCloseBtn = new QPushButton(this);
	m_pCloseBtn->setObjectName("m_pCloseBtn");
	m_pCloseBtn->setText("");
	m_pCloseBtn->setFixedSize(w, h);
	m_pCloseBtn->setStyleSheet(close_qss);

	connect(m_pMinBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
	connect(m_pMaxBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
	connect(m_pCloseBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
	connect(m_pMinimodeBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
	connect(m_pSettopBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);

	//视频名称
	m_pFileNameLabel = new QLabel(this);
	m_pFileNameLabel->setAlignment(Qt::AlignCenter);
	m_pFileNameLabel->hide();  // 视频文件标题，默认隐藏
	m_pFileNameLabel->setStyleSheet("QLabel{font-family:Microsoft YaHei; \
		font-size:14px;color:#FFFFFF;background-color:#363636;}");
}

//设置正在播放的视频标题
void CTitleBar::setFileNameLabelText(QString name) {
	m_pFileNameLabel->show();
	m_pFileNameLabel->setText(name);
}

//重置UI
void CTitleBar::RestoreUI() {
	m_pLogoBtn->move(5, 5);

	int w = this->width();
	int h = this->height();

	m_pCloseBtn->move(w - 25, 5);
	m_pMaxBtn->move(w - 25 - 35, 5);
	m_pMinBtn->move(w - 25 - 35 * 2, 5);
	m_pSettopBtn->move(w - 25 - 35 * 3, 5);
	m_pMinimodeBtn->move(w - 25 - 35 * 4, 5);

	m_pFileNameLabel->setFixedWidth(w - 120 - 5 - 25 - 35 * 4 - 5);
	m_pFileNameLabel->move(120 + 5 + 5, 5);
}

//拉伸窗口
void CTitleBar::resizeEvent(QResizeEvent* event) {
	RestoreUI();
}

//鼠标点击事件，拖拽移动
void CTitleBar::mousePressEvent(QMouseEvent* event)
{
	if (ReleaseCapture())
	{
		QWidget* pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
	event->ignore();
}

//双击全屏
void CTitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	emit sig_ShowFullFcreen();
}

//点击
void CTitleBar::onClicked() {
	QPushButton* pButton = qobject_cast<QPushButton*>(sender()); //找到触发这个槽函数的事件的对象
	QWidget* pWindow = this->window(); //找到包含这个窗口的主窗口

	if (pButton == m_pMinBtn) {//点了最小化按钮
		pWindow->showMinimized();
	}
	else if (pButton == m_pMaxBtn) {//点了最大化按钮
		if (pWindow->isMaximized()) { //判断是否已经是最大化
			pWindow->showNormal();
			m_pMaxBtn->setStyleSheet(max_normal_qss);
		}
		else {
			pWindow->showMaximized();
			m_pMaxBtn->setStyleSheet(maxed_qss);
		}
	}
	else if (pButton == m_pMinimodeBtn) { //点了小窗按钮
		emit sig_showMiniMode();
	}
	else if (pButton == m_pSettopBtn) { //点了置顶按钮
		HWND hwnd = (HWND)(pWindow->winId());
		if (::GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_TOPMOST)
		{
			// The window is topmost.
			::SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			m_pSettopBtn->setStyleSheet(settop_qss);
			m_pSettopBtn->setToolTip(tr("set to top window"));
		}
		else
		{
			// The window is not topmost.
			::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			m_pSettopBtn->setStyleSheet(settoped_qss);
			m_pSettopBtn->setToolTip(tr("cancal top window"));
		}
	}
	else if (pButton == m_pCloseBtn) //点击关闭按钮
	{
		emit sig_close();
	}

}

//左上角菜单里打开文件，拿到文件路径用信号传送出去
void CTitleBar::openFile()
{
	QString cfgPath = "HKEY_CURRENT_USER\\Software\\CMainWindow";
	QSettings settings(cfgPath, QSettings::NativeFormat);
	QString lastPath = settings.value("openfile_path").toString();  // 从注册表获取路径

	if (lastPath.isEmpty())
	{
		lastPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);  //获取默认的文档路径 
	}

	//可以同时打开多个文件
	QStringList filelist = QFileDialog::getOpenFileNames(
		this,
		tr("select video file"),
		lastPath,
		tr("video file (*.flv *.rmvb *.avi *.mp4);; all files(*.*);; "));

	if (filelist.isEmpty())
	{
		return;
	}

	int end = filelist[0].lastIndexOf("/");
	QString tmppath = filelist[0].left(end + 1);
	settings.setValue("openfile_path", tmppath);  // 将当前打开的路径写入到注册表

	emit sig_openfile(filelist);
}

//左上角菜单里打开文件夹，拿到文件路径用信号传送出去
void CTitleBar::openFloder()
{
	QString cfgPath = "HKEY_CURRENT_USER\\Software\\CMainWindow";
	QSettings settings(cfgPath, QSettings::NativeFormat);
	QString lastPath = settings.value("openfile_path").toString();  // 从注册表获取路径

	if (lastPath.isEmpty())
	{
		lastPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);  //获取默认的文档路径 
	}

	QString path = QFileDialog::getExistingDirectory( //返回打开的目录的路径
		this,
		tr("choose video directory"),
		lastPath
	);

	if (path.isEmpty())
	{
		return;
	}

	QDir dir(path);

	QStringList nameFilters;
	nameFilters << "*.mp4" << "*.flv" << "*.rmvb" << "*.avi";

	//将过滤后的文件名称存入到files列表中
	QStringList files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name); //存储符合条件的文件名和扩展名

	int _size = files.size();
	if (_size == 0)
	{
		QMessageBox::information(this, tr("Warn"), tr("this floder no video files"));
		return;
	}

	QStringList fileList;
	for (int i = 0; i < _size; i++)
	{
		QString fileName = path + "/" + files[i];
		fileList << fileName;
	}

	settings.setValue("openfile_path", path);  // 将当前打开的路径写入到注册表

	emit sig_openfile(fileList);
}

//左上角菜单里打开网络流，拿到地址用信号传送出去
void CTitleBar::openNetStream() {
	CNetStreamDlg dlg;
	if (dlg.exec() == QDialog::Accepted)
	{
		QString strText = dlg.getUrl();
		emit sig_openUrl(strText);
	}
}

//左上角菜单里点击退出
void CTitleBar::exit()
{
	::exit(0);
}