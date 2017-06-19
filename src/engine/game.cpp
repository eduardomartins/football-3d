#include "game.h"
#include <math.h>
#include <QDebug>

Game::Game(Player *player, Ball *ball, QObject *parent) : QObject(parent)
  ,Sy(-1500.0)
{
    timer = new QTimer(this);
    this->player = player;
    this->ball = ball;
    timer->start(100);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    connect(this, SIGNAL(updatePlayer(int)), this->player, SLOT(movePlayer(int)));


}

void Game::updateGame()
{

    // S = So + Vt

    Sox = ball->position[0];
    Soy = ball->position[1];

    Vx = ball->velocidade[0];
    Vy = ball->velocidade[1];

    t = (Sy - Soy)/ Vy;

    if (t >  0.0) {

        Sx = (Sox + Vx * t);

        int move = ((int) (Sx - player->position[0]) / 55.0);

        if (abs(move) >= 25)
            emit updatePlayer((move < 0.0 ? -1.1 : 1.1));
        else if (abs(move) >= 2)
            emit updatePlayer((move < 0.0 ? -1.0 : 1.0));
    }

}


Game::~Game()
{
    delete timer;
    timer->stop();
}


