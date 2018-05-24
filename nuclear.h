#ifndef NUCLEAR_H
#define NUCLEAR_H

#include"atom.h"
#include"neutron.h"
#include<cmath>

class Nuclear:public Atom{

public:
    Nuclear(int x,int y):Atom(1,x,y){}



    //首先声明的是，只有当中子的中心在原子核内部才算是发生撞击
    bool isHitByNeutron(Neutron neutron)
    {
        int neux=neutron.getX();
        int neuy=neutron.getY();

        if( abs(x-neux)<=RADIUS_Nuclear && abs(y-neuy)<=RADIUS_Nuclear )
        {
            return true;
        }
        return false;
    }



};

#endif // NUCLEAR_H
