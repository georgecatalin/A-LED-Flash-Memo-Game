#include "randomnumbers.h"


randomNumbers::randomNumbers(QObject *parent) : QObject(parent)
{

}

QVector<int> randomNumbers::GenerateRandomNumbers(int countOfNumbers)
{
    QVector<int> collection_of_random_numbers;

    int i=0;

    while (i<countOfNumbers)
    {
        int number=QRandomGenerator::global()->bounded(4)+1;
        collection_of_random_numbers.append(number);

        i=i+1;
    }

    return collection_of_random_numbers;
}
