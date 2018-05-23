#ifndef ABOUT_MATH_H
#define ABOUT_MATH_H

#include"atom.h"
#include"neutron.h"
#include"nuclear.h"
#include"view_paintlabel.h"
#include<cmath>
#include<vector>
using namespace std;


class About_Math{


public:

    /**
     * @brief isOverlapping
     * @param neutron
     * @param nuclear
     * @return
     *
     * 判断中子与原子核有没有覆盖，用在初始化中子的时候检阅。
     */
    static bool isOverlapping(Neutron neutron, vector<Atom> nuclears)
    {
        for( int i=0;i < nuclears.size();i++){
            int neux=neutron.getX();
            int neuy=neutron.getY();

            int nux=nuclears[i].getX();
            int nuy=nuclears[i].getY();

            //如果中子在原子核内部
            if(  abs(neux-nux)<=RADIUS_Nuclear && abs(neuy-nuy)<=RADIUS_Nuclear)
                return true;
        }
        return false;
    }
};




#endif // ABOUT_MATH_H
