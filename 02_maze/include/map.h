#ifndef MAP_H
#define MAP_H

#include <string>
#include "base.h"

using namespace std;

class Map
{
public:
    Map(string);
    ~Map();
    void printMap();
    position getEntrance();
    bool isRoad(position);
    bool isExit(position);
    void replace(position, string);
private:
    string m_strMap;
    int m_iMapSize;
    position m_coorEntrance;
    position m_coorExit;
};


#endif