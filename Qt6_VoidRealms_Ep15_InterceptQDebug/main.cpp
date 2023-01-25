#include <QCoreApplication>
#include <QDebug>
#include <iostream>

// --------------------------------------------------------------------------------------------------------
// Once below MessageHandler is installed, it can be anywhere in the application.

// When it is installed, all outputs using qDebug(), qInfo(), qWarning(), qCritical()
// and qFatal() will be passed to it, re-format the output to the format defined below.

// Whenn it is uninstalled, all outputs using qDebug(), qInfo(), qWarning(), qCritical()
// and qFatal() will just output as what it is plainly.

// std::cout is not influencecd.
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit(); // QString -> QByteArray
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    }
}
// --------------------------------------------------------------------------------------------------------

void TestLog()
{
    qDebug() << "TestLog() - This is qDebug() line";
    qInfo() << "TestLog() - This is qInfo() line";
    qWarning() << "TestLog() - This is qInfo() line";
    qCritical() << "TestLog() - This is qCritical() line";

    std::cout << "TestLog() - This is std::cout line" << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream keyIn(stdin);
    std::cout << "[std::cout] ---------- Starting the Log Test ----------\n";

    bool running = true;
    while(running)
    {
        std::cout << "[std::cout] Input a command (start, stop, test, or exit)...\n";
        QString cmd = keyIn.readLine();
        qInfo() << "[qInfo] You entered :" << cmd;

        if (cmd == "start")
        {
            qInfo() << "[qInfo] Install qInstallMessageHandler now!";
            qInstallMessageHandler(myMessageOutput);
        }
        else if (cmd == "stop")
        {
            qInfo() << "[qInfo] Uninstall qInstallMessageHandler now!";
            qInstallMessageHandler(0);
        }
        else if (cmd == "test")
        {
            qInfo() << "[qInfo] Run TestLog()!";
            TestLog();
        }
        else if (cmd == "exit")
        {
            qInfo() << "[qInfo] Set running to false now!";
            running = false;
        }
        else
        {
            qInfo() << "[qInfo] Wrong command. Please re-enter...";
        }
    }

    qInfo() << "[qInfo] Exit the main app now...";
    return a.exec();
}
