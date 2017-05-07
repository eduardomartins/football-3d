#ifndef PHISICS_H
#define PHISICS_H

#include <QObject>

const float GRAVITY = 9.806401351782f;

class Phisics : public QObject
{
    Q_OBJECT
public:
    explicit Phisics(QObject *parent = 0);

signals:

public slots:
};

#endif // PHISICS_H
