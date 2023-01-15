#include "coinbutton.h"
#include <QPainter>

CoinButton::CoinButton(QWidget *parent) : QPushButton(parent)
{
    //初始状态设置
    this->setStat(0);

    //设置按钮不规则样式，去掉边框
    this->setStyleSheet("QPushButton{border:None;}");

    //动画的定时器信号和槽实现
    connect(&this->mTimer,&QTimer::timeout,[=](){
       if(this->mStat)
       {
           //银币翻金币
           this->mFrame--;
       }
       else
       {
           //金币翻银币
           this->mFrame++;
       }
       //加载相应帧的图片
       QString frameName =  QString(":/res/Coin000%1.png").arg(this->mFrame);
       this->setIcon(QIcon(frameName));
       //停止计时器
       if(this->mFrame == 8||this->mFrame == 1)
       {
           this->mTimer.stop();
       }
    });
}

int CoinButton::stat() const
{
    return mStat;
}

void CoinButton::setStat(int stat)
{
    mStat = stat;
    if(this->mStat)
    {
        //金币
        this->setIcon(QIcon(":/res/Coin0001.png"));
    }
    else
    {
        //银币
        this->setIcon(QIcon(":/res/Coin0008.png"));
    }
    //设置硬币大小
    this->setIconSize(this->size());



}

void CoinButton::setStatWithAnimation(int stat)
{
    this->mStat = stat;
    if(this->mStat)
    {
        //mStat == 1 ，表示银币翻金币
        this->mFrame = 8;

    }
    else
    {
        //金币翻银币的过程
        this->mFrame = 1;
    }
    this->mTimer.start(30);

}

void CoinButton::flip()
{
    //翻转，状态置反
    this->setStatWithAnimation(!this->stat());
}

void CoinButton::paintEvent(QPaintEvent *ev)
{
    //绘制按钮的图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/BoardNode.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //调用父类的paintEvent
    QPushButton::paintEvent(ev);
}






















