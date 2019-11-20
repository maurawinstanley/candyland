#ifndef SQUARE_H
#define SQUARE_H
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QColor>
#include <QGraphicsItem>

#include <string>
class Square : public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    Square(QColor color, const int x, const int y, int id);

    //int get_location() { return location_; };

    //get_value() // type of value/?
    QRectF boundingRect() const override;
    QPainterPath shape() const override;



    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static int get_width() { return width_; }

signals:
    // for distance
    void SquareSelected(Square *sq);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    //int location_;

    int id_;


    int x_;

    int y_;

    QColor color_;

    static const int width_ = 40;

    friend bool operator==(const Square &first, const Square &other);
};

#endif // SQUARE_H
