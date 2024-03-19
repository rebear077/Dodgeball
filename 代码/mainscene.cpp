#include "mainscene.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <QTime>
//#include "enemyplane.h"
#include <ctime>
#include "gameover.h"
#include "ui_gameover.h"
#include <windows.h>
#include "heart.h"
#include <iostream>
using namespace std;

int num_enemy;  //屏幕上的子弹数量
int life;   //剩余生命数量
int timer_count;    //坚持的时间
int timer_count2;   //上一次增加生命值的时间
int init_flag;  //0：游戏初始化   1：游戏结束
int timer_flag = 0; //0：定时器开始计时 1：定时器结束计时

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    printf("Init\n");
//    cout << life << "\n";
    init_flag = 0;
    timer_flag = 0;
    initScene();
    playGame();
}

MainScene::~MainScene()
{
}

void MainScene::initScene()
{
    life = 3;   //初始生命数量为3
//    timer_count = 0;
    num_enemy = 1; //屏幕上的子弹数量先从1开始
    cout << "Begining life: " << life << "\n";
//    cout << "init timer: " << timer_count << "\n";
    //init_flag = 0;
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    //设置窗口标题
    setWindowTitle(GAME_TITLE);
    //设置图标资源
    setWindowIcon(QIcon(GAME_ICON));
    //定时器设置
    m_Timer.setInterval(GAME_RATE);
    m_recorder = 0;
    h_recorder = 0;
    srand((unsigned int)time(NULL));
}

void MainScene::playGame()
{
    timer_count = 0;
    timer_count2 = 0;
    m_Timer.start();
    //监听定时器
    connect(&m_Timer,&QTimer::timeout,[=](){
        if (m_flag == 0){
            //敌机出场
            enemyToScene();
            heartToScene();
            //更新游戏中元素的坐标
            updatePosition();
            //重新绘制图片
            update();
            collisionDetection();
            heartcollisionDetection();
            if (init_flag == 1){
                this->close();
                //this->destroy();
                Gameover *gameover = new Gameover();
                gameover->show();
                timer_count = 0;
                timer_flag = 0;
                m_Timer.stop();  //一定要加stop，不然如果玩家选择“再玩一局”，那就是几个定时器并行
                timer1.stop();
                timer2.stop();
            }
        }
    });
    //QTimer *timer1 = new QTimer(this); // this 指的是当前窗口 Widget
    // 定时器的并行问题
    // 启动定时器,单位是毫秒
    if (timer_flag == 0){
        ++timer_flag;
        timer1.start(5000);
    }
    // timer发出timeout（时间到了）的信号,
    connect(&timer1,&QTimer::timeout,[=](){
        //每隔5秒给屏幕上增加一个子弹
        addEnemyNumber();
    });
    //QTimer *timer2 = new QTimer(this);
    timer2.start(1000);
    connect(&timer2,&QTimer::timeout,[=](){
        //timer_counter表示坚持的时间，以秒为单位
        timer_count++;
    });
//    if (init_flag == 1){
//        delete timer2;
//        delete timer1;
//        timer2 = NULL;
//        timer1 = NULL;
//    }
}

//void MainScene::endGame()
//{
//    num_enemy = 10;
//    this->close();
//    Gameover *gameover = new Gameover();
//    gameover->show();
//}

void MainScene::updatePosition()
{
    //更新地图坐标
    m_map.mapPosition();
    //子弹坐标计算
    for(int i = 0 ; i< num_enemy;i++)
    {
        //非空闲子弹 更新坐标
        if(m_enemys[i].m_Free == false)
        {
            m_enemys[i].updatePosition();
        }
    }

//    for(int j = 0 ; j< ENEMY_NUM;j++)
//    {
//        if (h_hearts[j].h_Free == false){
//            h_hearts[j].updatePosition();
//        }
//    }
    //加血球如果处于非空闲状态则更新坐标
    if (h_hearts.h_Free == false){
        h_hearts.updatePosition();
    }

}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY , m_map.m_map1);
    //绘制飞船
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Rocket);
    //绘制子弹
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free == false)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
        }
    }

//    for(int j = 0 ; j< ENEMY_NUM;j++)
//    {
//        if (h_hearts[j].h_Free == false){
//            painter.drawPixmap(h_hearts[j].h_X,h_hearts[j].h_Y,h_hearts[j].h_heart);
//        }
//    }
    //加血球绘制
    if (h_hearts.h_Free == false){
          painter.drawPixmap(h_hearts.h_X,h_hearts.h_Y,h_hearts.h_heart);
    }

    QPainter p(this);
    QFont font("宋体",13,75);
    p.setFont(font);
    p.setPen(QColor("#F0FFFF"));//字体颜色
    QString s = QString::number(life,10);
    s = "剩余生命值："+ s;
    QString title(s);
    int widthOfTitle = p.fontMetrics().width(title);//字符串显示的像素大小
    p.drawText(this->width()/2-widthOfTitle/2,100,title);

    QPainter p2(this);
    QFont font2("宋体",13,75);
    p2.setFont(font2);
    p2.setPen(QColor("#F0FFFF"));//字体颜色
    QString s2 = QString::number(timer_count,10);
    s2 = "您已坚持："+ s2 + "秒";
    QString title2(s2);
    int widthOfTitle2 = p2.fontMetrics().width(title2);//字符串显示的像素大小
    p2.drawText(this->width()/2-widthOfTitle2/2,50,title2);
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x() - m_hero.m_Rect.width()*0.5; //鼠标位置 - 飞机矩形的一半
    int y = event->y() - m_hero.m_Rect.height()*0.5;
    //边界检测
    if(x <= 0 )
    {
        x = 0;
    }
    if(x >= GAME_WIDTH - m_hero.m_Rect.width())
    {
        x = GAME_WIDTH - m_hero.m_Rect.width();
    }
    if(y <= 0)
    {
        y = 0;
    }
    if(y >= GAME_HEIGHT - m_hero.m_Rect.height())
    {
        y = GAME_HEIGHT - m_hero.m_Rect.height();
    }
    m_hero.setPosition(x,y);
}

void MainScene::addEnemyNumber()
{
    ++add_time;
    //如果子弹数量未达到子弹的最大值，则加1
    if (num_enemy < ENEMY_NUM){
            num_enemy = num_enemy + 1;
    }
}

//清空屏幕上的子弹
void MainScene::refreshEnemyNumber()
{
    //将所有子弹的状态都值为空闲
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        m_enemys[i].m_Free = true;
    }
    enemyToScene();
}

void MainScene::enemyToScene()
{
    m_recorder++;
    //如果未到间隔时间，则直接return
    if(m_recorder < ENEMY_INTERVAL)
    {
        return;
    }
    m_recorder = 0;
    for(int i = 0 ; i< num_enemy;i++)
    {
        if(m_enemys[i].m_Free)
        {
            //子弹空闲状态改为false
            m_enemys[i].m_Free = false;
            //设置坐标
            m_enemys[i].m_X = rand() % (GAME_WIDTH - m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y = -m_enemys[i].m_Rect.height();
            break;
        }
    }
}

void MainScene::heartToScene()
{
//    h_recorder++;
//    if(h_recorder < HEART_INTERVAL)
//    {
//        return;
//    }
//    h_recorder = 0;
    //30秒后开始出现加血球，因为开始时子弹数量太少，比较简单
    //每一次加血球的出现都与上一次加血的时间隔15秒的倍数再出现
    if (timer_count >= 30 && (timer_count - timer_count2) % 15 == 0 && timer_count - timer_count2 >= 15){
        if(h_hearts.h_Free)
        {
            //子弹空闲状态改为false
            h_hearts.h_Free = false;
            //设置坐标
            h_hearts.h_X = rand() % (GAME_WIDTH - h_hearts.h_Rect.width());
            h_hearts.h_Y = -h_hearts.h_Rect.height();
        }
    }

    else{
        return ;
    }

//    h_hearts[0].h_Free = false;
//    //设置坐标
//    h_hearts[0].h_X = rand() % (GAME_WIDTH - h_hearts[0].h_Rect.width());
//    h_hearts[0].h_Y = -h_hearts[0].h_Rect.height();
//    for(int i = 0 ; i< ENEMY_NUM;i++)
//    {
//        if(h_hearts[i].h_Free)
//        {
//            //敌机空闲状态改为false
//            h_hearts[i].h_Free = false;
//            //设置坐标
//            h_hearts[i].h_X = rand() % (GAME_WIDTH - h_hearts[i].h_Rect.width());
//            h_hearts[i].h_Y = -h_hearts[i].h_Rect.height();
//        }
//    }


}

void MainScene::collisionDetection()
{
    //遍历所有非空闲的子弹
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (m_enemys[i].m_Free)
        {
            //空闲子弹 跳转下一次循环
            continue;
        }
        //如果子弹矩形框和飞船矩形框相交，发生碰撞，则变为空闲状态即可
        if (m_enemys[i].m_Rect.intersects(m_hero.m_Rect))
        {
            --life;
            cout << "Current Live: "  << life <<"\n";
            cout << "Spend time: " << timer_count << "\n";
            timer_count2 = timer_count - 5;
            h_hearts.h_Free = true; //如果加血球不清零的话，玩家可以通过主动撞击子弹清空屏幕，并立即获取生命值，从而无限游玩
            if (life == 0){
                life = -1;
//                printf("1\n");
//                cout << life <<"\n";
                init_flag = 1;
                break;
                //endGame();
            }
            //清空屏幕上的子弹
            refreshEnemyNumber();
        }
    }
}

void MainScene::heartcollisionDetection()
{
    if (h_hearts.h_Free)
    {
        return ;
    }
    //如果加血球矩形框和飞船矩形框相交，发生碰撞，同时变为空闲状态即可
    if (h_hearts.h_Rect.intersects(m_hero.m_Rect))
    {
        timer_count2 = timer_count;
        h_hearts.h_Free = true;
        ++life;
        cout << "Current Live: "  << life <<"\n";
        cout << "Spend time: " << timer_count << "\n";
    }
}

