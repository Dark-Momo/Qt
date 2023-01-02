#ifndef QOBJECTEXAMPLE_H
#define QOBJECTEXAMPLE_H

#include <QObject>

class QobjectExample : public QObject
{
    Q_OBJECT
public:
    explicit QobjectExample(QObject *parent = nullptr);

signals:

};

#endif // QOBJECTEXAMPLE_H
