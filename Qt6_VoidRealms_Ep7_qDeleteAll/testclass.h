#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>
#include <QDebug>

class testClass : public QObject
{
    Q_OBJECT
public:
    explicit testClass(QObject *parent = nullptr);
    ~testClass();

signals:

};

#endif // TESTCLASS_H
