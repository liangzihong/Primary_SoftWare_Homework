#ifndef VIEW_PAINTLABEL_H
#define VIEW_PAINTLABEL_H






#include<QTimer>
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


    //各种状态的set
    void setReadyToPaintNeutron(bool is){ readyToPaintNeutron=is; }
    void setReadyToPaintNuclear(bool is){ readyToPaintNuclear=is; }
    void setReadyToPaintArrow(bool is){ readyToPaintArrow=is; }
    void setArrowTox(int x) { arrowTox=x;}
    void setArrowToy(int y){ arrowToy=y;}



    //get各种状态
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


    //运动过程
    void startMove();
    void setIsMoving(bool is){isMoving=is;}
    bool getIsMoving(){return isMoving;}


    //全部清0过程
    void reset()
    {

        readyToPaintArrow=false;
        readyToPaintNeutron=false;
        readyToPaintNuclear=true;
        arrowEnsure=false;
        NuclearList.clear();
        NeutronList.clear();
        AtomList.clear();
        ExplosiveList.clear();
        isMoving=false;
        if(timer!=NULL)
        {
            delete timer;
            timer=NULL;
        }
        update();
    }


private:

    //初始化的状态
    bool readyToPaintNeutron=false;
    bool readyToPaintNuclear=true;
    bool readyToPaintArrow=false;
    bool arrowEnsure=false;         //锁定箭头
    int arrowTox;
    int arrowToy;



    //存放原子核和中子的和爆炸的vector
    vector<Nuclear> NuclearList;
    vector<Neutron> NeutronList;
    vector<Atom> AtomList;
    vector<Atom> ExplosiveList;

    //时间响应
    QTimer *timer;
    bool isMoving;

public slots:
    void myselfUpdate();

};


#endif // VIEW_PAINTLABEL_H






