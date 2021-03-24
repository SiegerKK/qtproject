#include "painter.h"
#include "ui_painter.h"

#include <iostream>

Painter::Painter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Painter)
    , image(500, 500, QImage::Format_RGB32)
{
    ui->setupUi(this);
    image.fill(Qt::white);
    tempImage = image;
    lastKnownPosition = new QPoint(0, 0);
}


Painter::~Painter(){
    delete lastKnownPosition;
    delete ui;
}

void Painter::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_P:
            paintMode = 1;
            break;
        case Qt::Key_L:
            paintMode = 2;
            break;
    }
}

void Painter::mousePressEvent(QMouseEvent *event){
    if(lastKnownPosition != 0) delete lastKnownPosition;
    lastKnownPosition = new QPoint(event->x(), event->y());

    if(paintMode == 2) tempImage = image;
}

void Painter::mouseMoveEvent(QMouseEvent *event){
    QPainter painter(&image);
    switch(paintMode){
        case 1:
            painter.drawLine(lastKnownPosition->rx(),
                             lastKnownPosition->ry(),
                             event->x(),
                             event->y());
            update();

            if(lastKnownPosition != 0) delete lastKnownPosition;
            lastKnownPosition = new QPoint(event->x(), event->y());

            break;
        case 2:
//            image = tempImage;
            for (int y = 0; y < image.height(); y++){
                memcpy(image.scanLine(y), tempImage.scanLine(y), image.bytesPerLine());
            }
            painter.drawLine(lastKnownPosition->rx(),
                             lastKnownPosition->ry(),
                             event->x(),
                             event->y());
            update();

            break;
    }
}

void Painter::mouseReleaseEvent(QMouseEvent *event){
    QPainter painter(&image);
    switch(paintMode){
        case 1: break;
        case 2:
            painter.drawLine(lastKnownPosition->rx(),
                             lastKnownPosition->ry(),
                             event->x(),
                             event->y());
            update();

            if(lastKnownPosition != 0) delete lastKnownPosition;
            lastKnownPosition = new QPoint(event->x(), event->y());

            break;
    }
}

void Painter::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

