#ifndef TESTPARENTCHILD_H
#define TESTPARENTCHILD_H

#include <QObject>
#include <QDebug>

class TestParentChild : public QObject
{
    Q_OBJECT

// Add below 2 options to disable copy ctor of qobject and its sub-class.
// See document <Qt_Documents/Q_DISABLE_COPY>
// Method 1
private:
    Q_DISABLE_COPY(TestParentChild)

// // Method 2
//private:
//TestParentChild(const TestParentChild &) = delete;
//TestParentChild &operator=(const TestParentChild &) = delete;


public:
    explicit TestParentChild(QObject *parent = nullptr);

    // Add a dtor here to illustrate the parent-child relation.
    ~TestParentChild();

signals:

};

#endif // TESTPARENTCHILD_H
