#include "rocket.h"
#include "config.h"

Rocket::Rocket()
{
    //初始化加载飞船图片资源
    m_Rocket.load(HERO_PATH);
    //初始化坐标
    m_X = GAME_WIDTH * 0.5 - m_Rocket.width()*0.5;
    m_Y = GAME_HEIGHT - m_Rocket.height();
    //初始化矩形框
    m_Rect.setWidth(m_Rocket.width());
    m_Rect.setHeight(m_Rocket.height());
    m_Rect.moveTo(m_X,m_Y);

    m_RktFree = true;
}

void Rocket::setPosition(int x, int y)
{
//    if (m_RktFree){
        m_X = x;
        m_Y = y;
        m_Rect.moveTo(m_X,m_Y);
//    }
}
