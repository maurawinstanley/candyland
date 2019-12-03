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
#include <QObject>
#include <QGraphicsScene>
#include <QMimeData>
#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QGraphicsSceneMouseEvent>
#include <queue>
#include <QIcon>



class Player: public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    Player(int id, bool is_human, QIcon icon);

    void drawIcon(QPainter *painter, QPoint pos);

    Square* get_location() { return location_; };

    void set_location(Square* loc) { location_ = loc; x_ = loc->get_x(); y_ = loc->get_y();};

    int get_wins() { return wins_; };

    int get_id() { return id_; };

    void IncrementWins() { wins_++; };

    void AddIcon(int x, int y);

    Powerup get_powerup() { return powerup_; };

    void set_powerup(Powerup powerup) { powerup_ = powerup; };

    void UsePowerup() { powerup_ = None;};

    void drawCard();

    void Move();

    void DrawPlayer(QPainter *painter, int value);


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

    static const int width_ = 35;

    int x_;

    int y_;

    int offset_;

    QIcon piece(int) const;

    std::string icon_string_;

    friend bool operator==(const Player &first, const Player &other);

    QIcon icon_;



};



class PlayerFactory {
public:


    static Player* createHuman(int id, QIcon icon);

    static Player* createCpu(int id, QIcon icon);

};


#endif // PLAYER_H
