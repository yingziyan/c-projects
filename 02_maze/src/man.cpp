#include <iostream>
#include <string>

#include "man.h"

using namespace std;


Man::Man(Map &map):m_coorPos(map.getEntrance())
{
    // 根据地图入口位置将小人画上地图
    map.replace(m_coorPos, MAN_BLOCK);
    m_uSteps = 0;
}


Man::~Man()
{}


void Man::move(Map &map, int dir)
{
    position nextPos;
    if (UP == dir || DOWN == dir)
    {
         nextPos.x = m_coorPos.x + dir;
         nextPos.y = m_coorPos.y;
    }

    if (LEFT == dir || RIGHT == dir)
    {
         nextPos.x = m_coorPos.x;
         nextPos.y = m_coorPos.y + (dir % 2);
    }

    if (map.isRoad(nextPos))
    {
        map.replace(nextPos, MAN_BLOCK);
        map.replace(m_coorPos, NON_BLOCK);
        m_coorPos = nextPos;
        setSteps();
        map.printMap();
    }

}


void Man::setSteps()
{
    ++ m_uSteps;
}


unsigned int Man::getSteps()
{
    return m_uSteps;
}


bool Man::isOut(Map &map)
{
    if (map.isExit(m_coorPos)) return true;
    return false;
}
