#ifndef KDTREE_H
#define KDTREE_H

#include <QObject>

class KDTree : public QObject
{
    Q_OBJECT
public:
    explicit KDTree(QObject *parent = 0);

signals:

public slots:
};

#endif // KDTREE_H