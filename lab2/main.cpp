#include <iostream> //cin and cout
#include "date.hpp"
#include "calendar.hpp"
using namespace std;

TimeRange Input_to_TimeRange(); //Takes user input and returns a correlated TimeRange object
Date Input_to_Calendar_Date();  //Takes user input and returns the correlated Date object
void input_error();             //Generalized input error function that prints error message and clears buffer
Calendar Fall;                  //Create and object called Fall from Calendar Class

//String for Calendar art
string ASCII_ART = "   ___      _                _           \n  / __\\__ _| | ___ _ __   __| | ___ _ __ \n / /  / _` | |/ _ \\ '_ \\ / _` |/ _ \\ '__|\n/ /__| (_| | |  __/ | | | (_| |  __/ |   \n\\____/\\__,_|_|\\___|_| |_|\\__,_|\\___|_|   \n";

int main() {

    Date tempDate;      //Temporary date and timerange objects for use in switch statement
    TimeRange tempTime;

    cout << ASCII_ART << endl;
    cout << "Welcome, please enter your choice:\n\n";   //user prompts
    while (true) {

        int user_input;      //menu system. Printed out to user everytime after an option is selected and executed
            cout << "\n\n[1] Exit Program \n"
            "[2] Print All Booked Appointments \n"
            "[3] Print All Days That Have Free Appointment Slots\n"
            "[4] Print All Free Appointments For a Given Day \n"
            "[5] Book an Appointment \n"
            "[6] Query an Appointment\n"
            "[7] Cancel an Appointment\n\n"
            "Enter choice: ";

        cin >> user_input;      //store user input for use in switch statement
        cin.clear();            //clear buffer regardless of user input, since this is in a loop,   
        cin.ignore(1000, '\n'); //and error checking is done by the switch statement, this functions as input validation
        cout << endl;

        switch (user_input)     //determines user input and executes corresponding code
        {
        case 1:     //exits the program
            return 0;
            break;
                
        case 2:     //uses overloaded operator to output booked timeslot information from Fall
            cout << Fall;
            break;
                
        case 3:     //prints out all days with slots available for booking
            Fall.printFreeDays();
            break;
                
        case 4:     //prints out all free timeslots for a given day
            tempDate = Input_to_Calendar_Date();    //returns corresponding TimeRange object from user input
            Fall.printFreeTimeSlots(tempDate);
            break;
                
        case 5:     //books a new appointment if the appointment slot is available
            tempDate = Input_to_Calendar_Date();    //returns corresponding Date object from user input
            tempTime = Input_to_TimeRange();        //returns corresponding TimeRange object from user input
            Fall.book(tempDate, tempTime);          //books an appointment over the specified date and timerange
            break;
                
        case 6:    //outputs to user whether the inputted date and time range has been booked or partially booked
            tempDate = Input_to_Calendar_Date();    //returns corresponding Date object from user input
            tempTime = Input_to_TimeRange();        //returns corresponding TimeRange object from user input
            Fall.query(tempDate, tempTime);         //returns query over inputted date and time arguments
            break;
                
        case 7:     //cancels all appointments that overlap the inputted date and time range
            tempDate = Input_to_Calendar_Date();    
            tempTime = Input_to_TimeRange();        
            Fall.cancel(tempDate, tempTime);        //cancels appointments over inputted date and time arguments
            break;
                
        default:    //default case, functions as input validation
            cout << "\nPlease Enter a number between 1 and 7\n";    //outputs error message for user
            break;
        }

    }

    return 0;
}

void input_error()  //General input error function that prints error message and clears buffer
{
    cout << "\n\ninvalid entry, please follow the prompt and try again\n";  //outputs error information
    cin.clear();                //clears buffer
    cin.ignore(1000, '\n');     //clears buffer
}

Date Input_to_Calendar_Date() {     //Takes user input and returns the correlated Date object
   
    int temp_month = 0,             //temporary month for use in function
        temp_day = 0;               //temporary day for use in function
    Date error_testing_date;        //creates a temporary Date object to access private variables in Date class

    while (1) {
        cout << "Please enter the desired month and day respectively in digits, separated by a space:\n";   //user prompt
        if (!(cin >> temp_month >> temp_day)) {     //input error testing for non integer entries
            input_error();      //clears buffer, outputs error message if input is invalid
            continue;
        }
        error_testing_date.set_date(temp_day, temp_month);  //sets date day and month variables to inputted values

        if (error_testing_date.isValid(1))  //if input is invalid, print out specific error message and starts again
        {
            break;  //if input is valid, break out of loop
        }

        cin.clear();    //if input is invalid, clear buffer and start loop again
        cin.ignore(1000, '\n');
    }

    switch (temp_month) {   //switch statement used to specify inputted month to be returned as an object
    case 9:
        return Fall.Sep[temp_day - 1];  //A September object is returned with corresponding index for inputted day
    case 10:
        return Fall.Oct[temp_day - 1];  //An October object is returned with corresponding index for inputted day
    case 11:
        return Fall.Nov[temp_day - 1];  //A November object is returned with corresponding index for inputted day
    case 12:
        return Fall.Dec[temp_day - 1];  //A December object is  returned with corresponding index for inputted day
    }

}

TimeRange Input_to_TimeRange(){     //Takes user input and returns a correlated TimeRange object

    int temp_beginM,    //temporary time variables to be used in function
        temp_beginH,
        temp_endM,
        temp_endH;

    TimeRange Selected_TimeRange;   //temporary TimeRange object to access private TimeRange variables, and be returned from function

    while (1)
    {

        cout << "\n\nPlease input the START hour and minute of the time range you would like to book/cancel, ";     //user input for start time
        cout << "separated by a space\nSTART time (24hr time): ";
        if (!(cin >> temp_beginH >> temp_beginM)) {     //input error testing for non integer entries
            input_error();      //clears buffer, outputs error message if input is invalid
            continue;
        }
        cout << "\n\nPlease input the END hour and minute  of the time range you would like to book/cancel,";
        cout << "separated by a space\nEND time (24hr time): ";
        if (!(cin >> temp_endH >> temp_endM)) { //input error testing for non integer entries
            input_error();      //clears buffer, outputs error message if input is invalid
            continue;
        }

        if (!(Selected_TimeRange.isValid(temp_beginH, temp_beginM, temp_endH, temp_endM)))  //if the inputted time is not valid, print error message and start loop againw
        {
            continue;
        }

        Selected_TimeRange.set_Time(temp_beginH, temp_beginM, temp_endH, temp_endM);    //if inputted time is valid, set Selected_TimeRange object to inputted values
        return Selected_TimeRange;  //return new TimeRange object from input
    }
}
