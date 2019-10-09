#ifndef MAP_H
#define MAP_H

#include <QLabel>
#include <vector>
#include "player.h"

//zamiana std::..... na Array2D, zdefiniowany wlasny typ

template<class T>
using Array2D = class std::vector<std::vector<T>>;

//typedef std::vector<std::vector<T>> Array2D;


class Map
{
public:

    Map();

    void setMap(Array2D<uint8_t> map);
    Array2D<uint8_t> getMap();

    uint8_t getMapWidth();
    uint8_t getMapHeight();


    bool isHigh(uint8_t x, uint8_t y);

private:
    Array2D<uint8_t> m_boardArray;
};

#endif // MAP_H
