#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <randomnumbers.h>
#include <QTime>
#include <QThread>
#include <gpiohandler.h>
#include <scores.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QStringList listOfColors;
    scores sc;


private slots:
    void on_btnGenerateNumbers_clicked();

    void on_spinBoxHowManyNumbers_valueChanged(int arg1);

    void on_btnRedLed_clicked();

    void on_btnBlueLed_clicked();

    void on_btnYellow_clicked();

    void on_btnGreenLed_clicked();

private:
    Ui::Widget *ui;

    void SetLayoutOfUserInputButtons();
    void SetConditionalFormattingOfLabel(QLabel * aLabel, QLabel * bLabel);
    void PopulateLabelsWithRandomNumbers();
    void ClearLabelsWithRandomNumbers();

    QString ConvertRandomNumbersToColorName(int random_number);

    void SleepInQt(int number_of_seconds);

    QVector<int> collection_of_random_numbers;
    int number_of_shots;

};
#endif // WIDGET_H
