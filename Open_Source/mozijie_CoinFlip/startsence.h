#ifndef STARTSENCE_H
#define STARTSENCE_H

#include <QMainWindow>
#include "mymainwindow.h"
#include "selectscene.h"

class StartSence : public MyMainWindow
{
    Q_OBJECT
public:
    explicit StartSence(QWidget *parent = nullptr);

private:
    SelectScene mSelectScene;

signals:

};

#endif // STARTSENCE_H
