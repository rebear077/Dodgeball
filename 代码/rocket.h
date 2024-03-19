#ifndef ROCKET_H
#define ROCKET_H
#include <QPixmap>

class Rocket
{
public:
    Rocket();
    void setPosition(int x, int y);

public:
    QPixmap m_Rocket;
    //飞船坐标
    int m_X;
    int m_Y;
    //飞船矩形边框
    QRect m_Rect;

    bool m_RktFree;
};

#endif // ROCKET_H
