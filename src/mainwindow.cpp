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

    connect(this, SIGNAL(buttonMovePressP1(int)), ui->openGLWidget, SLOT(movePlayer1(int)));
    connect(this, SIGNAL(buttonMovePressP2(int)), ui->openGLWidget, SLOT(movePlayer2(int)));

    counter = MIN(5);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimerCount()));

}

bool MainWindow::eventFilter(QObject *target, QEvent *e)
{
    Q_UNUSED(target);

    /*bool handled = false;
    if ( e->type() == QEvent::KeyPress )
    {
        QKeyEvent *keyEvent = (QKeyEvent *)e;

        if ( keyEvent->key() == Qt::Key_Left )
        {
            iP1Direction = (iP1Direction == 0 ? -5 : 0);
            handled = true;
        }
        else if ( keyEvent->key() == Qt::Key_Right )
        {
            iP1Direction  = (iP1Direction == 0 ? 5 : 0);
            handled = true;
        }
    }

    return handled;*/

    qDebug() << e->type() << target;

    return true;
}


void MainWindow::keyPressEvent(QKeyEvent* event) {

    if (!event->isAutoRepeat()) {
        switch (event->key()) {

        case Qt::Key_Up:
            emit buttonMovePressP1(-1);
            break;

        case Qt::Key_Down:
            emit buttonMovePressP1(1);
            break;

        case Qt::Key_W:
            emit buttonMovePressP2(-1);
            break;

        case Qt::Key_S:
            emit buttonMovePressP2(1);
            break;

        case Qt::Key_Space:
            if (started){
                started = false;
                timer->stop();
                this->ui->labelStatus->setText(QString("O jogo parado!!! Precione ESPAÇO para reiniciar."));
            } else {
                started = true;
                timer->start(1000);
                this->ui->labelStatus->setText(QString("Começa o jogo!!! Precione ESPAÇO para pausar."));
            }
            emit buttonStart();
            break;

        default:
            break;
        }
    }
    //qDebug()<< event->key() << event->type();
}


MainWindow::~MainWindow()
{
    delete ui;
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
        counter = 300;
    }
}


