#include <QCoreApplication>

#include <QMap>
#include <QSharedDataPointer>

#include "person.h"

// Use a QString 'nickName' to associate with a person object.
typedef QMap<QString, QSharedPointer<person>> NickName;

void setPersonInstance(NickName &family)
{
    // NickName family;
    for (int i = 0; i < 3; i++)
    {
        QSharedPointer<person> ptr(new person());
        ptr->setName("UnkownName" + QString::number(i));
        ptr->setAge(i);
        family.insert("UnkownPerson" + QString::number(i), ptr);
    }
}

void showPersonInstance(NickName &family)
{
    /*
    foreach(QString key, family.keys())
    {
        qInfo() << family[key]->getName();
        qInfo() << family[key]->getAge();
    }
    */

    foreach(QString key, family.keys())
    {
        QSharedPointer<person> ptr = family.value(key);
        qInfo() << key << ":" << ptr->getName() << ptr->getAge();
    }

}

// Here we add key and its value without checking whether the key already exists.
// When we add the 2nd instance with the same key, at inserting, the value of the 1st
// instance, here, the sharedpointer, will be deleted automatically.
void addPersonInstance(NickName &family, QString str)
{
    QSharedPointer<person> ptr(new person());
    ptr->setName(QString(str));
    ptr->setAge(10);
    qInfo() << "Before insert added item...";
    family.insert("TestAdded", ptr);
    qInfo() << "After insert added item...";
}
// Output:
/*
-- Add 2 instance:
Person object : person(0x564e82053f40)  is constructed!
Before insert added item...
After insert added item...
Person object : person(0x564e820540f0)  is constructed!
Before insert added item...
Person object : person(0x564e82053f40)  is destructed!
After insert added item...
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Basic Test
    QMap<QString, int> stuInfo;
    stuInfo.insert(QString("Jian Lao"), 41);
    qInfo() << stuInfo;

    stuInfo.insert(QString("Yu Han"), 39);
    qInfo() << stuInfo;

    qInfo() << stuInfo["Yu Han"];
    qInfo() << "-------------------------------------------";

    // Complex Example
    NickName family;
    setPersonInstance(family);

    qInfo() << "-- Show family info:";
    showPersonInstance(family);

    qInfo() << "-- Add 2 instance:";
    addPersonInstance(family, "Huang1");
    addPersonInstance(family, "Huang2");
    qInfo() << "-- Show family info:";
    showPersonInstance(family);


    return a.exec();
}
