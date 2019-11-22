#include "boardwindow.h"
#include "ui_boardwindow.h"
#include <QDebug>

enum Card {Blue, Green, Red, Yellow, Pink};

BoardWindow::BoardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BoardWindow)
{
    ui->setupUi(this);
    popup = new Popupwindow();
    connect(popup, SIGNAL(finish_clicked()), this, SLOT(on_finish_clicked()));
}

BoardWindow::~BoardWindow()
{
    delete ui;
}

void BoardWindow::on_pushButton_clicked()
{
    qDebug()<<"hi";

    popup->show();
    int num_players = popup->get_num_players();
    //qDebug()<<"sii";
    //qDebug()<<num_players;
    //NewGame(num_players);

}

void BoardWindow::NewGame(int num_players){
    //connect(c, popup::on_pushButton_clicked, this, &CellWindow::CellClickedSlot);
    //connect
    qDebug()<<"iii";
    qDebug()<<num_players;

    for (int i = 0; i<num_players; i++){
        Player* new_player = new Player(i+1);
        players_.push_back(new_player);
        qDebug()<<"i";
    }

}
void BoardWindow::on_finish_clicked(){
    qDebug()<<"finishe clicked";
    int num_players = popup->get_num_players();
    NewGame(num_players);
}


void BoardWindow::changeWindow()
{
    if(popup->isVisible())
    {
        popup->hide();
        this->show();
    }
    else
    {
        this->hide();
        popup->show();
    }
}

