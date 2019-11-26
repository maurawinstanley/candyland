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
    std::string s = "PLAYER 1, it is your turn to draw a card.";
    ui->turnLabel->setText(s.c_str());



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
    Card current_card;
    QColor color_needed;
    std::string card_string = "PLAYER " + std::to_string(active_player_ + 1) + " drew a ";
    int num = rand() % 5;
    if (num == 0){
        card_string += "Blue";
        current_card =  Card::Blue;
        color_needed = QColor(244, 154, 194);
    }
    if (num == 1){
        card_string += "Green";
        current_card = Card::Green;
        color_needed = QColor(154, 239, 244);
    }
    if (num == 2){
        card_string += "Red";
        current_card = Card::Red;
        color_needed = QColor(154, 244, 204);
    }
    if (num == 3){
        card_string += "Yellow";
        current_card = Card::Yellow;
        color_needed = QColor(239, 115, 108);
    }
    if (num == 4){
        card_string += "Pink";
        current_card = Card::Pink;
        color_needed = QColor(239, 244, 154);
    }



    Player* p = players_[active_player_];
    Square *current_square = p->get_location();
    Square *next_square = GetNextSquare(current_square, color_needed);

    card_string += " card. You have advanced " + std::to_string(next_square->get_id() - current_square->get_id()) + " spaces.";
    ui->drawCardLabel->setText(card_string.c_str());
    scene->update();
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
    std::string turn_string = "PLAYER " + std::to_string(active_player_ + 1) + ", it is your turn to draw a card.";
    ui->turnLabel->setText(turn_string.c_str());

}

Square* BoardWindow::GetNextSquare(Square* previous_square, QColor color_needed){ //gets the next square of the card's color
    int square_id = previous_square->get_id();
    int ctr = square_id;
    qDebug() << "Square id:" << square_id;
    qDebug() << "Needed color:" << color_needed;
    for (ctr; ctr < squares_.size(); ctr++){
        qDebug() << ctr << ", " << squares_[ctr]->get_color();
        if (squares_[ctr]->get_color() == color_needed){
            return squares_[ctr+1];
        }
    }
    // else that means there are no squares of that color left

    Square *null_square = new Square(0,0,-1);
    return null_square;


}


void BoardWindow::TakeTurn(Player *p){

}
