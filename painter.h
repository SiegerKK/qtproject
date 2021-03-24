#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class Painter; }
QT_END_NAMESPACE

class Painter : public QWidget
{
    Q_OBJECT

public:

    Painter(QWidget *parent = nullptr);
    ~Painter();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

private:
    Ui::Painter *ui;
    QImage image, tempImage;

    // 1 - free
    // 2 - line
    int paintMode = 1;
    QPoint *lastKnownPosition = 0;

};
#endif // PAINTER_H
