#include "mypushbuttom.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>
MyPushButtom::MyPushButtom(QString normalImg,QString pressedImg,QWidget *parent)
    : QPushButton(parent)
    , mNormalImg(normalImg)
    , mPressedImg(pressedImg)
{
    mStat = Normal;
}

void MyPushButtom::moveDown()
{
    //1位置大小属性发生变化
    //2给定开始的位置大小属性
    //3给定结束的位置大小属性
    //4给定速度，给定动画时长
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButtom::moveUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButtom::paintEvent(QPaintEvent *ev)
{
    //绘制按钮的图片
    QPainter painter(this);
    QPixmap pix;
    if(mStat == Normal)
        pix.load(mNormalImg);
    if(mStat == Pressed)
        pix.load(mPressedImg);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //绘制按钮的文字
    painter.drawText(0,0,this->width(),this->height(),
                     Qt::AlignHCenter|Qt::AlignVCenter,this->text());

}

void MyPushButtom::mousePressEvent(QMouseEvent *e)
{
    //鼠标按下的时候状态切到Pressed
    this->mStat == Pressed;
    update();
    //保证信号和槽功能
    QPushButton::mousePressEvent(e);
}

void MyPushButtom::mouseReleaseEvent(QMouseEvent *e)
{
    //鼠标按下的时候状态切到Normal
    this->mStat == Normal;
    update();
    //保证信号和槽功能
    QPushButton::mouseReleaseEvent(e);
}





