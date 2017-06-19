/*
 * MIT License
 *
 * Copyright (c) 2017 Eduardo Sant'Anna Martins <eduardo@eduardomartins.site>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MIN(A) A * 60 + 1

#define TIME_MATCH MIN(5)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    started = false;
    stopped = false;

    counter = TIME_MATCH;
    wait_conter = 5; // Espera 5 segundos

    timer = new QTimer(this);
    wait = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimerCount()));
    connect(wait, SIGNAL(timeout()), this, SLOT(waitMakeGoal()));

    connect(this, SIGNAL(buttonStart(bool)), ui->openGLWidget, SLOT(startMatch(bool)));
    connect(this, SIGNAL(matchIsOver(bool)), ui->openGLWidget, SLOT(finishMatch(bool)));

    connect(ui->openGLWidget->player1, SIGNAL(updateLCD(int)), this, SLOT(addGoalLCD(int)));
    connect(ui->openGLWidget->player2, SIGNAL(updateLCD(int)), this, SLOT(addGoalLCD(int)));

    connect(this, SIGNAL(buttonMovePress(int)), ui->openGLWidget->player1, SLOT(movePlayer(int)));
}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {

    case Qt::Key_Up:
        emit buttonMovePress(-1);
        break;

    case Qt::Key_Down:
        emit buttonMovePress(1);
        break;

    case Qt::Key_Space:
        if (started){
            if (stopped) {
                wait->stop();
                wait_conter = 5;
                stopped = false;
                timer->start(1000);
                this->ui->labelStatus->setText(QString("Começa o jogo!!! Precione ESPAÇO para parar a partida"));
            } else {
                stopped = true;
                timer->stop();
                this->ui->labelStatus->setText(QString("O jogo parado!!! Precione ESPAÇO para reiniciar a partida"));

            }
        } else {
            started = true;
            stopped = false;
            timer->start(1000);
            this->ui->labelStatus->setText(QString("Bola rolando!!! Precione ESPAÇO para parar a partida"));
        }

        emit buttonStart(stopped);
        break;

    }
    QMainWindow::keyPressEvent(event);
}



MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete wait;
}

void MainWindow::addGoalLCD(int id)
{
    stopped = true;
    timer->stop();
    emit buttonStart(stopped);

    wait->start(1000);

    switch (id) {
    case 2:
        ui->lcdNumber1->display(ui->lcdNumber1->value() + 1);
        this->ui->labelStatus->setText(QString("O jogo parado!!! Precione ESPAÇO para reiniciar a partida"));
        break;

    case 1:
        ui->lcdNumber2->display(ui->lcdNumber2->value() + 1);
        this->ui->labelStatus->setText(QString("O jogo parado!!! Precione ESPAÇO para reiniciar a partida"));
        break;

    default:
        break;
    }
}


void MainWindow::updateLCD(int seconds)
{
    int min, sec;

    if (seconds > 60){
        min = seconds/60;
    } else {
        min = 0;
    }
    sec = seconds % 60;

    ui->lcdNumberMin->display(min);
    ui->lcdNumberSeg->display(sec);

}

void MainWindow::waitMakeGoal()
{
    this->ui->labelStatus->setText(QString("Goooool!!! Partida recomeça em %1...\n ou precione ESPAÇO para recomeçar").arg(QString::number(wait_conter)));
    --wait_conter;

    if (wait_conter == 0){
        wait->stop();
        wait_conter = 5;
        stopped = false;
        timer->start(1000);
        emit buttonStart(stopped);
        this->ui->labelStatus->setText(QString("Começa o jogo!!! Precione ESPAÇO para parar a partida"));
    }

}


void MainWindow::updateTimerCount()
{
    counter--;
    updateLCD(counter);

    if(counter == 0){

        timer->stop();


        started = false;

        emit matchIsOver(started);

        stopped = false;

        QString resultado;

        if (ui->lcdNumber1->value() > ui->lcdNumber2->value())
            resultado = QString("Fim de Jogo! E o time do São Paulo vence o partida!");
        else if (ui->lcdNumber1->value() < ui->lcdNumber2->value())
            resultado = QString("Fim de Jogo! E o time do Corinthians vence a partida!");
        else
            resultado = QString("Fim de jogo! E a partida acaba empatada");

        ui->labelStatus->setText(QString("%1\n Precione ESPAÇO para jogar uma nova partida").arg(resultado));

        ui->lcdNumber1->display(0.0);
        ui->lcdNumber2->display(0.0);

        counter = TIME_MATCH;
    }
}


