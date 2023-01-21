#include <QCoreApplication>
#include <QTimer>

#include "testparentchild.h"

// -----------------------------------------------------------------------------------------------------------------------------
// FOR QOBJECT, IF YOU INITIALIZE ONR QOBJECT FROM ANOTHER, THAT QOBJECT WILL BE YOUR PARENT.
// QObject class itself, has ONLY one Ctor : QObject::QObject(QObject *parent = nullptr);
// ITSELF DOESN'T DENOTE THIS PARENT-CHILD RELATION, BUT I GUESS QT WILL DO SOME BACKGROUND WORK TO
// RECORD THIS PARENT-CHILD RELATION FOR MEMORY MANAGEMENT.
// -----------------------------------------------------------------------------------------------------------------------------

// (1). Set Parent-Child relation in construction.
// We define a function here that take QObject * as input, AND ITS PARENT, and return a pointer to TestParentChild object.
TestParentChild * getTestParentChildWhileCtor(QObject * parent)
{
    // Here, we created a memory leak by only using new, without delete, for normal C++.
    // But, we give this object, from new, a parent, who will delete this object when it expires.
    // So we are safe here.
    // This is the fantastic thing about QT Parent-Child relation.

    return new TestParentChild(parent);
}

// (2). Need to set Parent-Child relation after construction.
TestParentChild * getTestParentChildOnly()
{
    return new TestParentChild();
}
// TestParentChild(parent) and TestParentChild() will use the same Ctor since this Ctor assigns all parameters a default value.
// -----------------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    // 1. CREATE THE PARENT
    QCoreApplication a(argc, argv);

    QTimer timer;
    // Below line will terminate a, and then trigger parent-child
    // relation to delete momo and kuku.
    timer.singleShot(3000, &a, &QCoreApplication::quit);

    // 2. Create a Child. Set Parent-Child Relationship.
    qInfo() << "Will create an object, momo, WITH Parent a, by using new...";
    TestParentChild * momo = getTestParentChildWhileCtor(&a);
    qInfo() << "Will set momo's name to Momo...";
    momo->setObjectName("Momo");

    qInfo() << Qt::endl;

    // 3. Create another Child. Set Parent-Child relation after construction.
    qInfo() << "Will create an object, kuku, WITH No Parent, by using new...";
    TestParentChild * kuku = getTestParentChildOnly();
    qInfo() << "Will set kuku's name to Kukumalu...";
    kuku->setObjectName("Kukumalu");

    qInfo() << Qt::endl;

    // 4. Set kuku's parent. Both fine below.
    kuku->setParent(momo);
    // kuku->setParent(&a);

    // QCoreApplication::exec() enters the main event loop and waits until exit() is called.
    // Returns the value that was passed to exit() (which is 0 if exit() is called via quit()).
    // -------------------------------------------------------------------------------------------------
    // return a.exec(); // Here really starts the running of your program, which is a QCoreApplication.
    // -------------------------------------------------------------------------------------------------
    int ret = a.exec();
    qInfo() << "Return value is " << ret;
    return ret;     // a will delete its child, TestParentChild object, here...
}
