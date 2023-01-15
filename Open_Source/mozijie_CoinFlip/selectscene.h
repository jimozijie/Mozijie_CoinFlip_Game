#ifndef SELCETSCENE_H
#define SELCETSCENE_H

#include <QMainWindow>
#include "mymainwindow.h"

class SelectScene : public MyMainWindow
{
    Q_OBJECT
public:
    explicit SelectScene(QWidget *parent = nullptr);

signals:
    void backBtnClicked();

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // SELCETSCENE_H
