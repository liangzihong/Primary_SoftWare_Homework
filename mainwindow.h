#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMessageBox>
#include <QMainWindow>
#include<vector>
#include"atom.h"
#include"neutron.h"
#include"nuclear.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /*出现对话框*/
    void welcomeMessage();
    void statementMessage();

    void tellPaintNuclear();



private:
    Ui::MainWindow *ui;
    QMessageBox *msg;

};

#endif // MAINWINDOW_H
