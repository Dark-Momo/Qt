#include <QCoreApplication>
#include <QDebug>

#include "qobjectexample.h"

// Defining a function that passing by value of QObject is fine.
// void funcPassByValue(QobjectExample qobjExam)
//{
//}

void funcPassByRef(QobjectExample & qobjExam)
{
   qInfo() << "In funcPassByRef(), with input obj address : " << &qobjExam;
}

void funcPassByPointer(QobjectExample * qobjExam)
{
   qInfo() << "In funcPassByPtr(), with input obj address : " << qobjExam;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QobjectExample qobjInst;

    // ----------------------------------------------------------------------------
    // Below has error since it passes a qobject class by value.
    // QObject based classes have no copy constructor, and move(), while passing
    // a class object by value involves copy constructor.

    // funcPassByValue(qobjInst);
    // ----------------------------------------------------------------------------

    // Below is passing by reference.
    funcPassByRef(qobjInst);

    // Below is passing by pointer.
    funcPassByPointer(&qobjInst);

    return a.exec();
}
