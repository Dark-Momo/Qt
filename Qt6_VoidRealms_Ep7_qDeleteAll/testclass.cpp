#include "testclass.h"

testClass::testClass(QObject *parent)
    : QObject{parent}
{
    qInfo() << " Will Construct obj " << this << " with parent " << parent;
}

testClass::~testClass()
{
    qInfo() << " Will Donstruct obj " << this << " with parent " << this->parent();
}
