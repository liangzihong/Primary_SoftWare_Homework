#ifndef NUCLEAR_H
#define NUCLEAR_H

#include"atom.h"
#include"neutron.h"

class Nuclear:public Atom{

public:
    Nuclear(int x,int y):Atom(1,x,y){}

    //bool isHitByNeutron(Neutron neutron);
};

#endif // NUCLEAR_H
