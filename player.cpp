#include "player.h"

Player::Player(int id, bool is_human, QIcon icon, int wins)
{
    color_ = QColor(255,20,147);
    powerup_ = None;
    is_human_ = is_human;
    x_ = 675;
    y_ = 300;
    wins_ = wins;
    id_ = id;
    icon_ = icon;
    qDebug()<<"ID";
    qDebug()<<id_;
    offset_ = id_*5;
}


Player* PlayerFactory::createCpu(int id, QIcon icon, int wins) {
    Player* p = new Player(id, false, icon, wins);
    return p;
}


Player* PlayerFactory::createHuman(int id, QIcon icon, int wins) {
    Player* p = new Player(id, true, icon, wins);
    return p;
}


bool operator==(const Player &first, const Player &other) {
    return true;
}

QRectF Player::boundingRect() const
{
    return QRectF(x_+offset_, y_+offset_, width_, width_);
}
/**
    basic func to add ellipse for cell
    @return void
*/
QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addEllipse(x_+offset_, y_+offset_, width_, width_);
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

    painter->drawRect(QRect(this->x_ , this->y_ , 0, 0));
    painter->setBrush(b);

    //QIcon icon = QIcon(":/Documents/prog_proj/in_class/images/candy1.svg");
    QRect rect = QRect(x_ +offset_, y_ +offset_, width_, width_);
    icon_.paint(painter, rect, Qt::AlignCenter);

}


void Player::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // update this QGraphicsItem (force it to re-draw)
    //update();
    emit PlayerSelected(this);
}
