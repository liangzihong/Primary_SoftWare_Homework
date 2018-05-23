#ifndef NEUTRON_H
#define NEUTRON_H

#include"atom.h"
#include"nuclear.h"
#include<math.h>
#include<vector>
using namespace std;

#define PI 3.14159265
#define NORMAL_SPEED 2

class Neutron:public Atom
{
private:
    double angle;
    int speed;
public:


    Neutron(int x,int y):Atom(0,x,y){}
    void move()
    {
        speed=NORMAL_SPEED;
        int deltay= speed * sin(angle * PI /180);
        int deltax= speed * cos(angle * PI /180);

        int tmpy=abs(deltay);
        int tmpx=abs(deltax);
        double k;
        if(tmpy>tmpx)
        {
            k=(double)tmpy/tmpx;
        }
        else{
            k=(double)tmpx/tmpy;
        }


        //TODO:把deltax和deltay变成按比例

        x=x+deltax;
        y=y+deltay;

    }
    bool isHitNuclear( vector<Nuclear> nuclear);
    void paintExplosion( vector<Nuclear> nuclear);
    void splitThree();




    int getAngle(){return angle;}
    void setAngle(int angle){ this->angle=angle;}
    void setAngle(int arrowx,int arrowy)
    {
        double k= double(arrowy-y)/double(arrowx-x);
        double sita = atan(k) * 180/PI;


        if(sita<0){
            if(arrowy>y)
                sita=180+sita;
            else
                sita=sita;
        }
        else if(sita>0){
            if(arrowy<y)
                sita=sita+180;
        }





        angle=sita;
    }

    int getSpeed(){return speed;}
    void setSpeed(int speed){this->speed=speed;}
};


#endif // NEUTRON_H
