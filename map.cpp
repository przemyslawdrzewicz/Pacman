#include "map.h"

Map::Map()
{
}

void Map::setMap(Array2D<uint8_t> map)
{
    m_boardArray = map;
}

Array2D<uint8_t> Map::getMap()
{
    return m_boardArray;
}

bool Map::isHigh(uint8_t x, uint8_t y)
{
    return static_cast<bool>(m_boardArray[y][x]);
}


uint8_t Map::getMapWidth()
{
    return m_boardArray[0].size();
}
uint8_t Map::getMapHeight()
{
    return m_boardArray.size();
}
