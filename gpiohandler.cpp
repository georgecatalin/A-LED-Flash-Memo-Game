#include "gpiohandler.h"

const int gpiohandler::GPIO_NUMBER_FOR_LED_RED = 50;
const int gpiohandler::GPIO_NUMBER_FOR_LED_GREEN =49;
const int gpiohandler::GPIO_NUMBER_FOR_LED_BLUE=7;
const int gpiohandler::GPIO_NUMBER_FOR_LED_YELLOW=31;

/* ============================================================================================
            * List of error codes in C language given by the <errno.h> header
            * ***************************************************************
            * errno value       Error
1            * Operation not permitted *
2            * No such file or directory *
3            * No such process *
4            * Interrupted system call *
5            * I/O error *
6            * No such device or address *
7            * Argument list too long *
8            * Exec format error *
9            * Bad file number *
10           * No child processes *
11           * Try again *
12           * Out of memory *
13           * Permission denied *
            * *****************************************************************
 ==============================================================================================
 */


gpiohandler::gpiohandler(QObject *parent) : QObject(parent)
{
  qInfo()<<"In this game I am considering that LED RED is connected at GPIO"<<gpiohandler::GPIO_NUMBER_FOR_LED_RED<<" on the BeagleBone Black";
  qInfo()<<"In this game I am considering that LED GREEN is connected at GPIO"<<gpiohandler::GPIO_NUMBER_FOR_LED_GREEN<<" on the BeagleBone Black";
  qInfo()<<"In this game I am considering that LED BLUE is connected at GPIO"<<gpiohandler::GPIO_NUMBER_FOR_LED_BLUE<<" on the BeagleBone Black";
  qInfo()<<"In this game I am considering that LED YELLOW is connected at GPIO"<<gpiohandler::GPIO_NUMBER_FOR_LED_YELLOW<<" on the BeagleBone Black";


}

void gpiohandler::turn_on_led(int gpio_number)
{
    int existsDirectory=verify_if_directory_gpionumber_exists(gpio_number);


    if(existsDirectory)
                {
                    printf("I do not need to write in the file 'export'.\n");
                }
                else
                {
                    printf("I need to write '%d' in the file 'export'.\n",gpio_number);
                    write_to_export_file(gpio_number);
                }

    /* *** wait for half a second to make sure the the 'export' file was properly closed, and the directory gpio? added to file system *** */

    sleep(1);
    write_to_direction_file(gpio_number,(char *) "out");
    write_to_value_file(gpio_number,(char *) "1");

}

void gpiohandler::turn_off_led(int gpio_number)
{
    write_to_value_file(gpio_number,(char *) "0");
}

QVector<int> gpiohandler::convert_input_numbers_to_gpio_numbers(QVector<int> collection_of_numbers)
{
 for(int i=0;i<collection_of_numbers.size(); i++)
 {
     switch (collection_of_numbers[i])
     {
     case 1:
         collection_of_gpio_numbers_in_sequence.append(gpiohandler::GPIO_NUMBER_FOR_LED_RED);
         break;
     case 2:
         collection_of_gpio_numbers_in_sequence.append(gpiohandler::GPIO_NUMBER_FOR_LED_GREEN);
         break;
     case 3:
         collection_of_gpio_numbers_in_sequence.append(gpiohandler::GPIO_NUMBER_FOR_LED_BLUE);
         break;
     case 4:
         collection_of_gpio_numbers_in_sequence.append(gpiohandler::GPIO_NUMBER_FOR_LED_YELLOW);
         break;
     default:
         break;
     }
 }

 return collection_of_gpio_numbers_in_sequence;
}

void gpiohandler::flash_leds_in_gpio_numbers_sequence(QVector<int> sequence_of_gpio_numbers)
{
    for (int i=0;i<sequence_of_gpio_numbers.size() ;i++ )
    {
     qInfo()<<"This is "<<sequence_of_gpio_numbers[i];
     turn_on_led(sequence_of_gpio_numbers[i]);
     sleep(1);
     turn_off_led(sequence_of_gpio_numbers[i]);
    }
}


int gpiohandler::verify_if_directory_gpionumber_exists(int gpio_number)
{

    /* *** Construct the name of the directory *** */
    char buffer[100];

    snprintf(buffer,sizeof(buffer),PATH_TO_GPIO_DIR "gpio%d",gpio_number);

    struct stat file_properties;
    /* *** with stat() from <sys.stat.h> one can get file properties like file permission, creation and modification date, size *** */

    stat(buffer,&file_properties);

    if(S_ISDIR(file_properties.st_mode))
    {
        printf("The directory %s exists.\n", buffer);
        return (1);
    }
    else
    {
        printf("The directory %s does not exist.\n",buffer);
        printf("I shall create this directory for you and make the necessary adjustments to handle the gpio%d.\n",gpio_number);
        return (0);
    }
}

int gpiohandler::write_to_export_file(int gpio_number)
{
    int fd; /* *** this is the file descriptor *** */
        int return_from_write;
        char path[]=PATH_TO_GPIO_DIR "export";
        char buffer_convert_int_to_string[3];

        snprintf(buffer_convert_int_to_string ,sizeof(buffer_convert_int_to_string),"%d",gpio_number);

        //printf("...................................%s\n",buffer_convert_int_to_string);

        fd=open(path,O_WRONLY);

        if(fd==-1)
            {
                printf("There was an error when opening the file 'export' in %s. The error number is %d.\n",path,errno);
                return (-1);
            }

        return_from_write=write(fd,buffer_convert_int_to_string,strlen(buffer_convert_int_to_string));


        if(return_from_write<0)
        {
            printf("There was an error when writing to the file 'export' in gpio. The error number is %d.\n",errno);
            return (-1);
        }

        printf("I have written in the file 'export' of the gpio.\n\n");
        return (0);
}

int gpiohandler::write_to_direction_file(int gpio_number, char *direction)
{
    int fd; //file descriptor
        int return_from_write; //this integer will be returned as result from write() function. if -1 it means unsuccessful and error
        char buffer[100]; //this will be used in the snprintf() function

        snprintf(buffer,sizeof(buffer),PATH_TO_GPIO_DIR "gpio%d/direction",gpio_number);

        /* *** open file 'direction' *** */
        fd=open(buffer,O_WRONLY);

        if(fd==-1)
        {
            printf("There was an error when opening the file 'direction' in gpio%d. The error number is %d.\n",gpio_number,errno);
            return (-1);
        }

        return_from_write=write(fd,direction,strlen(direction));

        if(return_from_write<0)
        {
            printf("There was an error when writing to the file 'direction' in gpio%d. The error number is %d.\n",gpio_number,errno);
            return (-1);
        }

        printf("I have written in the file 'direction' of the gpio%d.\n",gpio_number);
        return (0);
}

int gpiohandler::write_to_value_file(int gpio_number, char *value)
{

    int fd; //file descriptor
    int return_from_write; //this integer will be returned as result from write() function. if -1 it means unsuccessful and error
    char buffer[100]; //this will be used in the snprintf() function

    snprintf(buffer,sizeof(buffer),PATH_TO_GPIO_DIR "gpio%d/value",gpio_number);

    /* *** open file 'direction' *** */
    fd=open(buffer,O_WRONLY);

    if(fd==-1)
    {
        printf("There was an error when opening the file 'direction' in gpio%d. The error number is %d.\n",gpio_number,errno);
        return (-1);
    }

    return_from_write=write(fd,value,strlen(value));

        if(return_from_write<0)
        {
            printf("There was an error when writing to the file 'direction' in gpio%d. The error number is %d.\n",gpio_number,errno);
            return (-1);
        }

        printf("I have written %s in the file 'value' of the gpio%d.\n",value, gpio_number);
        return (0);
}

