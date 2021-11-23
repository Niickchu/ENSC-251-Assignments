//main.cpp, put your driver code here, 
//you can manipulate your class objects here

#include <iostream> //cin and cout
#include "time.hpp" //time header file
#include "date.hpp" //date header file
using namespace std;

void user_input_for_date(Date& date1);							//prompts user to input date, and changes private date variables
void user_input_for_time(Date& date1, TimeRange& time1);		//prompts user to input time, and changes private time variables
void timerange_to_appointment(Date& date1, TimeRange& time1);	//converts time to index, and sets value of array
void input_error();												//prints input error message, and clears buffer

int main() {
	//bool second_input = false;	
	Date date1;				//creates a Date Class object called date1
	TimeRange time1;		//creates a TimeRange Class object call time1
	int appointment_date;	//holds unique value used to identify the day the appointment is on
	int current_date;		//holds unique value used to identify the currently selected date

	cout << "Welcome to the Simple Calendar System!\n\n\n";

	user_input_for_date(date1);				//prompts user for date input, and assigns values to private variables in date1 object

	appointment_date = date1.unique_date(date1.get_month(), date1.get_day());	//assigns a unique value to the inputted appointment date
	current_date = appointment_date;											//sets current date to the appointment date

	user_input_for_time(date1, time1);		//prompts user for time input, and assigns values to private variables in time1 object
	cout << "New appointment date:\n";		
	date1.output(cout, 0);					//outputs date and information about the date to the console
	time1.output(cout);						//outputs appointment start and end time to the console
	timerange_to_appointment(date1, time1);	//converts inputted time to index, and sets value of appointed[] array

	bool new_date = false;

	cout << "\n";

	while (1) //loop through prompts and input until user exits program
	{
		
		//outputs UI prompts for the user to interact with. Features may be fully utilized later
		cout << endl;
		cout << "Type '0' to exit \n";
		cout << "Type '1' to view the currently set date\n";
		cout << "Type '2' to change the currently set date\n";
		cout << "Type '3' to book a new appointment\n";
		cout << "Type '4' to cancel all appointments \n";
		cout << "Type '5' to view your current appointment times\n";
		cout << "Type '6' to view free appointment times \n";
		cout << "Type '7' to view currently booked appointment times\n";

		int userChoice;				//variable that holds user input choice
		cin.clear();				//Clears the buffer, since this is in a loop, it is left
		cin.ignore(1000, '\n');		//to iterate through each loop
		cin >> userChoice;			

		switch (userChoice)			//switch statement which provides output for user input choice
		{

		case 0:		//Exits Program
			cout << "\nThank you for booking with us!\n";
			exit (EXIT_SUCCESS);	//ends program

		case 1:		//Outputs Currently Set Date

			date1.output(cout, 0);	
			//outputs information in date1 object to console.
			break;

		case 2:		//Changes the currently set date

			user_input_for_date(date1);		
			//prompts user for date input, and assigns new values to private variables in date1 object

			current_date = date1.unique_date(date1.get_month(), date1.get_day()); 
			//updates the current unique date value to the inputted date

			new_date = true;

			cout << "\nNew Date Set\n";
			break;

		case 3:		//books another appointment

			date1.set_appointment(0, 47, false);			
			//deletes current appointment

			user_input_for_time(date1, time1);				
			//prompts user for time input, and assigns new values to private variables in time1 object

			timerange_to_appointment(date1, time1);			
			//converts new inputted time to index, and sets new value of appointed[] array

			appointment_date = date1.unique_date(date1.get_month(), date1.get_day()); 
			//updates the unique value of the appointment date to inputted date

			current_date = appointment_date;				
			//sets the current date to the newly inputted appointment date

			new_date = false;

			break;

		case 4:		//cancels all appointments

			date1.set_appointment(0, 47, false);			
			//resets appointed[] array to 0. This cancels all appointments
			new_date = true;
			cout << "\nAppointments Cleared\n";
			break;
		
		case 5:		//views appointment times

			if(new_date == true){
				cout << "No appointment set for today yet\n Try setting one with '3' command.\n";
				break;
			}

			time1.output(cout);
			
			//outputs appointment start and end time to the console

			break;

		case 6:		//views free appointment times
			if (!(current_date == appointment_date)){
				//if the current date is not the date with the appointment on it, it is free to book

				cout << "\n\nAll time slots are free\n" << endl;
				break;
			}
			date1.printFreeTimeSlots();	
			//if the current date is the date with the appointment on it, output free timeslots to the console

			break;

		case 7:		//views currently booked timeslots
			if (!(current_date == appointment_date)){
				//if the current date is not the date with the appointment on it, it is free to book

				cout << "\n\nNo time slots are booked\n" << endl;
				break;
			}

			date1.printAppointedTimeSlots();
			//if the current date is the date with the appointment on it, output taken timeslots to the console

			break;

		default:
			cout << "\nPlease Enter a number between 0 and 7\n";
			//runs if user inputs a value not between 0 and 7

			break;
		}
	}
}

void user_input_for_date(Date& date1) { 
	//prompts user for

	while (1) {
		int temp_day, temp_month;		//declare temporary day and month variables for use in function

		cout << "Please enter the desired month and day respectively in digits, separated by a space (eg. 9 16):\n";
		cin >> temp_month >> temp_day;	//user inputs intergers for month and day, separated by a space

		date1.set_date(temp_day, temp_month);	//sets day and month private variables to user input in date1 object

		if (date1.isValid(1))		//if user inputted a valid date, break out of while loop
		{
			break;
		}

		cin.clear();				//if input is invalid, clear the buffer and
		cin.ignore(1000, '\n');		//re-iterate through the loop
	}
	return; //not needed
}


void user_input_for_time(Date& date1, TimeRange& time1) {
//prompts user for time input, and assigns values to private variables in time1 object

	cout << "\nThe day's free time slots:\n";
	date1.printFreeTimeSlots();	//prints free time slots so user knows free slots to book
	cout << endl;

	while (1)
	{
		int temp_beginM,	//declare temporary begin and end time variables for use in function
			temp_beginH,
			temp_endM,
			temp_endH;

		cout << "\n\nPlease input the START hour and minute you would like to book in digits,";	//prompt user for start time
		cout << "separated by a space (eg. HH 00 or HH 30)\nSTART time (24hr time): ";
		if (!(cin >> temp_beginH >> temp_beginM)) { 
			//checks if user inputted a non-int value

			input_error();	//outputs error message and clears buffer
			continue;

		}
		cout << "\n\nPlease input the END hour and minute you would like to book in digits,";	//prompt user for end time
		cout << "separated by a space (eg. HH 00 or HH 30)\nEND time (24hr time): ";
		if (!(cin >> temp_endH >> temp_endM)) {
			//checks if user inputted a non-int value
			input_error();	//outputs error message and clears buffer
			continue;
		}

		if (!(time1.isValid(temp_beginH, temp_beginM, temp_endH, temp_endM))) //determines if inputted values are valid times ranges
		{
			continue;	//if inputted values are false, re-iterate through loop
		}

		time1.set_Time(temp_beginH, temp_beginM, temp_endH, temp_endM);	//if input is valid, assign inputted values to time1 object
		
		cout << "\n\n\n\n\n--------------------------------\nAppointment has ben set!\n";	//console output for visual appeal
		break;
	}
}


void timerange_to_appointment(Date& date1, TimeRange& time1)	//converts inputted time to index, and sets value of appointed[] array
{
	int begin_index, end_index;		//declares temporary variables for the starting and ending index

	begin_index = time1.Time_to_Index(time1.get_beginHour(), time1.get_beginMinute());	
	//gets beginning time, then converts it to an index. Assign index to temporary begin_index variable

	end_index = (time1.Time_to_Index(time1.get_endHour(), time1.get_endMinute()) -1);
	//gets ending time, then converts it to an index. Assign index to temporary end_index variable

	date1.set_appointment(begin_index, end_index, true);
	//passes index values to set_appointment function to set appointment slots to taken
}

void input_error()	//called when an input error occurs
{
	cout << "\n\ninvalid entry, please follow the prompt and try again\n"; //prompts user to retry entry
	cin.clear();			//clears buffer
	cin.ignore(1000, '\n');	//clears buffer
}
