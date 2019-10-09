#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QGridLayout>
#include <QPushButton>

#include "player.h"
#include "map.h"
#include "food.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void CreateGame();
    void DeleteGame();

private:
    void update();
    Array2D<QLabel*> drawMap(Map *map, uint8_t size, QPixmap &labelData, QWidget *parent );

protected:
    void keyPressEvent(QKeyEvent* event);


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    uint8_t m_blockSize = 50;
    Map *m_map;
    Map *m_foodMap;
    Array2D<QLabel*> m_foodLabelArray;
    Player *m_player;
    QLabel *m_pacman;
    QLabel *m_HowMuchEatenLabel;
    QLabel *m_foodEatLabel;

    uint8_t m_foodNumber = 0;
    uint8_t m_foodEat = 0;

    QPushButton *endButton;
};

#endif // MAINWINDOW_H
