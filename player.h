#ifndef PLAYER_H
#define PLAYER_H
#include "square.h"
#include <QColor>
#include <QGraphicsItem>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>



class Player: public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    Player(int id, bool is_human);

    Square* get_location() { return location_; };

    void set_location(Square* loc) { location_ = loc; };

    int get_wins() { return wins_; };

    void IncrementWins() { wins_++; };

    Powerup get_powerup() { return powerup_; };

    void set_powerup(Powerup powerup) { powerup_ = powerup; };

    void UsePowerup() { powerup_ = None;};

    void drawCard();

    void Move();

    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

signals:
    // for distance
    void PlayerSelected(Player *p);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Square* location_;

    int wins_;

    Powerup powerup_;

    int id_;

    bool is_human_;

    QColor color_;

    static const int width_ = 15;

    int x_;

    int y_;


    friend bool operator==(const Player &first, const Player &other);

};



class PlayerFactory {
public:


    static Player* createHuman(int id, bool is_human);

    static Player* createCpu(int id, bool is_human);

};


#endif // PLAYER_H
