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

#define MIN(A) A * 60

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    started = false;
    connect(this, SIGNAL(buttonStart()), ui->openGLWidget, SLOT(startMatch()));
    connect(this, SIGNAL(matchIsOver()), ui->openGLWidget, SLOT(finishMatch()));

    counter = MIN(3) + 1;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimerCount()));

    connect(this, SIGNAL(buttonMovePress(int)), ui->openGLWidget->player1, SLOT(movePlayer(int)));
    connect(ui->openGLWidget->player1, SIGNAL(takeGoal(int)), this, SLOT(addGoalLCD(int)));
    connect(ui->openGLWidget->player2, SIGNAL(takeGoal(int)), this, SLOT(addGoalLCD(int)));
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
            started = false;
            timer->stop();
            this->ui->labelStatus->setText(QString("O jogo parado!!! Precione ESPAÇO para reiniciar a partida"));
        } else {
            started = true;
            timer->start(1000);
            this->ui->labelStatus->setText(QString("Começa o jogo!!! Precione ESPAÇO para parar a partida"));
        }
        emit buttonStart();
        break;

    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
    QMainWindow::keyPressEvent(event);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addGoalLCD(int id)
{
    switch (id) {
    case 2:
        ui->lcdNumber1->display(ui->lcdNumber1->value() + 1);

        break;

    case 1:
        ui->lcdNumber2->display(ui->lcdNumber2->value() + 1);
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

void MainWindow::updateTimerCount()
{
    counter--;
    updateLCD(counter);

    if(counter == 0){
        timer->stop();
        emit matchIsOver();

        QString resultado;
        if (ui->lcdNumber1->value() > ui->lcdNumber2->value())
            resultado = QString("Fim de Jogo! E o time do São Paulo vence o partida!");
        else if (ui->lcdNumber1->value() < ui->lcdNumber2->value())
            resultado = QString("Fim de Jogo! E o time do Corinthians vence a partida!");
        else
            resultado = QString("Fim de jogo! E a partida acaba empatada");

        ui->labelStatus->setText(resultado);
        counter = 300;
    }
}


