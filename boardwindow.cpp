#include "boardwindow.h"
#include "ui_boardwindow.h"
#include "square.h"
#include <QDebug>

BoardWindow::BoardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BoardWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    graph_scene = new QGraphicsScene;

    QGraphicsView * view = ui->graphicsView;
    view->setScene(scene);
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());

    popup = new Popupwindow();
    connect(popup, SIGNAL(finish_clicked()), this, SLOT(on_finish_clicked()));
}

BoardWindow::~BoardWindow()
{
    delete ui;
}

void BoardWindow::on_pushButton_clicked()
{

   popup->show();
   int num_players = popup->get_num_players();

}

void BoardWindow::NewGame(int num_players){
    //connect(c, popup::on_pushButton_clicked, this, &CellWindow::CellClickedSlot);
    //connect
    qDebug()<<"iii";
    qDebug()<<num_players;

    for (int i = 0; i <num_players; i++){
        Player* new_player = new Player(i+1);
        players_.push_back(new_player);
        qDebug()<<"i";
    }

    SetUpBoard();

}
void BoardWindow::on_finish_clicked(){
    qDebug()<<"finishe clicked";
    int num_players = popup->get_num_players();
    NewGame(num_players);
}

void BoardWindow::SetUpBoard() {
    std::vector<std::vector<Square*>> squares = {};
    QColor color = QColor(255, 255, 255);
    Square *s;
    int counter = 0;

    // top row
    for (int x = 0; x < 10; x++) {
        if (rand() % 100 < 12) {
            s = new PowerSquare(x*Square::get_width(), 0, counter);
        } else {
            s = new Square(x*Square::get_width(), 0, counter);
        }
        counter++;
        scene->addItem(s);
    }

    s = new Square(9*Square::get_width(), Square::get_width(), counter);
    counter++;
    scene->addItem(s);

    // middle row
    for (int x = 9; x >= 0; x--) {
        if (rand() % 100 < 12) {
             s = new PowerSquare(x*Square::get_width(), 2*Square::get_width(), counter);
        } else {
            s = new Square(x*Square::get_width(), 2*Square::get_width(), counter);
        }
        counter++;
        scene->addItem(s);
    }

    s = new Square(0, 3*Square::get_width(), counter);
    counter++;
    scene->addItem(s);

    // bottom row
    for (int x = 0; x < 10; x++) {
        if (rand() % 100 < 12) {
             s = new PowerSquare(x*Square::get_width(), 4*Square::get_width(), counter);
        } else {
            s = new Square(x*Square::get_width(), 4*Square::get_width(), counter);
        }
        counter++;
        scene->addItem(s);
    }
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

