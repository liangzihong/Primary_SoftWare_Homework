#ifndef ATOM_H
#define ATOM_H


#define RADIUS_Nuclear 15
#define RADIUS_Neutron 8

class Atom{
protected:
    int type;
    int x;
    int y;
public:
    Atom(int type,int x,int y) {
        this->type=type;
        this->x=x;
        this->y=y;
    }
    int getType(){return type;}
    int getX(){return x;}
    int getY(){return y;}
};

#endif // ATOM_H
