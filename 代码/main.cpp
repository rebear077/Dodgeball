#include "mainscene.h"
#include "config.h"
#include <QApplication>
#include <QResource>
#include "startgame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainScene w;
    Startgame w;
    //注册外部的二进制资源文件
    QResource::registerResource(GAME_RES_PATH);
    w.show();
    return a.exec();
}
