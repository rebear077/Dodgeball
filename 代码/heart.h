#ifndef HEART_H
#define HEART_H
#include <QPixmap>

class Heart
{
public:
    Heart();
    //更新坐标
    void updatePosition();

public:
    //加血球资源对象
    QPixmap h_heart;
    //位置
    int h_X;
    int h_Y;

    float h_VX;
    float h_VY;

    //加血球的矩形边框（碰撞检测）
    QRect h_Rect;
    //状态
    bool h_Free;
    //速度
    int h_Speed;
};

#endif // HEART_H
