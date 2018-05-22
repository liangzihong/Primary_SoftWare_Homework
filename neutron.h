#ifndef NEUTRON_H
#define NEUTRON_H

#include"atom.h"
#include"nuclear.h"

class Neutron:public Atom
{
private:
    int angle;
public:


    Neutron(int x,int y):Atom(0,x,y){}
    void move();
    bool isHitNuclear( Nuclear nuclear);
    void paintExplosion(Nuclear nuclear);
    void splitThree();

    int getAngle();
    void setAngle();
};


#endif // NEUTRON_H
