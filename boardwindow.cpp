#include "boardwindow.h"
#include "ui_boardwindow.h"
#include "square.h"
#include <QDebug>
#include <string>



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

void BoardWindow::NewGame(int num_humans){

    active_player_ = 0;
    SetUpBoard();
    PlayerFactory pf;

    for (int i = 0; i < num_humans; i++){
        Player* p = pf.createHuman(i+1);
        scene->addItem(p);
        p->set_location(squares_[0]);
        players_.push_back(p);
        qDebug()<<"new human";
    }

    int num_cpu = 4-num_humans;
    if (num_cpu>0){
        for (int i = 0; i < num_cpu; i++){
            Player* p = pf.createCpu(i+1);
            scene->addItem(p);
            p->set_location(squares_[0]);
            players_.push_back(p);
            qDebug()<<"new cpu";
        }

    }
    /*for (int j = 0; j<num_players+num_cpu; j++){
        Square *sq = players_[j]->get_location();
        std::pair<int, int> loc = sq->get_location();
        qDebug()<<loc.first<<" : "<<loc.second;
        QGraphicsRectItem* item3 = new QGraphicsRectItem(loc.first+20*j,loc.second+20*j,15,15);
        scene->addItem(item3);
    }*/



}
void BoardWindow::on_finish_clicked(){
    qDebug()<<"finishe clicked";
    int num_players = popup->get_num_players();
    NewGame(num_players);
}

void BoardWindow::SetUpBoard() {
    squares_ = {};
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
        squares_.push_back(s);
    }

    s = new Square(9*Square::get_width(), Square::get_width(), counter);
    counter++;
    scene->addItem(s);
    squares_.push_back(s);

    // middle row
    for (int x = 9; x >= 0; x--) {
        if (rand() % 100 < 12) {
             s = new PowerSquare(x*Square::get_width(), 2*Square::get_width(), counter);
        } else {
            s = new Square(x*Square::get_width(), 2*Square::get_width(), counter);
        }
        counter++;
        scene->addItem(s);
        squares_.push_back(s);
    }

    s = new Square(0, 3*Square::get_width(), counter);
    counter++;
    scene->addItem(s);
    squares_.push_back(s);

    // bottom row
    for (int x = 0; x < 10; x++) {
        if (rand() % 100 < 12) {
             s = new PowerSquare(x*Square::get_width(), 4*Square::get_width(), counter);
        } else {
            s = new Square(x*Square::get_width(), 4*Square::get_width(), counter);
        }
        counter++;
        scene->addItem(s);
        squares_.push_back(s);
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


void BoardWindow::on_powerup_button_clicked()
{ //use the power up
    qDebug() << "in the power up button function";
//    Powerup p_powerup = p->get_powerup();
//    if (p_powerup==Powerup::None){
//        qDebug()<<"Sorry, no powerup currently available";
//    } else {
//        p->set_powerup(Powerup::None);
//    }
}

void BoardWindow::on_drawcard_button_clicked()
{ //draw card
   qDebug() << "i'm in the draw card function";
    Card current_card;
    QColor color_needed;
    std::string s = "You drew a ";
    int num = rand() % 5;
    if (num == 0){
        s += "Blue card.";
        current_card =  Card::Blue;
        color_needed = QColor(244, 154, 194);
    }
    if (num == 1){
        s += "Green card.";
        current_card = Card::Green;
        color_needed = QColor(154, 239, 244);
    }
    if (num == 2){
        s += "Red card.";
        current_card = Card::Red;
        color_needed = QColor(154, 244, 204);
    }
    if (num == 3){
        s += "Yellow card.";
        current_card = Card::Yellow;
        color_needed = QColor(239, 115, 108);
    }
    if (num == 4){
        s += "Pink card.";
        current_card = Card::Pink;
        color_needed = QColor(239, 244, 154);
    }

    ui->drawCardLabel->setText(s.c_str());
    scene->update();

    Player* p = players_[active_player_];
    Square *current_square = p->get_location();
    Square *next_square = GetNextSquare(current_square, color_needed);
    if (next_square->get_id()!= -1){
        //then it's a valid square so move the player to that location
        qDebug() << "moviing player";
        scene->removeItem(p);
        p->set_location(next_square);
        scene->addItem(p);
    } else {
        qDebug() << "next square id invalid";
    }
    if (active_player_ == 3) {
        active_player_ = 0;
    } else {
        active_player_++;
    }

}

Square* BoardWindow::GetNextSquare(Square* previous_square, QColor color_needed){ //gets the next square of the card's color
    int square_id = previous_square->get_id();
    int ctr = square_id+1;
    qDebug() << "Square id:" << square_id;
    qDebug() << "Needed color:" << color_needed;
    for (int ctr; ctr < squares_.size(); ctr++){
        qDebug() << ctr << ", " << squares_[ctr]->get_color();
        if (squares_[ctr]->get_color() == color_needed){
            return squares_[ctr];
        }
    }
    // else that means there are no squares of that color left

    Square *null_square = new Square(0,0,-1);
    return null_square;


}


void BoardWindow::TakeTurn(Player *p){

}
