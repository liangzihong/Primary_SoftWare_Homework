#include<QPainter>
#include"view_paintlabel.h"
#include<QWidget>
#include<QMouseEvent>


PaintLabel::PaintLabel(QWidget *parent): QLabel(parent)
{
    readyToPaintArrow=false;
    readyToPaintNeutron=false;
    readyToPaintNuclear=true;
    arrowEnsure=false;
    setMouseTracking(true);
}





/**
 * @brief PaintLabel::paintEvent
 * @param event
 * PaintLabel的对象update时，会被调用，  label->update ==paintEvent
 */
void PaintLabel::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    for(int i=0;i<AtomList.size();i++){
        Atom atom = AtomList[i];
        int x=atom.getX();
        int y=atom.getY();

        //画出原子核
        if(atom.getType()==1){
            painter.setBrush(Qt::yellow);
            painter.drawEllipse(x-RADIUS_Nuclear,y-RADIUS_Nuclear,2*RADIUS_Nuclear,2*RADIUS_Nuclear);
        }

        //画出中子
        else{
            painter.setBrush(Qt::blue);
            painter.drawEllipse(x-RADIUS_Neutron,y-RADIUS_Neutron,2*RADIUS_Neutron,2*RADIUS_Neutron);

        }
    }

    if(readyToPaintArrow){
        QPen pen;
        pen.setStyle(Qt::DashDotLine);
        pen.setColor(Qt::blue);
        pen.setWidth(5);
        painter.setPen(pen);
        painter.drawLine(NeutronList[0].getX(),NeutronList[0].getY(),arrowTox,arrowToy);
    }

}


/**
 * @brief mousePressEvent
 * @param event
 * 鼠标单击事件，event->x()是横坐标，event->y()是纵坐标
 */
void PaintLabel::mousePressEvent(QMouseEvent *event){

    if(readyToPaintNuclear){
        int x=event->x();
        int y =event->y();

        Nuclear nuclear(x,y);
        AtomList.push_back(nuclear);
        NuclearList.push_back(nuclear);
        update();
    }

    else if(readyToPaintNeutron){
        int x=event->x();
        int y=event->y();


        Neutron neutron(x,y);
        //判断有没重合，有则发出警告
        if( About_Math::isOverlapping(neutron,AtomList)){    //有重合
            QMessageBox::warning(this,"warming",tr("初始中子不能与原子核有重合部分"),QMessageBox::Ok,QMessageBox::Ok);
        }
        else {
           AtomList.push_back(neutron);
           NeutronList.push_back(neutron);
           this->setReadyToPaintNeutron(false);
           update();
        }
    }

    else if(readyToPaintArrow){
        arrowEnsure=true;
    }





}


void PaintLabel::mouseMoveEvent(QMouseEvent *event)
{

    //设置箭头所向的坐标，方便paint画图
    if(readyToPaintArrow){
        int x=event->x();
        int y=event->y();

        //箭头未确定，所以可以改变
        if(arrowEnsure==false){
            setArrowTox(x);
            setArrowToy(y);
        }
        update();
    }
}















