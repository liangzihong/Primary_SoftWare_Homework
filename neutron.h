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
        double deltay= sin(angle * PI /180);
        double deltax= cos(angle * PI /180);

        double tmpy=abs(deltay);
        double tmpx=abs(deltax);
        double k;


        //判断
        if(tmpy>=0.05 && tmpx>=0.05) {
            if(tmpy>tmpx)
            {
                k=(double)tmpy/tmpx;
                deltax=deltax / tmpx;     //绝对值小的那个变成 符号不变的单位1
                deltay=deltay/tmpy * k; //绝对值大的那个变成符号不变的 单位k
            }
            else{
                k=(double)tmpx/tmpy;
                deltay=deltay/tmpy;
                deltax=deltax/ tmpx *k;
            }
        }


        else{
            if(tmpy<0.05 && tmpx>=0.05) {
                deltay=0;
                while(abs(deltax)<2)
                    deltax=deltax*2;
            }
            else if(tmpx<0.05 && tmpy>=0.05){
                deltax=0;
                while(abs(deltay)<2)
                    deltay=deltay*2;
            }

        }

        //TODO:把deltax和deltay变成按比例

        x=x+deltax*speed;
        y=y+deltay*speed;

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
