#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>

class Character : public QObject
{
    Q_OBJECT
public:
    explicit Character(QObject *parent = 0);

signals:

public slots:
};

#endif // CHARACTER_H