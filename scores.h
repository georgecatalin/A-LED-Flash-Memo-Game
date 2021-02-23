#ifndef SCORES_H
#define SCORES_H

#include <QObject>
#include <QDebug>

class scores : public QObject
{
    Q_OBJECT
public:
    explicit scores(QObject *parent = nullptr);
    int highest_score;
    int smallest_score;
    int current_score;

    QVector<int> collection_of_button_presses;
    QVector<int> collection_of_generated_numbers;

public slots:
    void add_to_current_collection_of_user_input(int button_pressed);
    void clear_collections();
    void get_the_collection_of_generated_numbers(QVector<int> myCollection);
    int compute_score_for_user_input();


signals:

};

#endif // SCORES_H
