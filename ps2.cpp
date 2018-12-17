#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

double taxi_fare(int weekday, int start_time, int duration, int distance) {
    //int weekday     denoting the day of the week, 1–7 being Monday and 7 to Sunday.
    //int start_time     The starting time of the trip, in number of minutes since midnight of the stated day.
    //int duration     The speed of the taxi, in number of seconds it takes to cover 50 m.
    //int distance     The distance of the trip, in metres

    // 1. find end time. 
    
    float speed = 60.0 / duration * 50; // find speed in terms of meters per minute
    int time_elapsed = distance/speed; // time elapsed in terms of minutes
    int ending_time = start_time + time_elapsed;
    int end_day = weekday;
    printf("speed %f meters/minute, time elapsed %i minutes, starting time is %i and ending time is %i \n", speed, time_elapsed, start_time,ending_time);
    if(ending_time > 60 * 24){
        end_day = end_day +1;

    }
    // 2. simulate passage of time. each iteration is 1 minute
    // each iteration, our distance_travelled increases by meters per minute. (which is our 'speed' variable)
    int distance_travelled = 0;
    
    double fare = 3.4;
    int every_400m_checker = 0;
    int every_350m_checker = 0;
    int first_400m_checker = 1; // use as boolean, 1 if its the first time user enters the every 400m charge zone.
    int first_350m_checker = 1; // use as boolean, same as above

    int surcharge_start_1 = 60 * 16; // daily surcharge starts at 6pm
    int surcharge_end_1 = (60 * 23) + 59; // daily surcharge ends at 11.59pm
    int surcharge_start_2 = 60*6; // weekday surcharge
    int surcharge_end_2 = (60 * 8) + 59; // weekday surcharge
    int surcharge_start_3 = 0; // surcharge for midnight
    int surcharge_end_3 = (60 * 5) + 59; //surcharge for midnight

    float surcharge_multiplyer = 1.0;
    float added_to_fare = 0;

    for (int i = start_time +1; i <= ending_time; i +=1){ // i indicating time, which minute in the day we are at
        distance_travelled = distance_travelled + speed;
    // first surcharge
        if(i > (24 * 60)){ // to handle cases where time spill over midnight
            i = i % (24 * 60);
        }
        if(i >= surcharge_start_1 && i <= surcharge_end_1){ // check if time is between surcharge 1
            surcharge_multiplyer = 1.25;
        }
        else if (i >= surcharge_start_2 && i <= surcharge_end_2 && weekday >=1 && weekday <= 5 ){
            surcharge_multiplyer = 1.25;
        }
        else if (i >= surcharge_start_3 && i <= surcharge_end_3) {

            surcharge_multiplyer = 1.5;
        }
        else {}

        printf("MINUTE %i:, DISTANCE: %i, every_400m_checker: %i, CURRENT FARE %f, SURCHARGE MULTIPLYER %f \n", i, distance_travelled, every_400m_checker, fare), surcharge_multiplyer;

         // weekday surcharge
    // 3. basic fare up to 10km
        if (distance_travelled > 1000 && distance_travelled <= 10000 && first_400m_checker == 1){ // if user enters this distance for first time
            every_400m_checker = distance_travelled - 1000;
            first_400m_checker = 0;
            fare += (every_400m_checker / 400) * 0.22 * surcharge_multiplyer; // when user enters this distance for the first time, incur fares.
            added_to_fare = (every_400m_checker / 400) * 0.22 * surcharge_multiplyer;
            printf("AMOUNT ADDED TO FARE. ", added_to_fare);
        }
        else if (distance_travelled > 1000 && distance_travelled <= 10000 && first_400m_checker == 0){
             // if user entered this range of distance before
             every_400m_checker += speed;
        }
            if(every_400m_checker >= 400){
                added_to_fare = (every_400m_checker/400) *  0.22 * surcharge_multiplyer;
                fare +=  (every_400m_checker/400) *  0.22 * surcharge_multiplyer;
                printf("AMOUNT ADDED TO FARE %f", added_to_fare);
                every_400m_checker = every_400m_checker % 400;
                printf(" After performing modulus,  every_400m_checker is  %i \n", every_400m_checker);
            }
        if (distance_travelled > 10000 && first_350m_checker == 1){ // when user enters the range after 10km
            every_350m_checker = distance_travelled - 10000;
            first_350m_checker = 0;

        
            fare += (every_350m_checker / 350) * 0.22 * surcharge_multiplyer;
            added_to_fare = (every_350m_checker / 350) * 0.22 * surcharge_multiplyer;
            printf("AMOUNT ADDED TO FARE %f", added_to_fare);

        }


        else if (distance_travelled > 10000 && first_350m_checker == 0){ // if user has entered the >10km range before
            every_350m_checker += speed;
        }
            if(every_350m_checker >= 350){
                fare+= (every_350m_checker / 350) * 0.22 * surcharge_multiplyer;
                added_to_fare = (every_350m_checker / 350) * 0.22 * surcharge_multiplyer;
                printf("AMOUNT ADDED TO FARE %f", added_to_fare);
                every_350m_checker = every_350m_checker % 350;
            }

        
    }
        printf("fare is %f", fare);
        return fare;


}





int main(void) {
    // You may change the inputs to the function for testing
    ///taxi_fare(1, 5*60 + 50, 30, 15000);
    //double fare = taxi_fare(1, 5*60 + 50, 30, 15000); 
    //printf("The taxi fare is: $%.3f \n", fare);
    printf("Example 1: Expected end time: 18:01, expected travel distance: 1000m, expected fare: 3.40");
    double abc = taxi_fare(1, 359, 6, 1000);
    printf("Computed fare: $%.3f ------- ", abc);
    
    printf(" \n Example 2: Expected end time: 18:01, expected travel distance: 2000m, expected fare: 4.115.");
    double def =  taxi_fare(1, 5 * 60 + 57, 6, 2000);
    printf(" \n computed fare: $%.3f  ------- ", def);

    //printf("example 1 fare is: $%.3f", example1);

    return 0;
}