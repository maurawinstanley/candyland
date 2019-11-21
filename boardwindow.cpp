#include "boardwindow.h"
#include "ui_boardwindow.h"

BoardWindow::BoardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BoardWindow)
{
    ui->setupUi(this);
}

BoardWindow::~BoardWindow()
{
    delete ui;
}
