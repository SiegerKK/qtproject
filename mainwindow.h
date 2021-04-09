#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "painter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Painter *painter;


signals:

private slots:
    void on_actionNew_triggered();
    void on_action_Open_triggered();
    void on_actionSave_as_triggered();
    void on_action_Save_triggered();
    void on_action_Exit_triggered();
    void on_actionColor_triggered();
    void on_actionPencil_triggered();
    void on_actionLine_triggered();
    void on_actionRect_triggered();
    void on_actionFill_color_triggered();
    void on_actionCircle_triggered();
    void on_actionClean_triggered();
};

#endif // MAINWINDOW_H


//class MainWindow : public QMainWindow
//{
//    Q_OBJECT

//public:
//    MainWindow(QWidget *parent = nullptr);
//    ~MainWindow();

//private slots:
//    void on_action_New_triggered();

//private:
//    Ui::MainWindow *ui;
//};
//#endif // MAINWINDOW_H
