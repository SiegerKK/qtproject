#include "newfiledialog.h"
#include "ui_newfiledialog.h"
#include <string>

int NewFileDialog::width(){
    return std::stoi(ui->leWidth->text().toStdString());
}
int NewFileDialog::height(){
    return std::stoi(ui->leHeight->text().toStdString());
}

NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);
}

NewFileDialog::~NewFileDialog(){
    delete ui;
}
