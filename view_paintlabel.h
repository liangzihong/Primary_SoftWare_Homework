#ifndef VIEW_PAINTLABEL_H
#define VIEW_PAINTLABEL_H


#define RADIUS_Nuclear 30
#define RADIUS_Neutron 3

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

    //返回ready的状态
    bool getReadyToPaintNeutron(){return readyToPaintNeutron;}
    bool getReadyToPaintNuclear(){return readyToPaintNuclear;}

    //鼠标点击事件
    void mousePressEvent(QMouseEvent *event);

private:
    bool readyToPaintNeutron=false;
    bool readyToPaintNuclear=false;

    vector<Atom> AtomList;
};


#endif // VIEW_PAINTLABEL_H
