#include "square.h"

Square::Square(QColor color, const int x, const int y, int id)
{
    this->color_ = color;
    x_ = x;
    y_ = y;
    id_ = id;
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
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
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
