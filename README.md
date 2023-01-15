# Mozijie_CoinFlip_Game
这是一个基于QT框架开发的翻金币游戏，如果你想快速入手QT开发，可以将该项目作为你的QT入门项目。

#### 若项目对您有帮助，请给作者一个Starred吧，万分感谢！！

#### 项目作者：即墨子杰 同时也是B站的一位UP主（B站与GitHub同名），如果大家对力扣刷题、算法、MySQL感兴趣，欢迎关注！！

该项目提供游戏安装包（文件夹：软件安装包）和游戏源代码（文件夹：Open_Source）。

如果你有QT运行环境，您可以尝试下载源代码运行。如若没有QT运行环境，您也可以下载代码研究，并且可以打开软件安装包中的 Mozijie_CoinFlip_Game.exe （游戏文件）愉快的玩耍。

### 部分源码展示
#### selectscene.cpp
```C++
#include "selectscene.h"
#include<QPushButton>
#include <QPainter>
#include <QMenuBar>
#include <mypushbuttom.h>
#include "playscene.h"
#include <QSound>
SelectScene::SelectScene(QWidget *parent) : MyMainWindow(parent)
{
    //返回按钮
    MyPushButtom *btnBack = new MyPushButtom(":/res/BackButton.png",":/res/BackButtonSelected.png",this);

    btnBack->resize(72,32);

    connect(btnBack,&QPushButton::clicked,this,&SelectScene::backBtnClicked);

    btnBack->move(this->width()-btnBack->width(),this->height()- btnBack->height());
    //关卡按钮20个
    const int colWidth = 70;
    const int rowHeight = 70;
    //x y 偏移
    const int xOffset = 25;
    const int yOffset = 130;

    for (int i = 0;i<20;++i)
    {
      MyPushButtom *btn = new MyPushButtom(":/res/LevelIcon.png",":/res/LevelIcon.png",this);
      btn->setText(QString::number(i+1));
      //排列
      //行 i / 4
      //列 i % 4

      int row = i/4;
      int col = i%4;
      //x 坐标 = 列数 * 列宽 + x偏移
      //y 坐标 = 行数 * 行高 + y偏移
      int x = col *colWidth+xOffset;
      int y = row * rowHeight+yOffset;
      btn->resize(57,57);
      btn->move(x,y);

      connect(btn,&MyPushButtom::clicked,[=](){
        QSound::play(":/res/TapButtonSound.wav");

        //点击关卡按钮后打开一个新的场景PlayScene
        PlayScene *playScene = new PlayScene(i+1);
        //设置playScene关闭的时候自动释放
        playScene->setAttribute(Qt::WA_DeleteOnClose);
        playScene->move(this->pos());
        playScene->show();
        this->hide();

        connect(playScene,&PlayScene::backBtnClicked,[=](){
           QSound::play(":/res/BackButtonSound.wav");
           this->move(playScene->pos());
           this->show();
           //使用关闭
           playScene->close();
        });
      });
    };
}

void SelectScene::paintEvent(QPaintEvent *event)
{
    //画家对象
    QPainter painter(this);
    painter.translate(0,this->menuBar()->height());
    //背景图片的pixmap
    QPixmap pix(":/res/OtherSceneBg.png");
    //在0,0坐标开始绘制图片
    //这里第三、四个参数指定宽高可以让图片根据窗口大小进行缩放
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
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




