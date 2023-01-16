#include <QCoreApplication>

// No header file needed for QByteArray and qInfo().

// ******************************************************************
// QString.size() returns number of characters;
// QByteArray.size() returns number of bytes;

// QByteArray and QString is not QObject, so they can be copied.
// ******************************************************************

/* QByteArray ensures that the byte at position size() is always '\0',
 * so that you can use the return value of data() and constData() as
 * arguments to functions that expect '\0'-terminated strings. If
 * the QByteArray object was created from a raw data that didn't include
 * the trailing '\0'-termination byte, then QByteArray doesn't add it
 * automatically unless a deep copy is created.
 */

void stats(const QByteArray & qBArr)
{
    qInfo() << qBArr << ":" << "size is" << qBArr.size() << ", Capacity is" << qBArr.capacity();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Initialize simple QByteArray
    QByteArray sample1;
    qInfo() << sample1; // Output is "", from qInfo().

    QByteArray sample2("Hello World");
    qInfo() << sample2 << "with length" << sample2.length();

    // ---------------------------------------------------------------------------------------------------------------
    QByteArray sample3(10, '\t');
    qInfo() << sample3 << "with length" << sample3.length(); // Output is "\t\t\t\t\t\t\t\t\t\t"

    QByteArray sample4(10, '\r');
    qInfo() << sample4; // Output is "\r\r\r\r\r\r\r\r\r\r"

    QByteArray sample5(10, '\n');
    qInfo() << sample5; // Output is "\n\n\n\n\n\n\n\n\n\n"

    QByteArray sample6(10, '\0');
    qInfo() << sample6 << "with length" << sample6.length(); // Output is "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
    // So, Qt's QString and QByteArray doesn't have escape character...?
    // ---------------------------------------------------------------------------------------------------------------

    QString qStr1("Jian Lao");
    // QString's size() and length() is the same, returing number of characters.
    // Return type is qsizetype, which is signed, and platform independent.
    qsizetype len = qStr1.size(); // len is 8.
    qInfo() << "QString" << qStr1 << "has length" << len;

    // Below has error since you can't initialize a QByteArray directly from QString.
    // QByteArray sample7(qStr1);

    // ---------------------------------------------------------------------------------------------------------------
    // ---------------------------------------------------------------------
    // INITIALIZE A QBYTEARRAY USING A QSTRING
    QByteArray sample7(qStr1.toLocal8Bit());
    // ---------------------------------------------------------------------

    // QString.size() returns number of characters;
    // QByteArray.size() returns number of bytes;
    qInfo() << "QByteArray" << sample7 << "has length" << sample7.size();
    // ---------------------------------------------------------------------------------------------------------------

    // Interesting Things Here!
    // 1. If function declaration is void stats(QByteArray &qBArr), and usage is below:
    // stats(QByteArray("Jian Lao"));
    // This will have:
    // error: cannot bind non-const lvalue reference of type ‘QByteArray&’ to an rvalue of type ‘QByteArray’
    // For C++, if you take reference of a temporary object, that reference is Const.
    // So function prototype should be 'v'oid stats(const QByteArray &qBArr)';

    // 2. Function prototype can't use pointer, otherwise calling will be stats(&QByteArray("Jian Lao"))
    // For C++, you are not allowed to use pointer of a temporary object.

    stats(QByteArray("Jian Lao")); // Generate a temporary object in the function, and it will be destructd
                                   // when the function finishes.


    qInfo() << "sample7 is" << sample7; // "Jian Lao"
    sample7.reserve(32); // Not 32 bytes, but, at least 32 bytes.
    stats(sample7); // Output is : "Jian Lao" : size is 8 , Capacity is 32

    sample7.resize(24);
    stats(sample7);
    // Output is :
    // "Jian Lao\x00\x00\x00\x00 \x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00" : size is 24 , Capacity is 32

    sample7.truncate(6);
    stats(sample7); // Output is : "Jian L" : size is 6 , Capacity is 32

    sample7.clear();
    stats(sample7); // Output is : "" : size is 0 , Capacity is 0

    // ---------------------------------------------------------------------------------------------------------------

    sample7.resize(8);
    stats(sample7); // "\x00\x00\x00\x00\x00\x00\x00\x00" : size is 8 , Capacity is 16
    sample7.fill('\x02');
    stats(sample7); // "\x02\x02\x02\x02\x02\x02\x02\x02" : size is 8 , Capacity is 16

    return a.exec();
}
