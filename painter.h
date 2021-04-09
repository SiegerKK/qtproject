#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QFileDialog>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Painter; }
QT_END_NAMESPACE

class Painter : public QWidget
{
    Q_OBJECT

public:

//    Painter(QWidget *parent = nullptr);
    Painter(QWidget *parent = nullptr, int width = 500, int height = 500);
    ~Painter();

    void clear();
    void setFreePaintMode();
    void setLinePaintMode();
    void setElipsePaintMode();
    void setRectPaintMode();
    void changeFillColor();
    void changePaintingColor();
    void savePicture();
    void savePictureAs();
    void loadPicture();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

private:
    void rewritePictureFromBackup();

    Ui::Painter *ui;
    QImage image, tempImage;
    QColor color, colorFill;
    QString fileName;

    // 1 - free
    // 2 - line
    // 3 - elipse
    // 4 - square
    int paintMode = 1;
    QPoint *lastKnownPosition = 0;

};
#endif // PAINTER_H
