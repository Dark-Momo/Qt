#include <QCoreApplication>
#include <QScopedPointer>

#include "testclass.h"

// 1. QScopedPointer guarantees that the object pointed to will get deleted when the current scope disappears.
// 2. QSharedPointer will delete the pointer it is holding when it goes out of scope, provided no other QSharedPointer
//    objects are referencing it.

// ---------------------------------------------------------------------------------------------------------------------
void testScope()
{
    // We create a QScopedPointer by new here.
    QScopedPointer<TestClass> ptr(new TestClass());
    ptr->message("Hello, Test QScopePointer...");
    // The created QScopedPointer should be deleted upon exiting the function scope here.
}
// ---------------------------------------------------------------------------------------------------------------------

void work(QSharedPointer<TestClass> ptr)
{
    ptr->message("Working...");
}

void finish(QSharedPointer<TestClass> ptr)
{
    ptr->message("Finishing...");
}

void step(QSharedPointer<TestClass> ptr)
{
    ptr->message("Stepping...");
    for (int  i = 0; i < 3; i++)
    {
        work(ptr);
    }
    finish(ptr);
    qInfo() << "Getting out of step()";
}

// main() generate a 'normal' pointer, and pass it to its subfunction testShared().
// testShared() accepts this normal pointer, encasulate it into a QSharedPointer, and
// all its subfunction take this QSharedPointer as parameter.
void testShared(TestClass * testPtr)
{
    QSharedPointer<TestClass> ptr(testPtr); // ptr holds testPtr.
    // This ptr above is the ONLY QSharedPointer in this program, and all other functions
    // take it, starting from step()'s parameter. It is also this ptr who count its reference,
    // and finally delete the 'testPtr'.

    ptr->message("Starting...");
    step(ptr);
    qInfo() << "Getting out of testShared()";

    // ptr is deleted here, upon exit here.
}
// ---------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo() << "----- 1. test QScopePointer  -----";
    testScope();

    qInfo() << Qt::endl;
    qInfo() << "----- 2. test QSharedPointer -----";
    testShared(new TestClass());
    // Dtor of TestClass() will be called after Getting out of testShared()",
    // but before "Back to main()".

    qInfo() << "Back to main()";

    return a.exec();
}
