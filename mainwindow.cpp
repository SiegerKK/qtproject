#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newfiledialog.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    painter = new Painter();
    setCentralWidget(painter);
//    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionNew_triggered(){
    NewFileDialog dialog(this);
    dialog.setModal(true);
    int width = 0;
    int height = 0;
    if(dialog.exec() == 1){
        width = dialog.width();
        height = dialog.height();
//        qDebug() << width << " " << height;
        delete painter;
        painter = new Painter(this, width, height);
        setCentralWidget(painter);
    }
}

void MainWindow::on_action_Open_triggered(){
    painter->loadPicture();
}

void MainWindow::on_actionSave_as_triggered(){
    painter->savePictureAs();
}

void MainWindow::on_action_Save_triggered(){
    painter->savePicture();
}

void MainWindow::on_action_Exit_triggered(){
    close();
}

void MainWindow::on_actionPencil_triggered(){
    painter->setFreePaintMode();
}

void MainWindow::on_actionLine_triggered(){
    painter->setLinePaintMode();
}

void MainWindow::on_actionRect_triggered(){
    painter->setRectPaintMode();
}

void MainWindow::on_actionCircle_triggered(){
    painter->setElipsePaintMode();
}

void MainWindow::on_actionColor_triggered(){
    painter->changePaintingColor();
}

void MainWindow::on_actionFill_color_triggered(){
    painter->changeFillColor();
}

void MainWindow::on_actionClean_triggered(){
    painter->clear();
}
