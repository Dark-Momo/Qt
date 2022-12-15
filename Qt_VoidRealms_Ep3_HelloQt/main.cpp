// In order to have a terminal jumping out to run the code, we need to
// go to "Tools - Option - Build & Run - Run", select "Run In Termina".
// It is not selected by default.

#include <QCoreApplication>
#include <iostream>
#include <string>

#include <QTextStream>
#include <QDebug>

void do_cpp(void)
{
    std::string name;
    std::cout << "Please input your name : ";
    std::getline(std::cin, name);
    std::cout << "Your name is - " << name << std::endl;
}

void do_qt()
{
    QTextStream qin(stdin);
    QTextStream qout(stdout);

    qout << "Please input your name : ";
    qout.flush();

    QString name = qin.readLine(); // You can assign max length by its argument.
                                   // Default takes a default max length value.

    qout << "Your name is : " << name << "\n";
    // qout << "Your name is : " << name << Qt::endl;
    // qout.flush();

    // We need those flush() and Qt::endl at the end of each line that you want to output.

    // Otherwise, you will get all your output text together, and at the same time.
    // Because QTextStream doesn't flush output buffer itself, as what std::cout will do.
    // The execution sequence is:
    // (1) Put "Please input your name : " into output buffer, but doesn't output;
    // (2) Stuck at qin.readLine(), so nothing output on terminal, and wait here;
    // (3) After you input anything ended with Enter, it will show:
    // -----------------------------------------------------------------------------------
    // Jian
    // Please input your name : Your name is : Jian
    // -----------------------------------------------------------------------------------

    // When the function do_qt() is executed after }, all the stream will be destructed, and their
    // dtor will call flush() to flush output buffer. That is when you see the above line.
    // "\n" doesn't flush while Qt::endl can.
}

void do_mix()
{
    QTextStream qin(stdin);
    qInfo() << "Please input your name : ";
    QString name = qin.readLine();
    qInfo() << "Your name is " << name;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // User code begins here

    // do_cpp();

    do_qt();

    // do_mix();

    // End of user code

    return a.exec();
}
