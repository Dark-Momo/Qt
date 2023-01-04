#include <QCoreApplication>

#include "testclass.h"

typedef QList<testClass *> testList;

// Create a list of pointers
testList getTestList()
{
    testList list;
    for (int i = 0; i < 5; i++)
    {
        list.append(new testClass());
        list.last()->setObjectName("TestClass" + QString::number(i));
    }
    return list; // QList is not a QObject, so the return can copy it here.
}

// Display a list of pointers
void displayTestList(testList list)
{
    qInfo() << "Will display the pointers in our list...";
    foreach(testClass * item, list)
    {
        qInfo() << item; // Display a pointers withour validating it!
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testList list = getTestList();
    displayTestList(list);

    // Upon here, we have a list of QObjects testClass, without setting their parents.
    // THEY CAN'T USE THE PARENT-CHILD RELATIONSHIP THAT CAN HANDLE AUTO DELETION FROM, SOME PARENT.
    // So, if you run the program, you won't see dtor be called here.
    // If we don't delete them explicitly, we have memory leak until we close the program.

    qInfo() << "Will delete our list of QObjects testClass...";
    // Below 2 lines are the same, and will trigger the Dtor of testClass to be called!
    // qDeleteAll(list);
    qDeleteAll(list.begin(), list.end());

    list.clear(); // clear() if you use qDeleteAll to delete a list.

    displayTestList(list);
    // 1. If above clear() is missing : this displayTestList(list) will trigger program window show
    // "Press <RETURN> to close this window..." at bottom, which actually means crash.
    // It is because we are showing the list with pointers, but pointers now are NULL.
    // 2. If above clear() is there : the program window is still alive after this line.
    // It is expected, since "return a.exec();" runs normally without any quit().

    return a.exec();
}

/*
* template <typename ForwardIterator> void qDeleteAll(ForwardIterator begin, ForwardIterator end);
*
* Deletes all the items in the range [begin, end) using the C++ delete operator. The item type must
* be a pointer type (for example, QWidget *).
*
* Notice that qDeleteAll() doesn't remove the items from the container; it merely calls delete on them.
* In the example above, we call clear() on the container to remove the items.
*/
