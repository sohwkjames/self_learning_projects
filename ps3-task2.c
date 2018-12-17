/*************************
 * Problem Set 3: Task 2 *
 *************************
 
Make sure you have answered ALL 
the questions in this task.   */

#include <stdio.h>
#include <stdbool.h>


// a.
bool is_leap_year(int year) {
    
    //if century, not leap unless multiple of 400
    if(year%100 == 0){
        if(year%400 == 0){
            return true;
        }
        else{
            return false;
        }
    }
    
    if(year%4 == 0){
        return true;
    }
    else {
        return false;
    }
    
}


// b. 
int days_in_month(int month, int year) {

    // feb should be 29 days in leap years, 28 days in non leap
    if(month == 2){
        if(is_leap_year(year) == true){
            return 29;
        }
        else{
            return 28;
        }
    }
    //hard code the number of days in each month
    else if (month == 4 || month == 6 || month == 9 || month == 11){
        return 30;
    }
    else{
        return 31;
    }
    }

// c. 
int days_from_epoch(int day, int month, int year) {
    // convert the input date into days, then find difference from epoch date.
    int sum_of_days = 0;
    // account for all day values first.
    sum_of_days += day -1;

    // add all days of current month into counter.
    sum_of_days += days_in_month(month, year);
        if(month == 1){
        month = 12;
        year = year - 1;
    }
        else{
            month = month -1;
        }

    // each iteration will reduce year by 1. 
    while (year > 0){
        //debug printing 
        if(year == 2000){
         //   printf("Year 2000, month: %d, days in month: %d \n", month, days_in_month(month,year));
        }
         // handle all months
            sum_of_days += days_in_month(month,year);
            if(month == 1){
                month = 12;
                year = year -1;
            }
            else{
                month = month - 1;
            }
        }
        // return number of days - epoch date. by using 
        return sum_of_days - 719193;


    }



// d.
int day_of_week(int day, int month, int year) {
// returns day of the week of input date. return 0 = sunday, 6 = saturday. 1/1/1970 is a thursday.
    int day_track = days_from_epoch(day, month, year) % 7 ; // will return a value from 0 to 6
    day_track = day_track + 4;
    return day_track;

        }    


// e. 
void display_month(int month, int year) {
    
    printf(" S M T W T F S\n");
    // get first day
    int day = day_of_week(1, month, year);
    
    int total_dates = days_in_month(month,year);
    //printf("day is %d and total number of days is %d \n", day, total_dates);
    
    // handle starting day.
    int date = 1;
    for (int i = 0; i < day; i = i +1){
        printf("  ");
    }

    printf(" %d", date);

    // for each day in total number of days in month;
    for(date = 2; date <= total_dates; date = date +1){
        day = day + 1;
        printf("%2d", date);
        // if today is saturday, break line
        if (day == 6){
            printf("\n");
            day = -1;
        }

    }
}


int main(void){
 //   printf("** is_leap_year(2012)	expected 1 ** \n %d \n", is_leap_year(2012));
 //   printf("** is_leap_year(2100)	expected 0 ** \n %d \n", is_leap_year(2100));
 //   printf("** is_leap_year(2017)	expected 0 ** \n %d \n", is_leap_year(2017));
 //   printf("** days_in_month(9, 2017)   expected 30 ** \n %d \n", days_in_month(9, 2017));
 //   printf("** days_in_month(2, 2000)	expected 29 ** \n %d \n", days_in_month(2, 2000));
 //   printf("** days_from_epoch(10, 1, 1970), expected 9 ** \n %d \n", days_from_epoch(10, 1, 1970));
 //   printf("** days_from_epoch(7, 9, 2017), expected 17416 ** \n %d \n", days_from_epoch(7, 9, 2017));
 //   printf("** days_from_epoch(9, 8, 1965), expected -1606	 ** \n %d \n", days_from_epoch(9, 8, 1965));
 //   printf("** days_from_epoch(10, 1, 1970), expected 9	 ** \n %d \n", days_from_epoch(10, 1, 1970));
 //   printf("** day_of_week(1, 1, 1970), expected 4	 ** \n %d \n", day_of_week(1, 1, 1970)	);
 //     printf("** day_of_week(9, 9, 2017);	, expected 6	** \n %d \n", day_of_week(9, 9, 2017));
 display_month(9, 2017);

    return 0;

}