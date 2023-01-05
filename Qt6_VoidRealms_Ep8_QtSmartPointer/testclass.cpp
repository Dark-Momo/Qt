#include "testclass.h"

TestClass::TestClass(QObject *parent)
    : QObject{parent}
{
    qInfo() << "Will Construct obj " << this << " with parent " << parent;
}

TestClass::~TestClass()
{
    qInfo() << "Will Destruct obj " << this << " with parent " << this->parent();
}

void TestClass::message(QString value)
{
    qInfo() << this << value;
}
