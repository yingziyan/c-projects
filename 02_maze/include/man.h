#ifndef MAN_H
#define MAN_H

#include "base.h"
#include "map.h"

class Man
{
public:
    Man(Map &);
    ~Man();
    bool isOut(Map &);
    void move(Map &, int);
    inline void setSteps();
    unsigned int getSteps();
private:
    position m_coorPos;
    unsigned int m_uSteps;
};


#endif