#include <QDebug>

#include "qobjectexample.h"

QObjectExample::QObjectExample(QObject *parent)
    : QObject{parent}
{

}

void QObjectExample::dosomething()
{
    qInfo() << "In slot - dosomething(). Will emit close()";
    emit close(); // We can emit signal in the class's slot.
}
