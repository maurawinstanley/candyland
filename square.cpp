#include "square.h"

Square::Square(const int x, const int y, int id)
{
    int color_num = id % 5;
    switch (color_num) {
        case 0:
            color_ = QColor(244, 154, 194);
            break;
        case 1:
            color_ = QColor(154, 239, 244);
            break;
        case 2:
            color_ = QColor(154, 244, 204);
            break;
        case 3:
            color_ = QColor(239, 115, 108);
            break;
        case 4:
            color_ = QColor(239, 244, 154);
            break;

    }

    x_ = x;
    y_ = y;
    id_ = id;
}

PowerSquare::PowerSquare(const int x, const int y, int id) : Square(x, y, id) {
    qDebug() << "making a powerSquare at " << id;
    int num = rand() % 3;
    switch (num) {
        case 0:
            powerup_ = Powerup::Double;
            break;
        case 1:
            powerup_ = Powerup::PlusOne;
            break;
        case 2:
            powerup_ = Powerup::Backward;
            break;
    }
}
/**
    basic func to create rect of ell
    @return void
*/
QRectF Square::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

QPainterPath Square::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}

/**
    Basic setup of ui for Square
    @return void
*/
void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    //QPen p = painter->pen();
    painter->setBrush(QBrush(color_));
    if (get_powerup()!=Powerup::None){
        QPen pen(Qt::black, 5);
        painter->setPen(pen);
    }

    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    //painter->setPen(p);
    painter->setBrush(b);
}


/**
    signal to signify that the cell was clicked
    @return void
*/
void Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // update this QGraphicsItem (force it to re-draw)
    //update();
    emit SquareSelected(this);
}



bool operator==(const Square &first, const Square &other) {
    return true;
    //return first.get_id() == other.get_id();
}




std::pair<int, int>Square:: get_location(){
    std::pair<int, int> ret;
    ret.first = x_;
    ret.second = y_;
    return ret;


}


