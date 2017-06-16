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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "engine/glwidget.h"

#include <QTimer>
#include <QMainWindow>


typedef enum {
    W = 87,
    S = 83,
    ENTER = 16777220,
    LEFT = 16777234,
    UP = 16777235,
    RIGHT = 16777236,
    DOWN = 16777237,


} moveButtons;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool started;

    void updateLCD(int seconds);


public slots:
    void updateTimerCount();

protected:
    void keyPressEvent(QKeyEvent* event);
    virtual bool eventFilter(QObject *, QEvent *);

signals:
    void buttonMovePressP1(int);
    void buttonMovePressP2(int);

    void buttonStart();
    void matchIsOver();

private:

    int counter;

    QTimer *timer;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
