#include<QPainter>
#include"view_paintlabel.h"
#include<QWidget>
#include<QMouseEvent>


PaintLabel::PaintLabel(QWidget *parent): QLabel(parent)
{
    readyToPaintNeutron=false;
    readyToPaintNuclear=false;
}


/**
 * @brief PaintLabel::paint_Neutron
 * @param x
 * @param y
 * 画出中子
 */
void PaintLabel::paint_Neutron(double x, double y)
{
    if(readyToPaintNeutron) {
        QPainter painter(this);
        painter.setBrush(Qt::red);
        //如果x，y在画图范围内
        painter.drawEllipse(20,20,160,160);
    }


}

/**
 * @brief PaintLabel::paint_Nuclear
 * @param x
 * @param y
 * 画出原子核
 */
void PaintLabel::paint_Nuclear(double x, double y)
{
    if(readyToPaintNuclear){
        //原子核的半径初定为20
        QPainter painter(this);
        painter.setBrush(Qt::yellow);
        //如果x，y在画图范围内
        painter.drawEllipse(x-RADIUS_Nuclear,y-RADIUS_Nuclear,2*RADIUS_Nuclear,2*RADIUS_Nuclear);
    }
}



/**
 * @brief PaintLabel::paintEvent
 * @param event
 * PaintLabel的对象update时，会被调用，  label->update ==paintEvent
 */
void PaintLabel::paintEvent(QPaintEvent* event)
{
    for(int i=0;i<AtomList.size();i++){
        Atom atom = AtomList[i];
        if(atom.getType()==0)
            paint_Neutron(atom.getX(),atom.getY());
        else paint_Nuclear(atom.getX(),atom.getY());
    }
    setReadyToPaintNeutron(false);
    setReadyToPaintNuclear(false);
}


/**
 * @brief mousePressEvent
 * @param event
 * 鼠标单击事件，event->x()是横坐标，event->y()是纵坐标
 */
void PaintLabel::mousePressEvent(QMouseEvent *event){
    int x=event->x();
    int y =event->y();

    Nuclear nuclear(x,y);
    AtomList.push_back(nuclear);

    setReadyToPaintNuclear(true);
    update();

}















