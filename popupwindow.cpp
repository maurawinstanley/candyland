#include "popupwindow.h"
#include "ui_popupwindow.h"
#include <QDebug>

Popupwindow::Popupwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Popupwindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("0");
    ui->comboBox->addItem("1");
    ui->comboBox->addItem("2");
    ui->comboBox->addItem("3");
    ui->comboBox->addItem("4");
}

Popupwindow::~Popupwindow()
{
    delete ui;
}


void Popupwindow::on_comboBox_currentIndexChanged(int index)
{
    num_players_ = index;
    qDebug()<<num_players_;
}

void Popupwindow::on_pushButton_clicked()
{
    emit finish_clicked();
    //delete ui;
    Popupwindow::close();
}
