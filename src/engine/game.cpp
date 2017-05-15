#include "game.h"


namespace {
    const float PI = 3.1415926535f;

    //The amount of time by which the state of the crab is advanced in each call
    //to a crab's step() method
    const float BALL_ACELERATION = 0.01f;
    //The amount of time it takes for a crab to accelerate from no speed to its
    //maximum speed
    const float TIME_TO_MAXIMUM_SPEED = 0.18f;
    //The maximum angle formed by the direction at which a ball is hit off of a
    //crab and the normal direction for the crab
    const float MAX_CRAB_BOUNCE_ANGLE_OFFSET = 0.85f * PI / 2;
    //The maximum speed of the human-controlled crab
    const float PLAYER_MAXIMUM_SPEED = 2.2f;
    //The amount of time it takes for a ball to fade into play
    const float BALL_FADE_IN_TIME = 0.5f;
    //The amount of time it takes for a ball to fade out of play
    const float BALL_FADE_OUT_TIME = 0.5f;
    //The radius of the balls
    const float BALL_RADIUS = 0.04f;
    //The speed of the balls
    const float BALL_SPEED = 1.0f;
    //The ideal number of balls in play
    const int NUM_BALLS = 2;
    //The amount of time by which the state of the game is advanced in each call
    //to the game's step() method
    const float GAME_STEP_TIME = 0.01f;

    //Returns a random float from 0 to < 1
    float randomFloat() {
        return (float)rand() / ((float)RAND_MAX + 1);
    }
}


Game::Game(QObject *parent) : QObject(parent)
{

}
