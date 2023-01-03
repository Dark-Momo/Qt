#include "testparentchild.h"

TestParentChild::TestParentChild(QObject *parent) : QObject{parent}
{
    qInfo() << "Construct :" << this << " with Parent : " << parent;
}

TestParentChild::~TestParentChild()
{
    // Don't have parent info here. So use this->parent(), or parent().
    qInfo() << "Destruct :" << this << " with Parent : " << this->parent();

    // When deleting an object, show what children it has.
    // Here, foreach() is a QT method.
    foreach(QObject * child, children()) // const QObjectList &	children() const
    {
        qInfo() << "Current qobject has child - " << child;
    }
    qInfo() << Qt::endl;
}
