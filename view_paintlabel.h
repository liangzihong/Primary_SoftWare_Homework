#ifndef VIEW_PAINTLABEL_H
#define VIEW_PAINTLABEL_H

#include<QLabel>
#include<QPainter>
#include<vector>
#include"atom.h"
#include"neutron.h"
#include"nuclear.h"
using namespace std;
#define RADIUS_Nuclear 25
#define RADIUS_Neutron 3

class PaintLabel: public QLabel
{
    Q_OBJECT
public:
    explicit PaintLabel(QWidget*parent=0);
    void paintEvent(QPaintEvent* event);

    //运动过程中
    void paint_Neutron(double x,double y);
    void paint_Nuclear(double x,double y);

    //void paint_Explosion(double x, double y);
    //void paint_NeutronArrow(double startx,double starty,double endx,double endy);


    void setReadyToPaintNeutron(bool is){ readyToPaintNeutron=is; }
    void setReadyToPaintNuclear(bool is){ readyToPaintNuclear=is; }

    //鼠标点击事件
    void mousePressEvent(QMouseEvent *event);

private:
    bool readyToPaintNeutron=false;
    bool readyToPaintNuclear=false;

    vector<Atom> AtomList;
};


#endif // VIEW_PAINTLABEL_H
