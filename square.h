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

enum Powerup {Double, PlusOne, Backward, None};

class Square : public QObject, public QGraphicsItem {

    Q_OBJECT

public:
    Square(const int x, const int y, int id);

    std::pair<int, int> get_location();

    int get_id() const {return id_;};

    //get_value() // type of value/?

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    QColor get_color() { return color_; };

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    static int get_width() { return width_; }

signals:
    // for distance
    void SquareSelected(Square *sq);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int location_;

    int id_;

    int x_;

    int y_;

    QColor color_;

    static const int width_ = 75;

    friend bool operator==(const Square &first, const Square &other);

};


class PowerSquare: public Square {
public:
    PowerSquare(const int x, const int y, int id);
private:
    Powerup powerup_;
};

#endif // SQUARE_H
