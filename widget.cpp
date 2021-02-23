#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    SetLayoutOfUserInputButtons();

    listOfColors<<"red"<<"green"<<"blue"<<"yellow";

    Widget::number_of_shots=1;

    SetConditionalFormattingOfLabel(ui->lblInSeries_1,ui->lblSeriesHeader);
    SetConditionalFormattingOfLabel(ui->lblInSeries_2,ui->lblSeriesHeader);
    SetConditionalFormattingOfLabel(ui->lblInSeries_3, ui->lblSeriesHeader);
    SetConditionalFormattingOfLabel(ui->lblInSeries_4, ui->lblSeriesHeader);

    scores sc;


}

Widget::~Widget()
{
    delete ui;
}

void Widget::SetLayoutOfUserInputButtons()
{
    /* *** Lacon Logo Color Scheme ***
     * HEX: #CD202C Red
     * HEX: #747678 Gray
     * *** */

    ui->btnBlueLed->setStyleSheet("QPushButton {background-color:blue;color:white;}");
    ui->btnGreenLed->setStyleSheet("QPushButton {background-color:green;color:white;}");
    ui->btnRedLed->setStyleSheet("QPushButton {background-color:red;color:white;}");
    ui->btnYellow->setStyleSheet("QPushButton {background-color:yellow;color:black;}");

    ui->btnGenerateNumbers->setStyleSheet("QPushButton {background-color:#747678;color:white}");
}

void Widget::SetConditionalFormattingOfLabel(QLabel * aLabel, QLabel * bLabel)
{
    QString textInLabel;
    textInLabel=aLabel->text().toLower();


    /* ********************************************* Note to self:
     * In C++ language switch statement can only be used with integer or enum types.
     * *********************************************  */



    /*
     * red is 0
     * green is 1
     * blue is 2
     * yellow is 3
     * */

    switch (listOfColors.indexOf(textInLabel))
    {
    case 0:
        aLabel->setStyleSheet("QLabel {color:red;}");
        bLabel->setStyleSheet("QLabel {background-color:red;}");
        break;
    case 1:
        aLabel->setStyleSheet("QLabel {color:green}");
        bLabel->setStyleSheet("QLabel {background-color:green;}");
        break;
    case 2:
        aLabel->setStyleSheet("QLabel {color:blue}");
        bLabel->setStyleSheet("QLabel {background-color:blue;}");
        break;
    case 3:
        aLabel->setStyleSheet("QLabel {color:yellow}");
        bLabel->setStyleSheet("QLabel {background-color:yellow;}");
        break;
    default:
        aLabel->setStyleSheet("QLabel {color:black}");
         bLabel->setStyleSheet("QLabel {background-color:black;}");
        break;

    }
}


void Widget::PopulateLabelsWithRandomNumbers()
{

    for (int i=0;i<Widget::number_of_shots ;i++)
    {
        ui->lblInSeries_1->setText(ConvertRandomNumbersToColorName(collection_of_random_numbers[i]));
        SetConditionalFormattingOfLabel(ui->lblInSeries_1, ui->lblSeriesHeader);
        SleepInQt(2);

        ui->lblInSeries_1->setText("");
        ui->lblSeriesHeader->setStyleSheet("QLabel {background-color:white;}");
        SleepInQt(1);
    }

}

void Widget::ClearLabelsWithRandomNumbers()
{
    ui->lblInSeries_1->setText("");
}

QString Widget::ConvertRandomNumbersToColorName(int random_number)
{
    QString convert_number_to_color_name;

    switch (random_number)
    {
      case 1:
        convert_number_to_color_name="red";
        break;
    case 2:
        convert_number_to_color_name="green";
        break;
    case 3:
        convert_number_to_color_name="blue";
        break;
    case 4:
        convert_number_to_color_name="yellow";
        break;
    default:
        convert_number_to_color_name="black";
        break;
    }

    return convert_number_to_color_name;
}

void Widget::SleepInQt(int number_of_seconds)
{
    QTime sleepTime=QTime::currentTime().addSecs(number_of_seconds);
    while (QTime::currentTime()<sleepTime)
    {
        QApplication::processEvents();
        QThread::sleep(2);
    }
}


void Widget::on_btnGenerateNumbers_clicked()
{
    randomNumbers rn;
    collection_of_random_numbers=rn.GenerateRandomNumbers(Widget::number_of_shots);
    qDebug()<<"The number_of_shots Widget Class property is"<<Widget::number_of_shots;
    qDebug()<<collection_of_random_numbers;


    ClearLabelsWithRandomNumbers();
    PopulateLabelsWithRandomNumbers();

    gpiohandler gh;
    QVector<int> my_collection=gh.convert_input_numbers_to_gpio_numbers(collection_of_random_numbers);
    qInfo()<<"The sequence of gpio numbers is:"<<my_collection;
    gh.flash_leds_in_gpio_numbers_sequence(my_collection);

    sc.clear_collections();
    sc.get_the_collection_of_generated_numbers(collection_of_random_numbers);


}

void Widget::on_spinBoxHowManyNumbers_valueChanged(int number_of_shots)
{
    qDebug()<<"User has selected to generate randomly "<< number_of_shots<<" numbers";
    Widget::number_of_shots=number_of_shots;
    qDebug()<<"The number_of_shots Widget class property is "<<Widget::number_of_shots;
}

void Widget::on_btnRedLed_clicked()
{
    if (sc.collection_of_button_presses.size()<=number_of_shots)
    {
           sc.add_to_current_collection_of_user_input(1);
    }
    else
    {
        qInfo()<<"User pressed the coloured buttons more times than the number of the random generated numbers";
        sc.compute_score_for_user_input();
    }
}

void Widget::on_btnBlueLed_clicked()
{
     if (sc.collection_of_button_presses.size()<number_of_shots)
     {
         qInfo()<<sc.collection_of_button_presses.size();
         sc.add_to_current_collection_of_user_input(3);
     }
     else
     {
         qInfo()<<"User pressed the coloured buttons more times than the number of the random generated numbers";
         sc.compute_score_for_user_input();
         ui->lblYouRememberValue->setText(QString::number(sc.current_score));
     }
}

void Widget::on_btnYellow_clicked()
{
    if (sc.collection_of_button_presses.size()<number_of_shots)
    {
        qInfo()<<sc.collection_of_button_presses.size();
        sc.add_to_current_collection_of_user_input(4);
    }
    else
    {
        qInfo()<<"User pressed the coloured buttons more times than the number of the random generated numbers";
        sc.compute_score_for_user_input();
        ui->lblYouRememberValue->setText(QString::number(sc.current_score));
    }
}

void Widget::on_btnGreenLed_clicked()
{
    if (sc.collection_of_button_presses.size()<number_of_shots)
    {
        qInfo()<<sc.collection_of_button_presses.size();
        sc.add_to_current_collection_of_user_input(2);
    }
    else
    {
        qInfo()<<"User pressed the coloured buttons more times than the number of the random generated numbers";
        sc.compute_score_for_user_input();
        ui->lblYouRememberValue->setText(QString::number(sc.current_score));
    }
}
