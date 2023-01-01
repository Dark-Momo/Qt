#ifndef QOBJECTEXAMPLE_H
#define QOBJECTEXAMPLE_H

#include <QObject> // This is where you know your class inherits QObject.

class QObjectExample : public QObject
{
    // The Q_OBJECT macro inside the private section of the class declaration is used to enable meta-object features,
    // such as dynamic properties, signals, and slots.
    Q_OBJECT
public:
    // This ctor, depending on what parent you give, make itself child of the parent.
    // When the parent is deleted, all its children will be deleted.
    explicit QObjectExample(QObject *parent = nullptr);

    // signals: fiels by default is here, empty.
signals:
    void close(); // doing nothing.

    // public slots: field is created by programmer.
    // public slots are public functions.
public slots:
    void dosomething(); // Right Click the name - Refactor - Add definition in xxx.cpp to define the function.
};

#endif // QOBJECTEXAMPLE_H
