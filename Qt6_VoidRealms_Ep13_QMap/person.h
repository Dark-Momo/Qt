#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class person : public QObject
{
    Q_OBJECT   
private:
    QString name;
    int age;
public:
    explicit person(QObject *parent = nullptr);

    ~person();

    QString getName() const;
    void setName(const QString & s);

    int getAge() const;
    void setAge(const int a);

signals:

};

#endif // PERSON_H
