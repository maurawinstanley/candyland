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

    Card DrawCard();

    void TakeTurn();

private slots:
    void on_pushButton_clicked();

    void on_finish_clicked();
    void changeWindow();




private:
    Ui::BoardWindow *ui;
    Popupwindow *popup;

    std::vector<Player*> players_;
};

#endif // BOARDWINDOW_H
