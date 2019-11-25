#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H

#include <QMainWindow>
#include "popupwindow.h"
#include "player.h"

enum Card {Blue, Green, Red, Yellow, Pink};


namespace Ui {
class BoardWindow;
}

class BoardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BoardWindow(QWidget *parent = nullptr);
    ~BoardWindow();

    void NewGame(int num_players);

    void SetUpBoard();

    Card DrawCard();

    void TakeTurn(Player *p);

    Square* GetNextSquare(Square* previous_square, QColor color_needed);

private slots:
    void on_pushButton_clicked();

    void on_finish_clicked();
    void changeWindow();


    void on_powerup_button_clicked(Player *p);

    void on_drawcard_button_clicked(Player *p);

private:
    Ui::BoardWindow *ui;
    QGraphicsScene *scene;
    QGraphicsScene *graph_scene;
    Popupwindow *popup;

    std::vector<Player*> players_;
    std::vector<Square*> squares_;

};

#endif // BOARDWINDOW_H
