#include "scores.h"

scores::scores(QObject *parent) : QObject(parent)
{

}

void scores::add_to_current_collection_of_user_input(int button_pressed)
{
    collection_of_button_presses.append(button_pressed);
    qInfo()<<"User has entered the following numbers until now: "<<collection_of_button_presses;
}

void scores::clear_collections()
{
    collection_of_button_presses.clear();
    collection_of_generated_numbers.clear();
    current_score=0;
}

void scores::get_the_collection_of_generated_numbers(QVector<int> myCollection)
{
    collection_of_generated_numbers=myCollection;
    qInfo()<<"The list of generated color numbers is "<<collection_of_generated_numbers;
}

int scores::compute_score_for_user_input()
{
    current_score=0;

    for (int i=0;i<collection_of_generated_numbers.size();i++)
    {
        if (collection_of_button_presses[i]==collection_of_generated_numbers[i])
        {
            current_score++;
        }
    }

    qInfo()<<"The final user score is "<<current_score;
    return current_score;
}

