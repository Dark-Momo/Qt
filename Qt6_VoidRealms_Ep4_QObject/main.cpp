// Most objects in QT inherits QObject. But not all, template class, such as QList, QString, are not.
// QObject is base of a lot of classes, providing basic functions, such as connect.

// This project requires an independent Qobject class. Creating a QObject class in QT needs to:
// 1. Right Click Project - Add new - C++ Class - Input Class Name, and Base Class : QObject
//    -- QObject type will, by default, select QObject and Q_OBJECT.
//    -- Custom Base Class select nothing, leaving you to do the selection.
//    Click Next, and Finish about Cmake path.
// 2. In CMakeLists.txt, add your class's .h and .cpp file name in add_executable field after main.cpp.
//    Then, after Save, you will see these 2 files.

#include <QCoreApplication>

#include "qobjectexample.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // Also inherits QObject, means it has connect().

    // Below, we first define a QObject, and then connect its signal to another QObject's slot.
    // Then we emit that signal.
    // Here, connect() resides in the working mechanism even after it is executed, waiting for the signal event.
    QObjectExample QobjExam;
    // We have 2 QObject here, and they are not at the same palce. So we need Qt::QueuedConnection.
    // By default, it is Qt::AutoConnection.
    QObject::connect(&QobjExam, &QObjectExample::close, &a, &QCoreApplication::quit, Qt::QueuedConnection);
    QobjExam.dosomething(); // print log, and emit close();

    int ret = a.exec();
    qInfo() << "Return value of main() is " << ret;
    return ret;
    // return a.exec();
}

// When 'QCoreApplication a' is created, it doesn't know 'QObjectExample QobjExam', but they can communicate later
// by connect(). Why? QT has something called MOC (Meta Object Compiler). It will scan your file, pick any QObject
// you define, process at backend to enable, some mechanism, to make them communicate.
// ---------------------------------------------------------------------------------------------------------------------------
// The meta-object system is based on three things:
// 1. The QObject class provides a base class for objects that can take advantage of the meta-object system.
// 2. The Q_OBJECT macro inside the private section of the class declaration is used to enable meta-object features, such as
//    dynamic properties, signals, and slots.
// 3. The Meta-Object Compiler (moc) supplies each QObject subclass with the necessary code to implement meta-object features.
// ---------------------------------------------------------------------------------------------------------------------------
