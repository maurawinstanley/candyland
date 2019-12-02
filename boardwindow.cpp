#include "boardwindow.h"
#include "ui_boardwindow.h"
#include "square.h"
#include "card.h"
#include <QDebug>
#include <string>

std::string Stringify(Powerup p){
    switch(p){
        case Powerup::Double:
            return "Double";
        case Powerup::PlusOne:
            return "Plus one";
        case Powerup::Backward:
            return "Backward";
    }
}

BoardWindow::BoardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BoardWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    graph_scene = new QGraphicsScene;
    card_scene = new QGraphicsScene;

    QGraphicsView * view = ui->graphicsView;
    view->setScene(scene);
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());

    view2 = ui->graphicsView_2;
    view2->setScene(graph_scene);
    view2->setSceneRect(0,0,view2->frameSize().width(),view2->frameSize().height());

    card_view = ui->cardView;
    card_view->setScene(card_scene);
    card_view->setSceneRect(0,0,card_view->frameSize().width(),card_view->frameSize().height());

    popup = new Popupwindow();
    connect(popup, SIGNAL(finish_clicked()), this, SLOT(on_finish_clicked()));
    ui->drawcard_button->setEnabled(false);
    ui->powerup_button->setEnabled(false);
    ui->moveButton->setEnabled(false);
    player_icons_[0] = QIcon(":/Documents/prog_proj/in_class/images/computer.svg");
    player_icons_[1] = QIcon(":/Documents/prog_proj/in_class/images/candy1.svg");
    player_icons_[2] = QIcon(":/Documents/prog_proj/in_class/images/candy2.svg");
    player_icons_[3] = QIcon(":/Documents/prog_proj/in_class/images/candy3.svg");
    player_icons_[4] = QIcon(":/Documents/prog_proj/in_class/images/candy4.svg");


}

BoardWindow::~BoardWindow()
{
    delete ui;
}

void BoardWindow::on_pushButton_clicked()
{

}

void BoardWindow::NewGame(int num_humans){

    active_player_ = 0;
    SetUpBoard();
    PlayerFactory pf;
    players_ = {};

    for (int i = 0; i < num_humans; i++){
        QIcon icon = player_icons_[i+1];

        Player* p = pf.createHuman(i+1, icon);
        scene->addItem(p);
        p->set_location(squares_[0]);
        players_.push_back(p);
        qDebug()<<"new human";
    }

    int num_cpu = num_humans;
    if (num_cpu<4){
        for (num_cpu; num_cpu < 4; num_cpu++){
            QIcon icon = player_icons_[0];
            Player* p = pf.createCpu(num_cpu+1, icon);
            scene->addItem(p);
            p->set_location(squares_[0]);
            players_.push_back(p);
            qDebug()<<"new cpu";
        }
    }
    ui->drawcard_button->setEnabled(true);
    std::string s = "PLAYER 1, it is your turn to draw a card.";
    ui->turnLabel->setText(s.c_str());



}
void BoardWindow::on_finish_clicked(){
    /*for (int i = 0; i<4; i++){
        Player *p = players_[i];
        scene->removeItem(p);
    }*/
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


void BoardWindow::on_powerup_button_clicked() {

    // set active to most recent player
    if (active_player_ == 0) {
        active_player_ = 3;
    } else {
        active_player_--;
    }
    Player* p = players_[active_player_];
    Powerup powup = p->get_powerup();

    std::string turn_string = "PLAYER " + std::to_string(active_player_ + 1) + ", it is your turn to powerup.";
    ui->turnLabel->setText(turn_string.c_str());

    //use the power up
    if (powup==Powerup::None){
        qDebug()<<"Sorry, no powerup currently available";
    } else {
        if (powup == Powerup::Double){
            Square * current_square = p->get_location();
            QColor color_needed = current_square->get_color();
            Square *next_square = GetNextSquare(current_square, color_needed);
            MovePlayer(next_square, current_square);

        } else if (powup == Powerup::PlusOne) {
            qDebug()<<"Plus one";
            Square *current_square = p->get_location();
            int curr_id = current_square->get_id();
            Square *plus_one = squares_[curr_id+1];
            scene->removeItem(p);
            p->set_location(plus_one);
            scene->addItem(p);
            if (plus_one->get_powerup()!=Powerup::None){
//                qDebug()<<"there's a powerup";
//                qDebug()<<plus_one->get_powerup();
                p->set_powerup(plus_one->get_powerup());
            }

            CheckForWinner(plus_one);
        } else { //its backward
            qDebug()<<"backward";
            Square *current_square = p->get_location();
            int curr_id = current_square->get_id();
            Square *minus_one = squares_[curr_id-1];
            scene->removeItem(p);
            p->set_location(minus_one);
            scene->addItem(p);
            if (minus_one->get_powerup()){
//                qDebug()<<"there's a powerup";
//                qDebug()<<minus_one->get_powerup();
                p->set_powerup(minus_one->get_powerup());
            }
        }
    }

    p->set_powerup(Powerup::None);
    ui->powerup_button->setEnabled(false);

    if (active_player_ == 3) {
        active_player_ = 0;
    } else {
        active_player_++;
    }

    turn_string = "PLAYER " + std::to_string(active_player_ + 1) + ", it is your turn to draw a card.";
    ui->turnLabel->setText(turn_string.c_str());

}

void BoardWindow::on_drawcard_button_clicked() {
    //draw card
    QColor color_needed;
    std::string card_string = "PLAYER " + std::to_string(active_player_ + 1) + " drew a ";
    int num = rand() % 5;
    if (num == 0){
        card_string += "Blue";
        color_needed = QColor(154, 239, 244);
    } else if (num == 1){
        card_string += "Green";
        color_needed = QColor(154, 244, 204);
    } else if (num == 2){
        card_string += "Red";
        color_needed = QColor(239, 115, 108);
    } else if (num == 3){
        card_string += "Yellow";
        color_needed = QColor(239, 244, 154);
    } else {
        card_string += "Pink";
        color_needed = QColor(244, 154, 194);
    }
    card_string += " card";
    ui->drawCardLabel->setText(card_string.c_str());

    Card *c = new Card(color_needed);
    card_scene->addItem(c);
    current_card_ = c;
    ui->drawcard_button->setEnabled(false);
    ui->moveButton->setEnabled(true);
}

void BoardWindow::on_moveButton_clicked()
{
    Player* p = players_[active_player_];

    Square *current_square = p->get_location();
    Square *next_square = GetNextSquare(current_square, current_card_->get_color());
    MovePlayer(next_square, current_square);
    ui->moveButton->setEnabled(false);
    ui->drawcard_button->setEnabled(true);
}

void BoardWindow::MovePlayer(Square * next_square, Square* current_square){
//    qDebug()<<"got the next square";
    Player *p = players_[active_player_];
    std::string move_string = "PLAYER " + std::to_string(active_player_+1) + " advanced ";
    if (next_square->get_id()!= -1){
        // then it's a valid square so move the player to that location
        scene->removeItem(p);
        p->set_location(next_square);
        scene->addItem(p);
        move_string +=  std::to_string(next_square->get_id() - current_square->get_id()) + " spaces.";
        if (next_square->get_powerup()!=Powerup::None){
//            qDebug()<<"there's a powerup";
//            qDebug()<<next_square->get_powerup();
            p->set_powerup(next_square->get_powerup());
        }
    } else  {
        move_string += "0 spaces";
    }

    ui->moveLabel->setText(move_string .c_str());

    CheckForWinner(next_square);

    Powerup powup = p->get_powerup();

    if (powup!=Powerup::None){
        ui->powerup_button->setEnabled(true);
        qDebug()<<"congrats, you have a powerup";

        std::string pow_label = "Congrats, you have a powerup: " + Stringify(powup);
        ui->label->setText(pow_label.c_str());
        //ui->drawCardLabel_2->setText(c)
    } else {
        std::string pow_label = "Sorry, no powerup :(";
        ui->label->setText(pow_label.c_str());
    }


}

void BoardWindow::CheckForWinner(Square* next_square){
    // check for winner
    if (next_square == squares_[squares_.size()-1]){
        ui->drawcard_button->setEnabled(false);
        ui->powerup_button->setEnabled(false);
        std::string turn_string = "CONGRATIONS PLAYER " + std::to_string(active_player_ + 1) + ", YOU WIN! \n\n Click New Game to play again.";
        ui->turnLabel->setText(turn_string.c_str());
        players_[active_player_]->IncrementWins();
    } else {
        // update whose turn it is
        if (active_player_ == 3) {
            active_player_ = 0;
        } else {
            active_player_++;
        }
        std::string turn_string = "PLAYER " + std::to_string(active_player_ + 1) + ", it is your turn to draw a card.";
        ui->turnLabel->setText(turn_string.c_str());
    }
    UpdateGraph();
}

Square* BoardWindow::GetNextSquare(Square* previous_square, QColor color_needed){ //gets the next square of the card's color
    int square_id = previous_square->get_id();
    int ctr = square_id+1;
    for (ctr; ctr < squares_.size(); ctr++){
        if (squares_[ctr]->get_color() == color_needed){
            return squares_[ctr];
        }
    }
    // else that means there are no squares of that color left

    Square *null_square = new Square(0,0,-1);
    return null_square;


}
void BoardWindow::UpdateGraph(){
    graph_scene->clear();
    for (int i = 0; i<players_.size(); i++){

        Player *p = players_[i];
        int wins = p->get_wins();
        QGraphicsRectItem* item = new QGraphicsRectItem((i+1)*10,85,30, wins*10);
        //QGraphicsRectItem* item2 = new QGraphicsRectItem(30,85,40, 40);
        graph_scene->addItem(item);
        //graph_scene->addItem(item2);
    }
    graph_scene->update();
    view2->update();
}


void BoardWindow::on_powLabel_linkActivated(const QString &link)
{

}

void BoardWindow::on_newGameButton_clicked()
{
    popup->show();

}
