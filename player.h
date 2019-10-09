#ifndef PLAYER_H
#define PLAYER_H

#include <qwidget.h>
#include <qlabel.h>
#include <QKeyEvent>


class Player
{
public:
    static Player *getInstance();

private:
    Player();
    Player(const Player&);
    Player &operator=(const Player&);

public:

    //Setters
    void setX(uint8_t x);
    void setY(uint8_t y);
    void setPoint(QPoint point);

    //Getters
    uint8_t getX();
    uint8_t getY();
    QPoint getPoint();
    //Direction getDirection();
    //Direction setDirection(Direction d);

    QRect calculateRect(uint8_t step);

    //enum class Direction {
    //    Up,
//        Down,
//        Left,
     //   Right
  //  };

    QPixmap MoveUp();
    QPixmap MoveDown();
    QPixmap MoveLeft();
    QPixmap MoveRight();

private:
    QPoint m_point;
    QPixmap transPixmap;
    QPixmap mypix;

    static Player *s_instance;
};

#endif // PLAYER_H
