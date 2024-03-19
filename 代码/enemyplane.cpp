#include "enemyplane.h"
#include "config.h"
#include <conio.h>
#include <math.h>
#include <iostream>
using namespace std;

EnemyPlane::EnemyPlane()
{
    //子弹资源加载
    m_enemy.load(ENEMY_PATH);
    //子弹位置
    m_X = 0;
    m_Y = 0;
    m_VY = 0;
    //Y轴速度小于1会出现“在顶部平移的子弹”
    while(m_VY <= 1){
        float angle = (rand() / double(RAND_MAX) - 0.5) * 0.9 * PI;
        float scalar = 2 * rand() / double(RAND_MAX) + 2;
        m_VX = scalar * sin(angle);
        m_VY = scalar * cos(angle);
    }

    //子弹状态
    m_Free = true;
    //子弹速度
    m_Speed = ENEMY_SPEED;
    //子弹矩形
    m_Rect.setWidth(m_enemy.width() * 3 / 5);
    m_Rect.setHeight(m_enemy.height() * 3 / 5);
    m_Rect.moveTo(m_X,m_Y);
}

void EnemyPlane::updatePosition()
{
    //空闲状态，不计算坐标
    if(m_Free)
    {
        return;
    }
    //更改行进间的轨迹
    m_X += m_VX;
    m_Y += m_VY;
//    cout << "Speed X: "  << m_VX;
//    cout << "Speed Y: " << m_VY << "\n";
//    if (m_VY == 0){
//        m_Y += 0.01;
//    }
//    else{
//        m_Y += m_VY;
//    }
    if (m_X <= 0 || m_X >= GAME_WIDTH){
        m_VX = -m_VX;
    }
    m_Rect.moveTo(m_X,m_Y);
    //子弹出界后状态返回为true
    if(m_Y >= GAME_HEIGHT)
    {
        m_Free = true;
    }
}
