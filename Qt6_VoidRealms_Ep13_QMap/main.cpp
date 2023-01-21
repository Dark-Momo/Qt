#include <QCoreApplication>

#include <QMap>
#include <QSharedDataPointer>

#include "person.h"

// Use a QString 'nickName' to associate with a person object.
typedef QMap<QString, QSharedPointer<person>> nickName;

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

    // Complex Example





    return a.exec();
}
