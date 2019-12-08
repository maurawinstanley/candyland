#include "boardwindow.h"
#include "ui_boardwindow.h"
#include "square.h"
#include "card.h"
#include <QDebug>
#include <string>
#include <QThread>
#include <QApplication>
#include <QThread>

//simulating game logic for computers - so that they just move and don't draw a card
//labeling the start and end square
//swapping a powerup

std::string Stringify(Powerup p){
    switch(p){
        case Powerup::Double:
            return "Double";
        case Powerup::PlusOne:
            return "Plus one";
        case Powerup::Backward:
            return "Backward";
        case Powerup::None:
            return "None";
    }
}

BoardWindow::BoardWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BoardWindow)
{
    ui->setupUi(this);
    board_scene = new QGraphicsScene;
    graph_scene = new QGraphicsScene;
    card_scene = new QGraphicsScene;

    board_view = ui->graphicsView;
    board_view->setScene(board_scene);
    board_view->setSceneRect(0,0,board_view->frameSize().width(),board_view->frameSize().height());

    graph_view = ui->graphicsView_2;
    graph_view->setScene(graph_scene);
    graph_view->setSceneRect(0,0,graph_view->frameSize().width(),graph_view->frameSize().height());

    card_view = ui->cardView;
    card_view->setScene(card_scene);
    card_view->setSceneRect(0,0,card_view->frameSize().width(),card_view->frameSize().height());

    popup = new Popupwindow();
    connect(popup, SIGNAL(finish_clicked()), this, SLOT(on_finish_clicked()));
    ui->drawcard_button->setEnabled(false);
    ui->powerup_button->setEnabled(false);
    ui->moveplayer_button->setEnabled(false);
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

void BoardWindow::NewGame(int num_humans, std::vector<int> wins){

    num_humans_ = num_humans;
    active_player_ = 0;
    SetUpBoard();
    PlayerFactory pf;
    players_ = {};

    // reset labels
    std::string pow_label;
    for (int i = 0; i < players_.size(); i++) {
        pow_label += "Player " + std::to_string(i+1) + ": None\n";
    }
    ui->label->setText(pow_label.c_str());
    ui->drawCardLabel->setText("");
    ui->moveLabel->setText("");


    for (int i = 0; i < num_humans; i++){
        QIcon icon = player_icons_[i+1];

        Player* p = pf.createHuman(i+1, icon, wins[i]);
        board_scene->addItem(p);
        p->set_location(squares_[0]);
        players_.push_back(p);
        qDebug()<<"new human";
    }

    int num_cpu = num_humans;
    if (num_cpu<4){
        for (num_cpu; num_cpu < 4; num_cpu++){
            QIcon icon = player_icons_[0];
            Player* p = pf.createCpu(num_cpu+1, icon, wins[num_cpu]);
            board_scene->addItem(p);
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
    int num_players = popup->get_num_players();
    NewGame(num_players, {0,0,0,0});
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
        board_scene->addItem(s);
        squares_.push_back(s);
    }

    s = new Square(9*Square::get_width(), Square::get_width(), counter);
    counter++;
    board_scene->addItem(s);
    squares_.push_back(s);

    // middle row
    for (int x = 9; x >= 0; x--) {
        if (rand() % 100 < 12) {
             s = new PowerSquare(x*Square::get_width(), 2*Square::get_width(), counter);
        } else {
            s = new Square(x*Square::get_width(), 2*Square::get_width(), counter);
        }
        counter++;
        board_scene->addItem(s);
        squares_.push_back(s);
    }

    s = new Square(0, 3*Square::get_width(), counter);
    counter++;
    board_scene->addItem(s);
    squares_.push_back(s);

    // bottom row
    for (int x = 0; x < 10; x++) {
        if (rand() % 100 < 12) {
             s = new PowerSquare(x*Square::get_width(), 4*Square::get_width(), counter);
        } else {
            s = new Square(x*Square::get_width(), 4*Square::get_width(), counter);
        }
        counter++;
        board_scene->addItem(s);
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

    ui->powerup_button->setEnabled(false);
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
            board_scene->removeItem(p);
            p->set_location(plus_one);
            board_scene->addItem(p);
            if (plus_one->get_powerup()!=Powerup::None){
                p->set_powerup(plus_one->get_powerup());
            }

            CheckForWinner(plus_one);
        } else { //its backward
            qDebug()<<"backward";
            Square *current_square = p->get_location();
            int curr_id = current_square->get_id();
            Square *minus_one = squares_[curr_id-1];
            board_scene->removeItem(p);
            p->set_location(minus_one);
            board_scene->addItem(p);
            if (minus_one->get_powerup()){
                p->set_powerup(minus_one->get_powerup());
            }
        }
    }

    p->set_powerup(Powerup::None);
    ui->powerup_button->setEnabled(false);

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

    card_scene->removeItem(current_card_);
    current_card_= new Card(color_needed);
    card_scene->addItem(current_card_);

    ui->drawcard_button->setEnabled(false);
    ui->moveplayer_button->setEnabled(true);
    std::string s = "PLAYER " + std::to_string(active_player_+1) + ", it is your turn to move.";
    ui->turnLabel->setText(s.c_str());
}

void BoardWindow::on_moveplayer_button_clicked()
{
    Player* p = players_[active_player_];

    Square *current_square = p->get_location();
    Square *next_square = GetNextSquare(current_square, current_card_->get_color());
    MovePlayer(next_square, current_square);
    ui->moveplayer_button->setEnabled(false);
    ui->drawcard_button->setEnabled(true);

    CheckForWinner(next_square);
}

void BoardWindow::MovePlayer(Square * next_square, Square* current_square){
//    qDebug()<<"got the next square";
    Player *p = players_[active_player_];
    std::string move_string = "PLAYER " + std::to_string(active_player_+1) + " advanced ";
    if (next_square->get_id()!= -1){
        // then it's a valid square so move the player to that location
        int current_id = current_square->get_id();
        while (current_id <= next_square->get_id()) {
            board_scene->removeItem(p);
            p->set_location(squares_[current_id]);
            board_scene->addItem(p);
            //board_scene->update();
            current_id++;
        }
        move_string +=  std::to_string(next_square->get_id() - current_square->get_id()) + " spaces.";
        if (next_square->get_powerup()!=Powerup::None){
            p->set_powerup(next_square->get_powerup());
        }
    } else  {
        move_string += "0 spaces";
    }

    ui->moveLabel->setText(move_string .c_str());

    //CheckForWinner(next_square);

    Powerup powup;
    std::string pow_label = "Current PowerUps: \n";

    for (int i = 0; i < players_.size(); i++) {
        powup = players_[i]->get_powerup();
//        if (i == active_player_) {
//            pow_label += "<font color=\"blue\">Player " + std::to_string(i+1) + ": " + Stringify(powup) + "</font>\n";
//        }
        pow_label += "Player " + std::to_string(i+1) + ": " + Stringify(powup) + "\n";
    }
    ui->label->setText(pow_label.c_str());

//    CheckForWinner(next_square);

}

void BoardWindow::CheckForWinner(Square* next_square){
    // check for winner
    if (next_square == squares_[squares_.size()-1]){

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

        if (players_[active_player_]->get_powerup() != Powerup::None) {
            ui->powerup_button->setEnabled(true);
            QString tmp = ui->turnLabel->text();
            tmp.append("\nYou may also apply your current power up.");
            ui->turnLabel->setText(tmp);
        } else {
            ui->powerup_button->setEnabled(false);
        }
    }
    Player *next_player = players_[active_player_];
    if (next_player->get_humanity()==false){ //iz a computer

        ui->drawcard_button->setEnabled(false);
        ui->moveplayer_button->setEnabled(false);

        MoveComputer();
    }

    UpdateGraph();
}

void BoardWindow::MoveComputer(){
    QThread::msleep(1000);
    QColor color_needed;
    std::string card_string = "PLAYER " + std::to_string(active_player_ + 1) + " drew a ";
    qDebug()<<"iz a coputer";
    Player* p = players_[active_player_];
    qDebug()<<p->get_id();
    qDebug()<<active_player_;
    //on_drawcard_button_clicked();
    //on_moveplayer_button_clicked();

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
            board_scene->removeItem(p);
            p->set_location(plus_one);
            board_scene->addItem(p);
            if (plus_one->get_powerup()!=Powerup::None){
                p->set_powerup(plus_one->get_powerup());
            }

            CheckForWinner(plus_one);
        } else { //its backward
            qDebug()<<"backward";
            Square *current_square = p->get_location();
            int curr_id = current_square->get_id();
            Square *minus_one = squares_[curr_id-1];
            board_scene->removeItem(p);
            p->set_location(minus_one);
            board_scene->addItem(p);
            if (minus_one->get_powerup()){
                p->set_powerup(minus_one->get_powerup());
            }
        }
    }

    p->set_powerup(Powerup::None);



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
    card_scene->removeItem(current_card_);
    current_card_= new Card(color_needed);
    card_scene->addItem(current_card_);

    Square *current_square = p->get_location();
    Square *next_square = GetNextSquare(current_square, current_card_->get_color());
    MovePlayer(next_square, current_square);

    ui->drawcard_button->setEnabled(true);
    CheckForWinner(next_square);

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
        QGraphicsRectItem* item = new QGraphicsRectItem(i*35,130,25,-wins*10);
        graph_scene->addItem(item);
    }
    graph_scene->update();
    graph_view->update();
}

void BoardWindow::on_newgame_button_clicked()
{
    popup->show();
}

void BoardWindow::on_reset_button_clicked()
{
    std::vector<int> wins = {};
    for (int i = 0; i<4; i++){
        Player *p = players_[i];
        wins.push_back(p->get_wins());
        board_scene->removeItem(p);
    }
    NewGame(num_humans_, wins);
}
