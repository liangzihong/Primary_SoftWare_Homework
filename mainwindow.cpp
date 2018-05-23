#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>
#include <QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




/**
 * @brief MainWindow::welcomeMessage
 * 这是强制出现的一个对话框，说明这个软件的用途。
 *
 * 因为mainwindow会先构造函数再show，所以如果welcomeMessage放在构造函数中，就没有想要的结果。
 * 所以必须先要mainwindow的show之后，再调用这个函数出现对话框。
 * 并且   exec是会产生中断，而show不会，所以如果只用show的话，另一个对话框也会出现，这样不好，必须按了确定，才有另一个对话框出现。
 */
void MainWindow::welcomeMessage(){
    msg=new QMessageBox();
    msg->setText("欢迎来到原子核裂变的链式反应，这个软件生动地展示链式反应");
    msg->exec();

    delete msg;
    statementMessage();
}



/**
 * @brief MainWindow::statementMessage
 * 这也是强制出现的，被 welcomeMessage所调用，表明是跟随其后出现的
 */
void MainWindow::statementMessage(){
    msg=new QMessageBox();
    msg->setText("现在实验开始\n你需要按照实验指引进行，每完成一个步骤，就按下旁边的确定按钮进行下一步\nGood luck!");
    msg->exec();

    delete msg;
    tellPaintNuclear();
}





/**
 * @brief MainWindow::tellPaintNuclear
 * 告诉使用者现在可以 画原子核
 */
void MainWindow::tellPaintNuclear(){
    msg=new QMessageBox();
    QString content="现在需要你在屏幕中点击你想创建的原子核的个数和位置\n点击完成后按下一步";
    msg->setText(content);
    msg->exec();

    delete msg;
    ui->paintlabel->update();

}


/**
 * @brief MainWindow::tellPaintArrow
 * 告诉使用者现在可以   画箭头
 */
void MainWindow::tellPaintArrow()
{
    msg=new QMessageBox();
    QString content="现在请你确定中子出发时的方向和速度\n你可以移动鼠标，虚线长度代表速度\n如果确定就再单击一下鼠标";
    msg->setText(content);
    msg->exec();

    delete msg;
}


/**
 * @brief MainWindow::tellPaintNeutron
 * 告诉使用者现在可以    画中子
 */
void MainWindow::tellPaintNeutron()
{
    msg=new QMessageBox();
    QString content="现在在屏幕中点击一下，代表初始中子的位置\n注意中子的位置不能与各个原子核有交集\n如果重合则无法显示";
    msg->setText(content);
    msg->exec();

    delete msg;

}





/**
 * @brief MainWindow::on_nextstep_button_clicked
 * 这里是nextstep的响应事件，用来控制 PaintLabel，决定能否通过点击屏幕产生事件
 */
void MainWindow::on_nextstep_button_clicked()
{

    bool readyNuclear= ui->paintlabel->getReadyToPaintNuclear();
    bool readyNeutron= ui->paintlabel->getReadyToPaintNeutron();
    bool readyArrow= ui->paintlabel->getReadyToPaintArrow();

    if(readyNuclear){
        readyNuclear=false;
        ui->paintlabel->setReadyToPaintNuclear(false);
        ui->paintlabel->setReadyToPaintNeutron(true);

        tellPaintNeutron();
    }

    //因为在画中子的时候，画完中子 readyNeutron就为true，所以几乎没机会进入这个
    else if(readyNeutron){
        readyNeutron=false;
        ui->paintlabel->setReadyToPaintNeutron(false);
    }

    //告诉现在要画箭头
    else if(readyArrow==false && readyNeutron==false){

        readyArrow =true;
        ui->paintlabel->setReadyToPaintArrow(true);
        tellPaintArrow();
    }
}



void MainWindow::on_start_button_clicked()
{

    //收起箭头,开始移动
     if(ui->paintlabel->getArrowEnsure()){

         ui->paintlabel->setReadyToPaintArrow(false);
         ui->paintlabel->update();

         ui->paintlabel->startMove();
     }
}































