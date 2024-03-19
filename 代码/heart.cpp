#include "heart.h"
#include "config.h"
#include <conio.h>
#include <math.h>

Heart::Heart()
{
    //加血球对象资源加载
    h_heart.load(HEART_PATH);
    //加血球对象位置
    h_X = 0;
    h_Y = 0;
    h_VY = 0;
    while(h_VY == 0){
        float angle = (rand() / double(RAND_MAX) - 0.5) * 0.9 * PI;
        float scalar = 2 * rand() / double(RAND_MAX) + 2;
        h_VX = scalar * sin(angle);
        h_VY = scalar * cos(angle);
    }

    //加血球对象状态
    h_Free = true;
    //加血球对象速度
    h_Speed = ENEMY_SPEED;
    //加血球对象矩形
    h_Rect.setWidth(h_heart.width() * 3 / 5);
    h_Rect.setHeight(h_heart.height() * 3 / 5);
    h_Rect.moveTo(h_X,h_Y);
}

void Heart::updatePosition()
{
    //空闲状态，不计算坐标
    if(h_Free)
    {
        return;
    }
    //更改行进间的轨迹
    h_X += h_VX;
    h_Y += h_VY;
//    if (h_VY <= 0){
//        h_Y += 0.01;
//    }
//    else{
//        h_Y += h_VY;
//    }
    if (h_X <= 0 || h_X >= GAME_WIDTH){
        h_VX = -h_VX;
    }
    h_Rect.moveTo(h_X,h_Y);
    //加血球对象出界后状态返回为true
    if(h_Y >= GAME_HEIGHT)
    {
        h_Free = true;
    }
}
