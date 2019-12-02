#ifndef CARD_H
#define CARD_H

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QColor>
#include <QGraphicsItem>
#include <string>


class Card : public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    Card(QColor color);


    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static int get_width() { return width_; }
    static int get_height() { return height_; }


private:

    QColor color_;

    static const int width_ = 320;
    static const int height_ = 140;

};

#endif // CARD_H
