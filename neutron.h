#ifndef NEUTRON_H
#define NEUTRON_H

#include"atom.h"
#include"nuclear.h"
#include<math.h>
#include<vector>
using namespace std;

#define PI 3.14159265
#define NORMAL_SPEED 3
#define SPEED_OF_TIME 3
#define XLEFT_LIMIT 0
#define XRIGHT_LIMIT 1000
#define YDOWN_LIMIT 700
#define YUP_LIMIT 0


class Neutron:public Atom
{
private:
    double angle;
    int speed;
    int collisionTag;    //用来记作上一次碰撞是哪一面，不能出现 撞完弹走之后还在撞
public:


    Neutron(int x,int y):Atom(0,x,y){ collisionTag=0;}

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
                while(abs(deltax)<speed)
                    deltax=deltax*2;
            }
            else if(tmpx<0.05 && tmpy>=0.05){
                deltax=0;
                while(abs(deltay)<speed)
                    deltay=deltay*2;
            }

        }

        //TODO:把deltax和deltay变成按比例

        x=x+deltax*speed;
        y=y+deltay*speed;

        collision();

    }
    bool isHitNuclear( vector<Nuclear> nuclear);
    void paintExplosion( vector<Nuclear> nuclear);
    void splitThree();


    //碰撞边界的话，直接改变angle
    void collision()
    {

        if( y-RADIUS_Neutron <= YUP_LIMIT &&  x-RADIUS_Neutron<=XLEFT_LIMIT ||
                y-RADIUS_Neutron <= YUP_LIMIT && x+RADIUS_Neutron>= XRIGHT_LIMIT ||
                y+RADIUS_Neutron >=YDOWN_LIMIT && x-RADIUS_Neutron<=XLEFT_LIMIT ||
                y+RADIUS_Neutron >=YDOWN_LIMIT && x+RADIUS_Neutron>= XRIGHT_LIMIT)
        {
                 angle=angle+180;
        }
        //碰到y的up边界  y==0
        else if( y-RADIUS_Neutron <= YUP_LIMIT )
        {
            if(collisionTag!=1) {
                angle= 360-angle;
                collisionTag=1;
            }
        }
        //碰到y的down边界  y==700
        else if( y+RADIUS_Neutron >=YDOWN_LIMIT)
        {
            if(collisionTag!=2){
                angle=360-angle;
                collisionTag=2;
            }
        }
        //碰到x的left边界  x==0
        else if( x-RADIUS_Neutron<=XLEFT_LIMIT)
        {
            if(collisionTag!=3){
                angle=540-angle;
                collisionTag=3;
            }
        }
        //碰到x的right边界   x==1000
        else if( x+RADIUS_Neutron>= XRIGHT_LIMIT)
        {
            if(collisionTag!=4){
                angle=540-angle;
                collisionTag=4;
            }
        }

        while(angle>360)
            angle=angle-360;
        while(angle<=0)
            angle=angle+360;


    }


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
