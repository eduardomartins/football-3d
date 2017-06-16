#ifndef GAME_H
#define GAME_H

#include "src/ball.h"

#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = 0);

    void handleCollitions();

signals:

public slots:

private:
    Ball *balls[2];
    int score[2];
};

#endif // GAME_H
