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






void MainWindow::tellPaintNuclear(){
    msg=new QMessageBox();
    QString content="现在需要你在屏幕中点击你想创建的原子核的个数和位置\n点击完成后按下一步";
    msg->setText(content);
    msg->exec();

    delete msg;
    ui->paintlabel->setReadyToPaintNeutron(true);
    ui->paintlabel->update();

}














