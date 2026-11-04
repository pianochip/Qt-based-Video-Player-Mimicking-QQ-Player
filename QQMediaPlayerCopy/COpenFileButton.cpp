#include "COpenFileButton.h"
#include "CNetStreamDlg.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QMenu>
#include <QEvent>
#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>
#include <QMessageBox>

#define LEFT_BUTTON_WIDTH 145
#define RIGHT_BUTTON_WIDTH 60
#define BUTTON_HEIGHT 40

COpenFileButton::COpenFileButton(QWidget* parent)
	:QWidget(parent)
{	//设置总按钮的样式
	this->setFixedSize(m_totalWidth, BUTTON_HEIGHT);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);


	//计算按钮总宽度
	m_totalWidth = LEFT_BUTTON_WIDTH + RIGHT_BUTTON_WIDTH;
	
	//打开文件 按钮
	m_pOpenFileButton = new QPushButton(this);
	m_pOpenFileButton->setText(tr("open file"));
	m_pOpenFileButton->setFixedSize(LEFT_BUTTON_WIDTH, BUTTON_HEIGHT);
	m_pOpenFileButton->setIcon(QIcon(":/videoWidget/resources/videoWidget/openfile.svg"));
	m_pOpenFileButton->setStyleSheet("QPushButton{"
		"padding-left:30px;"
		"border-top-left-radius:20px;border-bottom-left-radius:20px;"
		"background-color: rgb(55, 55, 55);"
		"color:rgb(255, 255, 255);"
		"text-align:left;"
		"}");
	connect(m_pOpenFileButton, &QPushButton::clicked, this, &COpenFileButton::on_openfile);

	//下拉菜单 按钮
	m_pArrowButton = new QPushButton(this);
	m_pArrowButton->setFixedSize(RIGHT_BUTTON_WIDTH, BUTTON_HEIGHT);
	m_pArrowButton->setStyleSheet("QPushButton{"
		"background-image: url(:/videoWidget/resources/videoWidget/vline.svg);"
		"background-repeat: no-repeat;"
		"background-origin: padding;"
		"background-position: left;"
		"border-top-right-radius:20px;border-bottom-right-radius:20px;"
		"background-color: rgb(55, 55, 55);}"
		"QPushButton::menu-indicator:open{"
		"image:url(:/videoWidget/resources/videoWidget/down_arrow_16px.svg);"
		"subcontrol-position:right center;right:10px;"
		"subcontrol-origin:padding;border:none;}"
		"QPushButton::menu-indicator:closed{"
		"image:url(:/videoWidget/resources/videoWidget/down_arrow_16px.svg);"
		"subcontrol-position:right center;right:10px;"  
		"subcontrol-origin:padding;border:none;}");

	//下拉菜单
	QMenu* pMenu = new QMenu(this);
	pMenu->setStyleSheet(R"(
		QMenu
		{
			background-color:rgb(73, 73, 73);
		}
		QMenu::item
		{
			 font:16px;
			 color:white;
			 background-color:rgb(73, 73, 73);
			 margin:8px 8px;
		}
		/*选择项设置*/
		QMenu::item:selected
		{
			 background-color:rgb(54, 54, 54);
		}
	)");
	pMenu->setFixedWidth(m_totalWidth);
	QAction* act1 = new QAction("open file", this);
	QAction* act2 = new QAction("open floder", this);
	QAction* act3 = new QAction("open net stream", this);
	connect(act1, &QAction::triggered, this, &COpenFileButton::on_openfile);
	connect(act2, &QAction::triggered, this, &COpenFileButton::on_openFloder);
	connect(act3, &QAction::triggered, this, &COpenFileButton::on_openNetStream);
	m_pArrowButton->setMenu(pMenu);
	pMenu->installEventFilter(this);

	//水平布局
	QHBoxLayout* pHLay = new QHBoxLayout(this);
	pHLay->addWidget(m_pOpenFileButton);
	pHLay->addWidget(m_pArrowButton);
	pHLay->setSpacing(3);
	pHLay->setContentsMargins(0, 0, 0, 0);
	this->setLayout(pHLay);
}
COpenFileButton::~COpenFileButton(){}

void COpenFileButton::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿
	painter.setBrush(QBrush(QColor(55, 55, 55)));
	painter.setPen(Qt::transparent);
	QRect rect = this->rect();
	painter.drawRoundedRect(rect, BUTTON_HEIGHT / 2, BUTTON_HEIGHT / 2);  //设置窗口圆角 15px

	QWidget::paintEvent(event);
}

//修正菜单弹出的坐标,让它和左侧大按钮的左下角对齐
bool COpenFileButton::eventFilter(QObject* watched, QEvent* event) {
	if (m_pOpenFileButton && m_pArrowButton) {
		if (event->type() == QEvent::Show && watched == m_pArrowButton->menu()) {
			int menuXPos = m_pOpenFileButton->pos().x();
			int menuYPos = m_pOpenFileButton->pos().y() - m_pOpenFileButton->height();
			int menuWidth = m_totalWidth;
			QPoint pos = QPoint(menuXPos, menuYPos + 1);

			m_pArrowButton->menu()->move(pos);
			return true;
		}
	}
	return false;
}

void COpenFileButton::on_openfile()
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


void COpenFileButton::on_openFloder()
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


void COpenFileButton::on_openNetStream() {
	CNetStreamDlg dlg;
	if (dlg.exec() == QDialog::Accepted)
	{
		QString strText = dlg.getUrl();
		emit sig_openUrl(strText);
	}
}