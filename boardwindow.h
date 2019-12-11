#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H

#include <QMainWindow>
#include "popupwindow.h"
#include "card.h"
#include "player.h"

namespace Ui {
class BoardWindow;
}

class BoardWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BoardWindow(QWidget *parent = nullptr);
    ~BoardWindow();

    void NewGame(int num_players, std::vector<int> wins);

    void SetUpBoard();

    void MovePlayer(Square *next_square, Square *current_square);

    Square* GetNextSquare(Square* previous_square, QColor color_needed);

    void CheckForWinner(Square* next_square);


private slots:

    void MoveComputer();

    void on_finish_clicked();

    void on_powerup_button_clicked();

    void on_drawcard_button_clicked();

    void on_newgame_button_clicked();

    void on_moveplayer_button_clicked();

    void changeWindow();

    void UpdateGraph();

    void on_reset_button_clicked();

signals:
    // for distance
    void powerupUsed();

    void finish_clicked();

private:
    Ui::BoardWindow *ui;
    QTimer *timer_;
    QGraphicsScene *board_scene;
    QGraphicsScene *graph_scene;
    QGraphicsScene *card_scene;

    Popupwindow *popup;

    QGraphicsView* board_view;
    QGraphicsView* graph_view;
    QGraphicsView* card_view;

    Card* current_card_;

    std::vector<Player*> players_;
    std::vector<Square*> squares_;
    std::vector<Square*> power_squares_;
    int num_humans_;
    int active_player_;
    QMap<int, QIcon> player_icons_;

    bool game_over_;

};

#endif // BOARDWINDOW_H
