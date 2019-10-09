#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qlabel.h>
#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QPalette colorBlack(QPalette::Window, Qt::black);
    ui->board->setPalette(Qt::black);
}

Array2D<QLabel*> MainWindow::drawMap(Map *map, uint8_t size, QPixmap &labelData, QWidget *parent )
{
    uint8_t height = map->getMapHeight();
    uint8_t width = map->getMapWidth();

    //Klasa tworząca prostokąt, służący do rysowania mapy
    QRect rect(0, 0, size, size);

    Array2D<QLabel*> labelArray;

    uint8_t y;
    for(y = 0; y < height; ++y)
    {
        std::vector<QLabel*> rowLabel;

        uint8_t x;
        for(x = 0; x < width; ++x)
        {
            if(static_cast<bool>(map->getMap()[y][x]))
            {
                QLabel *label = new QLabel(parent);
                 //label->setAutoFillBackground(true);
                label->setPixmap(labelData);
                label->setGeometry(rect);
                label->move(x * size, y * size);

                rowLabel.push_back(label);
            }
            else
            {
                rowLabel.push_back(nullptr);
            }
        }
        labelArray.push_back(rowLabel);
    }

    return labelArray;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    QPoint point = m_player->getPoint();

    if(event->key() == Qt::Key_Down)
    {
        if(point.y() + 1 < m_map->getMapHeight())
        {
            point.setY(point.y() + 1);
            m_pacman->setPixmap(m_player->MoveDown());
        }
    }
    else if(event->key() == Qt::Key_Up)
    {
        if(point.y() - 1 >= 0)
        {
            point.setY(point.y() - 1);
            m_pacman->setPixmap(m_player->MoveUp());
        }
    }
    else if(event->key() == Qt::Key_Left)
    {
        if(point.x() - 1 >= 0)
        {
            point.setX(point.x() - 1);
            m_pacman->setPixmap(m_player->MoveLeft());
        }
    }
    else if(event->key() == Qt::Key_Right)
    {
        if(point.x() + 1 < m_map->getMapWidth())
        {
            point.setX(point.x() + 1);
            m_pacman->setPixmap(m_player->MoveRight());
        }
    }

    QLabel * foodLabel = m_foodLabelArray[point.y()][point.x()];
    if(foodLabel != nullptr && !foodLabel->isHidden())
    {
        m_foodEatLabel->setText(QString::number(m_foodEat++));
        foodLabel->hide();
    }

    if(!m_map->isHigh(point.x(), point.y()))
    {
        m_player->setPoint(point);
        m_pacman->setGeometry(m_player->calculateRect(m_blockSize));
    }



    if (m_foodEat > 85)
    {
        QFont msgf( "Arial", 20, QFont::Bold);
        QMessageBox msgBox;
        msgBox.setFont(msgf);
        msgBox.setText("Koniec gry!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:

            QApplication::quit();
              break;
        }

    }

}

void MainWindow::CreateGame()
{
    //********************************************************************************
    //Stworzenie obiektu klasy Map
    m_map = new Map();

    //Mapa
    Array2D<uint8_t> boardArray = {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0},
                    {0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0},
                    {0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
                    {0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
                    {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0}
                   };
    m_map->setMap(boardArray);

    //********************************************************************************
    //Food map
    Array2D<uint8_t> foodMapArray;
    foreach (const std::vector<uint8_t> &row, boardArray) {
        std::vector<uint8_t> foodRow;
        foreach (const uint8_t &col, row) {
            (static_cast<bool>(col)) ? foodRow.push_back(0) : foodRow.push_back(1);
        }
        foodMapArray.push_back(foodRow);
    }

    //Stworzenie jedzenia na mapie
    m_foodMap = new Map();
    m_foodMap->setMap(foodMapArray);




    //********************************************************************************
    QPixmap wallColor(m_blockSize, m_blockSize);
    wallColor.fill(Qt::blue);

    //********************************************************************************
    //Rysowanie mapy
    drawMap(m_map, m_blockSize, wallColor, ui->board);

    //********************************************************************************
    //Rysowanie zarcia
    QPixmap foodColor ("C:/Users/User/Desktop/kebab.png");
    m_foodLabelArray = drawMap(m_foodMap, m_blockSize, foodColor, ui->board);


    //********************************************************************************
    /*Obiekt klasy Player (potrzebny do zastosowania metody KeyPressEvent,
    czyli poruszania się postacią)*/
    m_player = Player::getInstance();
    m_player->setPoint(QPoint(9, 6));

    QPixmap mypix ("C:/Users/User/Desktop/pacleft.png");

    //Obiekt klasy QLabel, za pomocą którego porusza się player (gracz)
    m_pacman = new QLabel(ui->board);
    m_pacman->setGeometry(m_player->calculateRect(50) );
    //pacman->setAutoFillBackground(true);
    m_pacman->setPixmap(m_player->MoveUp());
    m_pacman->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_pacman->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    m_pacman->raise();


    QFont f( "Arial", 15, QFont::Bold);
    m_foodEatLabel = new QLabel(ui->board);

    m_HowMuchEatenLabel = new QLabel(ui->board);
    m_HowMuchEatenLabel->setText("Ilość zjedzonych kebabów: ");
    m_HowMuchEatenLabel->setGeometry(QRect(450, 400, 350, 50));
    m_HowMuchEatenLabel->setFont( f);

    m_foodEatLabel->setText(QString::number(m_foodEat));
    m_foodEatLabel->setGeometry(QRect(800, 400, 50, 50));

    m_foodEatLabel->setFont( f);

    m_foodEatLabel->raise();
    //label->move(x * size, y * size);
}



void MainWindow::on_pushButton_clicked()
{
    CreateGame();
    QObjectList children = ui->board->children();
    foreach ( QObject* ob, children) {
        qobject_cast<QWidget*>(ob)->show();
    }

    ui->pushButton->hide();
    ui->pushButton-> setFocusPolicy(Qt::NoFocus );

    ui->board->setFocusPolicy(Qt::StrongFocus );
}


