#include <iostream>

#include <ctime>

 

std::string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",

                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

std::string days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri",

                      "Sat"};

 

class Date{

    // Private Members

    private:

        std::string month;

        std::string day;

        int date;

        int year;

    // Public Members

    public:

        // Default Constructor

        Date() { 

                const int BASE_YEAR = 1900;

                time_t timer;

                tm * time;

                std::time(&timer);

                time = localtime(&timer);

                date = time->tm_mday;

                month = months[time->tm_mon];

                day = days[time->tm_wday];

                year = time->tm_year + BASE_YEAR;

        }

        void printDate(void) { 

            std::cout << "Current date " 

                      << this->month << " " << this->day << " "

                      << this->date  << " " << this->year;

        }

        // Destructor

        ~Date() {}

};

 

int main()

{

    Date d;

 

    d.printDate();

}