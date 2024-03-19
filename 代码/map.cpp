#include "map.h"
#include "config.h"

Map::Map()
{
    m_map1.load(MAP_PATH);
    m_map1_posY = -GAME_HEIGHT;
}

void Map::mapPosition()
{
    m_map1_posY = 0;
}
