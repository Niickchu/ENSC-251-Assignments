#include <stdio.h>
#include <iostream>
#include <ostream>
#include <vector>
#include "time.hpp"


using namespace std;

class Date {
	//a friend function that compares two date objects and returns two if
	//both the day and month are the same. Does not take intwo account
	//the appointed times.
	friend const bool equal(const Date& date1, const Date& date2);	
private:
	//the private member variables 
	int day;
	int month;
	bool appointed[48] = { false };

public:

	class appointmentInfo	//nested class. This class stores appointment info for each date class
	{
		public:
			int start_time;		//appointment start time
			int end_time;		//appointment end time
			int appointment_num;	//appointment number
			appointmentInfo();					//default constructor
			appointmentInfo(int start, int end, int num);		//constructor
			bool alreadybooked(TimeRange &time, bool output);	//input a timerange, and returns if there is a pre-existing booking over that range
			void print_info();					//prints appointment info to the console
			void get_Apps_info(ostream& outs2);			//inputs appointment info into inputter ostream variable
	};

	int test;
	//vector called day_apps that holds all appointment information for a single date object
	vector<appointmentInfo> day_apps;
	
	//adds an appointmentInfo object to the day_apps vector
	void add_app_info(int start, int end) ;
	
	// returns a vector of indices (within day_apps) for all overlapping appointments within the input TimeRange
	vector<int> check_for_appointments(TimeRange &time, bool output);

	//prints out all appointment info for given day
	void printAppointmentInfo();
	
	//sends all appointment info for given day to inputted ostream variable
	void getAppointmentInfo(ostream& out1);

	//default constructor that assigns default values to the objects variables 
	Date();

	//constructor that assigns the passed in values to their respective member variables
	Date(int _day, int _month);

	//set function that takes both the day and month, and assigns them
	void set_date(int new_day, int new_month);

	//set function that takes only the day and assignts it
	void set_day(int new_day);

	//set function that takes only the month and assigns it
	void set_month(int new_month);

	//set function that takes a start index and end index for the appointed array and
	//assigns the indexes between (inclusive) and assigns them the value of 'booked'
	void set_appointment(int start_index, int end_index, bool booked);

	//get function that takes an index for the appointed array and returns the value at
	//that index
	bool get_appointment(int slot);

	//get function that returns the objects day
	int get_day() const;

	//get function that returns the objects month
	int get_month() const;

	//returns true if the objects day and month are the same as a holiday's. 
	//false otherwise. Determined by const holiday objects
	bool isHoliday();

	//returns true if the objects day and month are the same as a weekend's. 
	//false otherwise
	bool isWeekend();

	//checks if the date falls within acceptable date rangs as determined in the assumptions
	//as well as if the date is a holiday or weekend. Returns false if the date is unacceptable, 
	//a weekend or a holiday. The returnError will return the cause of invalid dates.
	bool isValid(bool returnError);

	//function that inputs the objects information to an output stream
	void output(ostream& outs, int option);

	//prints out all currently available timeslots in 30 min intervals
	void printFreeTimeSlots();
	//prints out all currently booked timeslots in 30 min intervals
	void printAppointedTimeSlots();
	
	//takes the inputted month as an interger, and returns the corresponding month as a string
	string int_to_Month(int int_month); 
	
	//determines the suffix ending for the ordinal numbers for any inputted interger
	static string suffix(int int_day);
	
	//returns a unique integer value for an inputted date
	int unique_date(int month, int day);

};
