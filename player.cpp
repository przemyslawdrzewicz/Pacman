#include "player.h"

Player *Player::s_instance = nullptr;

Player *Player::getInstance()
{
    if(s_instance == nullptr)
    {
        s_instance = new Player();
    }
    return s_instance;
}

Player::Player()
{
    mypix.load("C:/Users/User/Desktop/pacleft.png");
}

void Player::setX(uint8_t x)
{
    m_point.setX(x);
}

void Player::setY(uint8_t y)
{
    m_point.setY(y);
}

//Getters
uint8_t Player::getX()
{
    return m_point.y();
}
uint8_t Player::getY()
{
    return m_point.x();
}

QRect Player::calculateRect(uint8_t step)
{
    QRect rect;
    rect.setTop(step * m_point.y());
    rect.setLeft(step * m_point.x());
    rect.setWidth(40);
    rect.setHeight(40);

    return rect;
}

void Player::setPoint(QPoint point)
{
    m_point = point;
}

QPoint Player::getPoint()
{
    return m_point;
}


QPixmap Player::MoveUp()
{
    QTransform transform;
    QTransform trans = transform.rotate(90);
    transPixmap = QPixmap(mypix.transformed(trans));

    return transPixmap;
}


QPixmap Player::MoveDown()
{
    QTransform transform;
    QTransform trans = transform.rotate(-90);
    transPixmap = QPixmap(mypix.transformed(trans));

    return transPixmap;
}

QPixmap Player::MoveLeft()
{
    QTransform transform;
    QTransform trans = transform.rotate(0);
    transPixmap = QPixmap(mypix.transformed(trans));

    return transPixmap;
}

QPixmap Player::MoveRight()
{
    QTransform transform;
    QTransform trans = transform.rotate(180);
    transPixmap = QPixmap(mypix.transformed(trans));

    return transPixmap;
}
