#include "card.h"

Card::Card(QColor color)
{
  color_ = color;
}

/**
    basic func to create rect of ell
    @return void
*/
QRectF Card::boundingRect() const
{
    return QRectF(0, 0, width_, height_);
}

QPainterPath Card::shape() const
{
    QPainterPath path;
    path.addRoundedRect(QRectF(5, 5, width_, height_), 10, 10);
    return path;
}

/**
    Basic setup of ui for Square
    @return void
*/
void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawRoundedRect(QRect(5,5, this->width_, this->height_), 10,10);
    painter->setBrush(b);
}
