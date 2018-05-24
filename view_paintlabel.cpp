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

    timer=new QTimer(this);
    isMoving=false;
}





/**
 * @brief PaintLabel::paintEvent
 * @param event
 * PaintLabel的对象update时，会被调用，  label->update ==paintEvent
 */
void PaintLabel::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    //初始化状态
    if(isMoving==false) {
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



    //运动状态
    else{


        //先画原子核
        for(int i=0;i<NuclearList.size();i++){
            Nuclear tmp=NuclearList[i];
            int x=tmp.getX();
            int y=tmp.getY();
            painter.setBrush(Qt::yellow);
            painter.drawEllipse(x-RADIUS_Nuclear,y-RADIUS_Nuclear,2*RADIUS_Nuclear,2*RADIUS_Nuclear);
        }




        //再画中子
        Neutron tmp1=NeutronList[0];
        tmp1.move();
        NeutronList[0]=tmp1;
        //NeutronList.push_back(tmp1);
        for(int i=0;i< NeutronList.size();i++)
        {
            Neutron tmp=NeutronList[i];
            int x=tmp.getX();
            int y=tmp.getY();
            painter.setBrush(Qt::blue);
            painter.drawEllipse(x-RADIUS_Neutron,y-RADIUS_Neutron,2*RADIUS_Neutron,2*RADIUS_Neutron);
        }



        //再画爆炸
        for(int i=0;i< NuclearList.size();i++)
        {
            Nuclear nuclear=NuclearList[i];
            for(int j=0;j<NeutronList.size();j++)
            {
                Neutron netron=NeutronList[j];
                if(nuclear.isHitByNeutron(netron)==true)
                {
                    ExplosiveList.push_back(nuclear);
                    NuclearList.erase(NuclearList.begin()+i);
                    i--;     //因为消除了这个，vector后面的会补上来
                    break;
                }
            }

        }

        for(int i=0;i<ExplosiveList.size();i++)
        {
            Atom explosive=ExplosiveList[i];
            int x=explosive.getX();
            int y=explosive.getY();

            painter.setBrush(Qt::green);
            painter.drawEllipse(x-RADIUS_Nuclear,y-RADIUS_Nuclear,2*RADIUS_Nuclear,2*RADIUS_Nuclear);
        }
        ExplosiveList.clear();











        /*for(int i=0;i< NeutronList.size();i++){
            Neutron tmp=NeutronList[i];           
            tmp.move();
            NeutronList[i]=tmp;
            // move完之后要放回去
            int x=tmp.getX();
            int y=tmp.getY();
            painter.setBrush(Qt::blue);
            painter.drawEllipse(x-RADIUS_Neutron,y-RADIUS_Neutron,2*RADIUS_Neutron,2*RADIUS_Neutron);


            QMessageBox::warning(this,"debug",tr(("angle为%1"))
                   .arg(QString::number(tmp.getAngle())) ,QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok);


            //tr("移動到：(%1, %2)")).arg(QString::number(event->x()), QString::number(event->y())
        }*/







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


//鼠标移动，画出虚线
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



//开始移动了
void PaintLabel::startMove()
{
    NeutronList[0].setAngle(arrowTox,arrowToy);
    setIsMoving(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(myselfUpdate()));
    timer->start(SPEED_OF_TIME);
}


void PaintLabel::myselfUpdate(){
    update();
}







