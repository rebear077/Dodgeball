#ifndef MAP_H
#define MAP_H
#include <QPixmap>

class Map
{
public:
    Map();
    void mapPosition();

public:
    //地图图片对象
    QPixmap m_map1;
    //地图Y轴坐标
    int m_map1_posY;
};

#endif // MAP_H
