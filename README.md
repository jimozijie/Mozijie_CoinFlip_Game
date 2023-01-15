# Mozijie_CoinFlip_Game
这是一个基于QT框架开发的翻金币游戏，如果你想快速入手QT开发，可以将该项目作为你的QT入门项目。

#### 若项目对您有帮助，请给作者一个Starred吧，万分感谢！！

#### 项目作者：即墨子杰 同时也是B站的一位UP主（B站与GitHub同名），如果大家对力扣刷题、算法、MySQL感兴趣，欢迎关注！！

该项目提供游戏安装包（文件夹：软件安装包）和游戏源代码（文件夹：Open_Source）。

如果你有QT运行环境，您可以尝试下载源代码运行。如若没有QT运行环境，您也可以下载代码研究，并且可以打开软件安装包中的 Mozijie_CoinFlip_Game.exe （游戏文件）愉快的玩耍。

### 部分源码展示
#### playscene.cpp
```C++
#include "playscene.h"
#include "mypushbuttom.h"
#include <QPainter>
#include <QMenuBar>
#include <QLabel>
#include <coinbutton.h>
#include <dataconfig.h>
#include <QTimer>
#include <QMessageBox>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int level,QWidget *parent) : MyMainWindow(parent)
{
    mHasWin = false;
    //返回按钮
    MyPushButtom *btnBack = new MyPushButtom(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    btnBack->resize(72,32);
    connect(btnBack,&QPushButton::clicked,this,&PlayScene::backBtnClicked);
    btnBack->move(this->width()-btnBack->width(),this->height()- btnBack->height());

    //添加左下角的label
    QLabel *label = new QLabel(this);
    label->resize(150,50);
    label->setText(QString("Level:%1").arg(level));
    //设置字体
    label->setFont(QFont("华文新魏",20));
    //移动到左下角
    label->move(30,this->height()-label->height());

    const int colWidth = 50;
    const int rowHeight = 50;
    const int xOffset = 57;
    const int yOffset = 200;

    //取出第几关的二位数组数据
    dataConfig data;
    QVector<QVector<int> >  dataArray = data.mData[level];

    //16个硬币按钮
    for (int row = 0;row < 4;++row)
    {
        for(int col = 0;col < 4;++col)
        {
            CoinButton *btn = new CoinButton(this);
            //存储按钮到数组第几行第几列
            mCoins[row][col] = btn;
            //x 坐标 = 列数 * 列宽 + x偏移
            //y 坐标 = 行数 * 行高 + y偏移
            int x = col *colWidth+xOffset;
            int y = row * rowHeight+yOffset;
            btn->setGeometry(x,y,50,50);

            //设置row行col列的值，从dataConfig的数据中获取
            btn->setStat(dataArray[row][col]);

            connect(btn,&CoinButton::clicked,[=](){
                //每次点击硬币的时候就改变状态，状态置反
                //btn->flip();
                this->filp(row,col);
            });
        }
    }
}

void PlayScene::filp(int row, int col)
{
    //如果胜利了，就直接返回
    if(mHasWin)
    {
        return;
    }
    this->mCoins[row][col]->flip();
    //翻金币的音效
    QSound::play(":/res/ConFlipSound.wav");

    //延时翻动其他硬币
    QTimer::singleShot(250,[=](){
        //翻动上下左右的硬币
        if(row+1<4)
            this->mCoins[row+1][col]->flip();
        if(row-1>=0)
            this->mCoins[row-1][col]->flip();
        if(col+1<4)
            this->mCoins[row][col+1]->flip();
        if(col-1>=0)
            this->mCoins[row][col-1]->flip();
        //判断游戏是否胜利
        this->judgeWin();
    });


}

void PlayScene::judgeWin()
{
    //16个硬币按钮判断状态都是1
    for (int row = 0;row < 4;++row)
    {
        for(int col = 0;col < 4;++col)
        {
            //判断某个硬币是银币
            if(!this->mCoins[row][col]->stat())
            {
                //只要有一个是银币，就返回，游戏继续
                return ;
            }
        }
    }
    //所有都是金币的情况下游戏结束
    mHasWin = true;

    //播放胜利音效
    QSound::play(":/res/LevelWinSound.wav");

//    QMessageBox::information(this,"恭喜","你已经胜利了");
    //播放胜利动画
    QLabel *labelWin = new QLabel(this);
    QPixmap pix = QPixmap(":/res/LevelCompletedDialogBg.png");
    labelWin->setPixmap(pix);
    labelWin->resize(pix.size());
    labelWin->move((this->width()-labelWin->width())/2,-labelWin->height());
    labelWin->show();

    QPropertyAnimation *animation = new QPropertyAnimation(labelWin,"geometry",this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x(),labelWin->y()+100
                                 ,labelWin->width(),labelWin->height()));
    animation->setDuration(1000);
    //设置动画的运动曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //动画播放完自动删除动画对象
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.translate(0,this->menuBar()->height());
    //背景图片的pixmap
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    //在0,0坐标开始绘制图片
    //这里第三、四个参数指定宽高可以让图片根据窗口大小进行缩放
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()/2,pix.height()/2);
    painter.drawPixmap(0,0,pix);
}

```


### 部分游戏截图
#### 开始场景

<img src="https://user-images.githubusercontent.com/106757368/212527599-3a4347c2-7726-43f0-a5b9-8dc707b04a8c.png" width="200px">

#### 关卡场景

<img src="https://user-images.githubusercontent.com/106757368/212527593-e9e8a643-b79f-48a1-9471-908c10d5af69.png" width="200px">


#### 游戏场景—第一关

<img src="https://user-images.githubusercontent.com/106757368/212527602-cd9940bc-8edc-419e-be80-9e76181c1760.png" width="200px">

目前只发布了该游戏的第一代版本，如若后续有更新，将会以新文件夹的形式加入库中。




