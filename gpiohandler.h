#ifndef GPIOHANDLER_H
#define GPIOHANDLER_H

#include <QObject>
#include <QDebug>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> // this is header file is mention because it includes the stat() function

#define PATH_TO_GPIO_DIR "/sys/class/gpio/"

class gpiohandler : public QObject
{
    Q_OBJECT
public:
    explicit gpiohandler(QObject *parent = nullptr);

    static const int GPIO_NUMBER_FOR_LED_RED;
    static const int GPIO_NUMBER_FOR_LED_GREEN;
    static const int GPIO_NUMBER_FOR_LED_BLUE;
    static const int GPIO_NUMBER_FOR_LED_YELLOW;

    void turn_on_led(int gpio_number);
    void turn_off_led(int gpio_number);

    QVector<int> collection_of_gpio_numbers_in_sequence;
    QVector<int> convert_input_numbers_to_gpio_numbers(QVector<int> collection_of_numbers);
    void flash_leds_in_gpio_numbers_sequence(QVector<int> sequence_of_leds);


private:
    int verify_if_directory_gpionumber_exists(int gpio_number);
    int write_to_export_file(int gpio_number);
    int write_to_direction_file(int gpio_number, char * direction);
    int write_to_value_file(int gpio_number, char * value);

signals:

};

#endif // GPIOHANDLER_H
