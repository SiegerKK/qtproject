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

// 1 - free
// 2 - line
// 3 - elipse
// 4 - square
void Painter::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_F:
            setFreePaintMode();
            break;
        case Qt::Key_L:
            setLinePaintMode();
            break;
        case Qt::Key_E:
            setElipsePaintMode();
            break;
        case Qt::Key_P:
            setSquarePaintMode();
            break;
        case Qt::Key_S:
            savePicture();
            break;
        case Qt::Key_O:
            loadPicture();
            break;
    }
//    void setFillPaintMode();
//    void changePaintingColor();
}

void Painter::mousePressEvent(QMouseEvent *event){
    if(lastKnownPosition != 0) delete lastKnownPosition;
    lastKnownPosition = new QPoint(event->x(), event->y());

    if(paintMode == 2 || paintMode == 3 || paintMode == 4) tempImage = image;
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

void Painter::setFreePaintMode(){
    paintMode = 1;
}
void Painter::setLinePaintMode(){
    paintMode = 2;
}
void Painter::setElipsePaintMode(){
    paintMode = 3;
}
void Painter::setSquarePaintMode(){
    paintMode = 4;
}

void Painter::savePicture(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                                    QString(),
                                                    tr("Images (*.png)"));
    if (!fileName.isEmpty())
        image.save(fileName);
}

void Painter::loadPicture(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image File"),
                                                    QString(),
                                                    tr("Images (*.png)"));

    tempImage.load(fileName);
    rewritePictureFromBackup();
}

void Painter::rewritePictureFromBackup(){
    for (int y = 0; y < image.height(); y++){
        memcpy(image.scanLine(y), tempImage.scanLine(y), image.bytesPerLine());
    }
}



//+przerobić obsługę zdarzeń przyciśnięcia klawisza na klawiaturze powiązanych z wyborem trybu rysowania - w momencie przyciśnięcia
//    klawisza ma być uruchamiana odpowiednia metoda, która jednocześnie będzie slotem. W tym momencie może się wydawać trochę
//    bez sensu - ponieważ w tej metodzie (slocie) będzie tylko zmiana jednego atrybutu klasy (np. tryb='l'), ale na przyszłych
//    zajęciach będziemy te tryby wywoływać w inny sposób (np. z menu) i pisząc, od tej pory, kod w ten sposób będzie mniej przerabiania później.
//+dodać możliwość rysowania elips (klawisz e - oczywiście odrębna metoda/slot) - patrz dokumentacja do klasy QPainter - metoda drawEclipse
//+dodać możliwość rysowania prostokątów (klawisz p - oczywiście odrębna metoda/slot)
//+zapis tworzonego rysunku do pliku graficznego z wykorzystaniem standardowego okina dialogowego wyboru pliku - (metoda getSaveFileName)
//+odczyt tworzonego rysunku z pliku graficznego z wykorzystaniem standardowego okna dialogowego wyboru pliku (metoda getOpenFileName)
//dodać możliwość zmiany koloru pióra rysowanych elementów (klawisz w - patrzy wyżej)  z wykorzystniem standardowego okna dialogowego do wyboru koloru
//dodać możliwość zmiany koloru wypełnienia rysowanych elementów (klawisz k - patrzy wyżej)

