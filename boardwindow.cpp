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
    SetUpBoard();
    //std::vector<Square* > test = squares_.back();
    int k = 0;
    for (int i = 0; i <num_players; i++){
        Player* new_player = new Player(i+1, true);
        scene->addItem(new_player);
        new_player->set_location(squares_.back());
        players_.push_back(new_player);

        qDebug()<<"i";
        k++;
    }
    int num_cpu = 4-num_players;
    if (num_cpu>0){
        for (k; k<4; k++){
            Player* new_player = new Player(k+1, false);
            scene->addItem(new_player);
            new_player->set_location(squares_.back());
            players_.push_back(new_player);
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


void BoardWindow::on_powerup_button_clicked(Player *p)
{ //use the power up
    Powerup p_powerup = p->get_powerup();
    if (p_powerup==Powerup::None){
        qDebug()<<"Sorry, no powerup currently available";
    } else {
        p->set_powerup(Powerup::None);
    }
}

void BoardWindow::on_drawcard_button_clicked(Player *p)
{ //draw card
    Card current_card;
    QColor color_needed;
    if (rand() % 5 == 0){
        current_card =  Card::Blue;
        color_needed = QColor(244, 154, 194);
    }
    if (rand() % 5 == 1){
        current_card = Card::Green;
        color_needed = QColor(154, 239, 244);
    }
    if (rand() % 5 == 2){
        current_card = Card::Red;
        color_needed = QColor(154, 244, 204);
    }
    if (rand() % 5 == 3){
        current_card = Card::Yellow;
        color_needed = QColor(239, 115, 108);
    }
    if (rand() % 5 == 4){
        current_card = Card::Pink;
        color_needed = QColor(239, 244, 154);
    }

    Square *current_square = p->get_location();
    Square *next_square = GetNextSquare(current_square, color_needed);
    if (next_square->get_id()!= -1){
        //then it's a valid square so move the player to that location
        p->set_location(next_square);
    }




}

Square* BoardWindow::GetNextSquare(Square* previous_square, QColor color_needed){ //gets the next square of the card's color
    int square_id = previous_square->get_id();
    int ctr = square_id+1;

    for (ctr; ctr<squares_.size(); ctr++){
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















