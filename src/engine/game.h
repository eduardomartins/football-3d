#ifndef GAME_H
#define GAME_H

#include "scene.h"
#include <QTimer>
#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(Player *player, Ball *ball, QObject *parent = 0);
    ~Game();

public slots:
    void updateGame();

signals:
    void updatePlayer(int);

public slots:

private:

    bool lock;

    Ball *ball;
    Player *player;
    QTimer *timer;

    float Sx, Sox, Vx, Sy, Soy, Vy, t;
};

#endif // GAME_H
