#ifndef RANDOMNUMBERS_H
#define RANDOMNUMBERS_H

#include <QObject>
#include <QDebug>
#include <QRandomGenerator>

class randomNumbers : public QObject
{
    Q_OBJECT
public:
    explicit randomNumbers(QObject *parent = nullptr);
    QVector<int> collection_of_random_shots;
    QVector<int> GenerateRandomNumbers(int countOfNumbers);

private:


signals:

};

#endif // RANDOMNUMBERS_H
