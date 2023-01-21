#include "person.h"
#include "qdebug.h"

person::person(QObject *parent)
    : QObject{parent}
{
    qInfo() << "Person object :" << this << " is constructed!";
}

person::~person()
{
    qInfo() << "Person object :" << this << " is destructed!";
}

QString person::getName() const
{
    return name;
}

void person::setName(const QString &s)
{
    name = s;
}

int person::getAge() const
{
    return age;
}

void person::setAge(const int a)
{
    age = a;
}





