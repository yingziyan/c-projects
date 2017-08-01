#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>

#include "base.h"
#include "map.h"

using namespace std;

Map::Map(string mapNumber)
{
    string filename = "maps/" + mapNumber;  
    ifstream in(filename.c_str());

    string line;
    if(in.is_open())
        getline(in, line);

    // 初始化地图信息
    stringstream ss(line);
    ss >> m_iMapSize >> m_coorEntrance.x >> m_coorEntrance.y >> m_coorExit.x >> m_coorExit.y;

    // 初始化地图
    for (int i = 0; i < m_iMapSize; i ++)
    {
        getline(in, line);
        m_strMap = m_strMap + line + "\n";
    }

}
Map::~Map()
{}

void Map::printMap()
{
    system("clear");
    cout << "[[    @skyasker " << right << setw((m_iMapSize - 8) * 2) << " At: 2017.08.01    ]]" << endl << endl;
    cout << m_strMap;
}

position Map::getEntrance()
{
    return m_coorEntrance;
}

bool Map::isRoad(position pos)
{
    if (pos.x < 0 || pos.x > (m_iMapSize - 1) || pos.y < 0 || pos.y > (m_iMapSize - 1))
        return false;
    if (NON_BLOCK == m_strMap.substr(pos.x * (m_iMapSize * BLOCK_WIDTH + 1) + BLOCK_WIDTH * pos.y, BLOCK_WIDTH))
        return true;
    else
        return false;
}

bool Map::isExit(position pos)
{
    if (pos.x == m_coorExit.x && pos.y == m_coorExit.y) return true;
    return false;
}

void Map::replace(position pos, string block)
{
    m_strMap = m_strMap.replace(pos.x * (m_iMapSize * BLOCK_WIDTH + 1) + BLOCK_WIDTH * pos.y, BLOCK_WIDTH, block);
}


