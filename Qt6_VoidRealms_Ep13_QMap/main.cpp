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
    qInfo() << "Show family info:";
    showPersonInstance(family);






    return a.exec();
}
