#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QTimer>
#include "map.h"
#include "rocket.h"
#include "config.h"
#include "enemyplane.h"
#include "heart.h"

extern int timer_count;

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //初始化界面
    void initScene();
    //启动游戏 用于启动定时器对象
    void playGame();
    //更新坐标
    void updatePosition();
    //绘图事件
    void paintEvent(QPaintEvent *event);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
    //增加子弹数量
    void addEnemyNumber();
    //清空当前屏幕上的子弹
    void refreshEnemyNumber();
    //背景对象
    Map m_map;
    //定时器
    QTimer m_Timer;
    QTimer timer1;
    QTimer timer2;
    //飞船t对象
    Rocket m_hero;
    //子弹出场
    void enemyToScene();
    //加血球对象出场
    void heartToScene();
    //子弹数组
    EnemyPlane m_enemys[ENEMY_NUM];
    //Heart h_hearts[ENEMY_NUM];
    Heart h_hearts;
    //子弹出场间隔记录
    int m_recorder;
    //子弹与飞船碰撞检测
    void collisionDetection();
    //加血球与飞船碰撞检测
    void heartcollisionDetection();
    //游戏结束
    void endGame();
    int m_flag = 0;
    //计时
    //int timer_count = 0;
    int add_time = 0;
    //生命值出场间隔记录
    int h_recorder;
};
#endif // MAINSCENE_H
