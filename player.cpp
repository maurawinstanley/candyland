#include "player.h"

Player::Player(int id, bool is_human, QIcon icon)
{
    color_ = QColor(255,20,147);
    powerup_ = None;
    is_human_ = is_human;
    x_ = 675;
    y_ = 300;
    wins_ = 0;

    icon_ = icon;
}
/*void Player::drawIcon(QPainter *painter, QPoint pos)
{
    QPixmap pixmap = icon.pixmap(QSize(22, 22),
                                   isEnabled() ? QIcon::Normal
                                               : QIcon::Disabled,
                                   isChecked() ? QIcon::On
                                               : QIcon::Off);
    painter->drawPixmap(pos, pixmap);
}
void Player::AddIcon(int x, int y) {
    QPixmap pixmap("://icons/icon_file.png");
    Directory *test = new DataFile(x, y, pixmap);
    addItem(test);

}*/


Player* PlayerFactory::createCpu(int id,QIcon icon) {
    Player* p = new Player(id, false, icon);
    return p;
}


Player* PlayerFactory::createHuman(int id, QIcon icon) {
    Player* p = new Player(id, true, icon);
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

    painter->drawRect(QRect(this->x_, this->y_, 0, 0));
    painter->setBrush(b);

    //QIcon icon = QIcon(":/Documents/prog_proj/in_class/images/candy1.svg");
    QRect rect = QRect(x_, y_, width_, width_);
    icon_.paint(painter, rect, Qt::AlignCenter);

}

/*void Player::DrawPlayer(QPainter *painter, int value){
    QIcon icon = piece(value);
    QRect rect = QRect(x_, y_, width_, width_);
    icon.paint(painter, rect, Qt::AlignCenter);
}*/


void Player::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // update this QGraphicsItem (force it to re-draw)
    //update();
    emit PlayerSelected(this);
}
