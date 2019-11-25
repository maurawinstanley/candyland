#include "player.h"

Player::Player(int id, bool is_human)
{
    color_ = QColor(255,20,147);
    powerup_ = None;
    is_human_ = is_human;
    x_ = 675;
    y_ = 300;
}

Player* PlayerFactory::createCpu(int id, bool is_human) {
    Player* p = new Player(id, false);
    return p;
}


Player* PlayerFactory::createHuman(int id, bool is_human) {
    Player* p = new Player(id, true);
    return p;
}

//QColor Cell::alive_color_ = QColor(255,20,147);
//QColor Cell::dead_color_ = QColor(255, 255, 255);

bool operator==(const Player &first, const Player &other) {
    return true;
    //return first.get_id() == other.get_id();
}

QRectF Player::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}
/**
    basic func to add ellipse for cell
    @return void
*/
QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addEllipse(x_, y_, width_, width_);
    return path;
}

/**
    Basic setup of ui for cell
    @return void
*/
void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    painter->setBrush(b);
}

void Player::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // update this QGraphicsItem (force it to re-draw)
    //update();
    emit PlayerSelected(this);
}
