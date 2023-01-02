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

    // ------------------------------------------------------------------------------------------
    // Below has error since it passes a qobject class by value.
    // QObject based classes have NO Copy Constructor, and Move(), while passing
    // a class object by value involves copy constructor.
    // The reason is, if you copy a qobject, the connect() relation will also be
    // copied, which will make system complex, and unexpected. For example, you have
    // a controller controlling a LED by connect(), if you copy that controller, you will
    // have 2 controller controlling the same LED, which makes things complex. More issues
    // will come out when you delete them.

    // funcPassByValue(qobjInst);
    // ------------------------------------------------------------------------------------------

    // Below is passing by reference.
    funcPassByRef(qobjInst);

    // Below is passing by pointer.
    funcPassByPointer(&qobjInst);

    return a.exec();
}
