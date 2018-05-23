#ifndef VIEW_PAINTLABEL_H
#define VIEW_PAINTLABEL_H


#define RADIUS_Nuclear 15
#define RADIUS_Neutron 8

#include<QLabel>
#include<QPainter>
#include<vector>
#include<QMessageBox>
#include<about_math.h>
#include"atom.h"
#include"neutron.h"
#include"nuclear.h"
using namespace std;



class PaintLabel: public QLabel
{
    Q_OBJECT
public:
    explicit PaintLabel(QWidget*parent=0);
    void paintEvent(QPaintEvent* event);


    //void paint_Explosion(double x, double y);
    //void paint_NeutronArrow(double startx,double starty,double endx,double endy);


    void setReadyToPaintNeutron(bool is){ readyToPaintNeutron=is; }
    void setReadyToPaintNuclear(bool is){ readyToPaintNuclear=is; }
    void setReadyToPaintArrow(bool is){ readyToPaintArrow=is; }
    void setArrowTox(int x) { arrowTox=x;}
    void setArrowToy(int y){ arrowToy=y;}



    //返回ready的状态
    bool getReadyToPaintNeutron(){return readyToPaintNeutron;}
    bool getReadyToPaintNuclear(){return readyToPaintNuclear;}
    bool getReadyToPaintArrow(){return readyToPaintArrow;}
    bool getArrowEnsure(){return arrowEnsure;}
    int getArrowTox(){return arrowTox;}
    int getArrowToy(){return arrowToy;}


    //鼠标点击事件
    //鼠标移动事件
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    bool readyToPaintNeutron=false;
    bool readyToPaintNuclear=false;
    bool readyToPaintArrow=false;
    bool arrowEnsure=false;         //锁定箭头

    int arrowTox;
    int arrowToy;


    vector<Nuclear> NuclearList;
    vector<Neutron> NeutronList;
    vector<Atom> AtomList;
};


#endif // VIEW_PAINTLABEL_H






