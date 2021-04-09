#include "painter.h"
//#include "ui_painter.h"

#include <iostream>

Painter::Painter(QWidget *parent, int width, int height)
    : QWidget(parent)
    , image(width, height, QImage::Format_RGB32)
{
    image.fill(Qt::white);
    tempImage = image;
    lastKnownPosition = new QPoint(0, 0);
}


Painter::~Painter(){
    delete lastKnownPosition;
}

// 1 - free
// 2 - line
// 3 - elipse
// 4 - square
void Painter::keyPressEvent(QKeyEvent *event){
//    switch(event->key()){
//        case Qt::Key_F:
//            setFreePaintMode();
//            break;
//        case Qt::Key_L:
//            setLinePaintMode();
//            break;
//        case Qt::Key_E:
//            setElipsePaintMode();
//            break;
//        case Qt::Key_P:
//            setSquarePaintMode();
//            break;
//        case Qt::Key_S:
//            savePicture();
//            break;
//        case Qt::Key_O:
//            loadPicture();
//            break;
//        case Qt::Key_W:
//            changePaintingColor();
//            break;
//        case Qt::Key_K:
//            changeFillColor();
//            break;
//    }
}

void Painter::mousePressEvent(QMouseEvent *event){
    if(lastKnownPosition != 0) delete lastKnownPosition;
    lastKnownPosition = new QPoint(event->x(), event->y());

    if(paintMode == 2 || paintMode == 3 || paintMode == 4)
        tempImage = image;
}

void Painter::mouseMoveEvent(QMouseEvent *event){
    QPainter painter(&image);
    painter.setPen(color);
    painter.setBrush(colorFill);
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
            rewritePictureFromBackup();
            painter.drawLine(lastKnownPosition->rx(),
                             lastKnownPosition->ry(),
                             event->x(),
                             event->y());
            update();

            break;
        case 3:
            rewritePictureFromBackup();
            painter.drawEllipse(lastKnownPosition->rx(),
                                lastKnownPosition->ry(),
                                event->x() - lastKnownPosition->rx(),
                                event->y() - lastKnownPosition->ry());
            update();

            break;
        case 4:
            rewritePictureFromBackup();
            painter.drawRect(lastKnownPosition->rx(),
                             lastKnownPosition->ry(),
                             event->x() - lastKnownPosition->rx(),
                             event->y() - lastKnownPosition->ry());
            update();

            break;
    }
}

void Painter::mouseReleaseEvent(QMouseEvent *event){}

void Painter::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void Painter::setFreePaintMode(){
    paintMode = 1;
}
void Painter::setLinePaintMode(){
    paintMode = 2;
}
void Painter::setElipsePaintMode(){
    paintMode = 3;
}
void Painter::setRectPaintMode(){
    paintMode = 4;
}

void Painter::changeFillColor(){
    colorFill = QColorDialog::QColorDialog::getColor();
}

void Painter::changePaintingColor(){
    color = QColorDialog::QColorDialog::getColor();
}

void Painter::savePictureAs(){
    fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                                    QString(),
                                                    tr("Images (*.png)"));
    if (!fileName.isEmpty())
        image.save(fileName);
}
void Painter::savePicture(){
    if (!fileName.isEmpty())
        image.save(fileName);
}

void Painter::loadPicture(){
    fileName = QFileDialog::getOpenFileName(this, tr("Open Image File"),
                                                    QString(),
                                                    tr("Images (*.png)"));

    if(!fileName.isEmpty()&& !fileName.isNull()){
        tempImage.load(fileName);
        rewritePictureFromBackup();
    }
}

void Painter::rewritePictureFromBackup(){
    for (int y = 0; y < image.height(); y++)
        memcpy(image.scanLine(y), tempImage.scanLine(y), image.bytesPerLine());
}

void Painter::clear(){
//    tempImage = QImage(500, 500, QImage::Format_RGB32);
    tempImage.fill(Qt::white);
    rewritePictureFromBackup();
    update();
}
