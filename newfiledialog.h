#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>

namespace Ui {
class NewFileDialog;
}

class NewFileDialog : public QDialog
{
    Q_OBJECT

public:
    int width();
    int height();

    explicit NewFileDialog(QWidget *parent = nullptr);
    ~NewFileDialog();

private:
    Ui::NewFileDialog *ui;
};

#endif // NEWFILEDIALOG_H
