#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QPainter>

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    //设置窗口大小、标题等
    setFixedSize(320,588);
    setWindowTitle("翻金币");
    setWindowIcon(QIcon(":/res/Coin0001.png"));
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

void MyMainWindow::paintEvent(QPaintEvent *event)
{
    //画家对象
    QPainter painter(this);
    //背景图片的pixmap
    QPixmap pix(":/res/MenuSceneBg.png");
    //在0,0坐标开始绘制图片
    //这里第三、四个参数指定宽高可以让图片根据窗口大小进行缩放
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

