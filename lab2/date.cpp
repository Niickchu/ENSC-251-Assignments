//date.cpp to implement your class
//testedit
#include "date.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <vector>

using namespace std;

string to_time(int index);
//nested class things

int to_index(int Hour, int Minute)	//function that returns an index correlated with the arguments passed in
{
	int index = (60 * Hour + Minute) / 30;			//converting hours to minutes, then adding minutes all divided by 30 returns an index value

	return index;
}

//prints out all appointment info for given day
void Date::appointmentInfo::print_info(){
	cout << "Appointment Info: \n\n";
	cout << "Start Time: " << to_time(start_time) << endl;	//outputs start time for given appointment
	cout << "End Time: " << to_time(end_time) << endl;	//outputs end time for given appointment
	cout << "Appointment Number: " << appointment_num << endl << endl;	//outputs appointment number

}

//sends all appointment info for given day to inputted ostream variable
void Date::appointmentInfo::get_Apps_info(ostream& Outs) 
{
	Outs << "Appointment Number " << appointment_num << endl; 	//inputs appointment number to passed in ostream variable
	Outs << "Start Time: " << to_time(start_time) << endl;		//inputs start time for given appointment to passed in ostream variable
	Outs << "End Time: " << to_time(end_time) << endl << endl;	//inputs end time for given appointment to passed in ostream variable
}

// returns a vector of indices (within day_apps) for all overlapping appointments within the input TimeRange
vector<int> Date::check_for_appointments(TimeRange &time, bool output){
	vector<int> indices;
	int counter = day_apps.size();
	int index = 0;
	for(auto i : day_apps){
	
		
		if(i.alreadybooked(time, output)){
			cout << endl;
			indices.push_back(index);
			if(output){
			day_apps[index].print_info();
			}
		}
		
		index++;
	}
	return indices;
}

// returns true if the passed in TimeRange is booked on the given day.
bool Date::appointmentInfo::alreadybooked(TimeRange &time, bool output){
	int start_index = time.Time_to_Index(time.get_beginHour(), time.get_beginMinute());
	int end_index = time.Time_to_Index(time.get_endHour(), time.get_endHour());

	bool start_overlap = false;
	bool end_overlap = false;
	bool partial_overlap = false;
	bool complete_overlap = false;

	for(int i = start_index; i <= end_index; i++){
		if(start_time == i){
			start_overlap = true;
			partial_overlap = true;
		}
		if(end_time == i){
			partial_overlap = true;
			end_overlap = true;
		}
	}
	

	if(start_overlap && end_overlap){
		complete_overlap = true;
	}
	if(start_index < start_time && end_index > end_time){
		complete_overlap = true;
	}
	if(start_index > start_time && end_index < end_time){
		complete_overlap = true;
	}

	cout << endl;

	if(complete_overlap){
		if(output){
		cout << "Complete booking overlap \n";}
		return true;
	}else if (partial_overlap)
	{
		if(output){
		cout << "Partial overlap \n";}
		return true;
	}
	
	return false;

}

//default constructor for appointmentInfo
Date::appointmentInfo::appointmentInfo() : start_time(0), end_time(0), appointment_num(0) {} //initializes value to 0 by default

//constructor for appointmentInfo
Date::appointmentInfo::appointmentInfo(int start, int end, int num) : start_time(start), end_time(end), appointment_num(num) {} //

//adds a appointmentInfo object to the day_apps vector
void Date::add_app_info(int start, int end) {
	int size = day_apps.size();
	appointmentInfo tempAppInfo = appointmentInfo(start, end, size + 1);
	day_apps.push_back(tempAppInfo);	

}

//prints out all appointment info for given day
void Date::printAppointmentInfo(){

	int size = day_apps.size();	//gets size of day_apps vector. day_apps stores all apointment info for a given day

	for(int i = 0; i < size; i ++){	//loop through entire day_apps vector

		day_apps[i].print_info();	//utilizes print_info function to print out info for entire day_apps vector
	}

}

//Sends all appointment info for a given day to an ostream
void Date::getAppointmentInfo(ostream &out1) {

	int size = day_apps.size();	//gets size of day_apps vector. day_apps stores all apointment info for a given day

	for (int i = 0; i < size; i++) 	//loop through entire day_apps vector
	{
		day_apps[i].get_Apps_info(out1); //utilizes get_Apps_info to input appointment info into passed in outs variable
	}

}

//default constructor assigns the date to 9/8
Date::Date() : day(8), month(9) {}

//constructor that takes in a day and month and initializes the object's
//day and month variable to be the same
Date::Date(int _day, int _month) : day(_day), month(_month) {}

//Date object constants to compare with other date objects to check if they are holidays.
//Tar is Truth and Reconciliation, TD is Thanksgiving, RD is Remembrance Day
const Date TaR(30, 9);
const Date TD(11, 10);
const Date RD(11, 11);


const bool equal(const Date& date1, const Date& date2) {
	bool equal_day = date1.day == date2.day;
	bool equal_month = date1.month == date2.month;
	return (equal_day && equal_month);
	//returns true only if the day and month of date1 is the same as the
	//date2's day and month
}

void Date::set_date(int _day, int _month) {

	//assigns the passed in values the objects private variables
	day = _day;
	month = _month;
}

//a not member function that takes an appointed array index and returns it as a
//colon seperated time
string to_time(int index) {
	string time;

	//since the appointed array is in intervals of 30 min, the minutes
	//can be found by multiplying the index by 30
	int temp_min = index * 30;
	int min = temp_min % 60;
	int hours = floor(temp_min / 60);
	int temp_time = hours * 100 + min;

	//checks how great the time variables is to check determine how many zeroes are
	//needed to keep a constant amount of digits
	if (temp_time < 10) {

		time = "000" + to_string(temp_time);

	}
	else if (temp_time < 100) {

		time = "00" + to_string(temp_time);

	}
	else if (temp_time < 1000) {
		time = "0" + to_string(temp_time);

	}
	else {

		time = to_string(temp_time);

	}

	//inserts a colon into the middle of time string to complete the formatting
	time = time.insert(2, ":");

	return time;
}

void Date::set_day(int new_day) {

	//sets the object's day variable to the passed in new_day
	day = new_day;
}

void Date::set_month(int new_month) {

	//sets the object's month variable to the passed in new_month
	month = new_month;

}


void Date::set_appointment(int start_index, int end_index, bool booked) {

	//using a for loop to set all the values inclusively bewteen the passed in indexes
	//to the value of 'booked'
	for (int i = start_index; i <= end_index; i++) {

		appointed[i] = booked;

	}

}



bool Date::get_appointment(int slot) {
	//returns the value of appointed array and index slot
	return appointed[slot];

}

//returns the value of private variable 'day'
int Date::get_day() const { return day; }
//returns the value of private variable 'month'
int Date::get_month() const { return month; }

//uses the equal function to check if the object is the same as a const holiday declared above
bool Date::isHoliday() {

	return (equal(*this, TaR) || equal(*this, TD) || equal(*this, RD));
}


bool Date::isWeekend() {
	//this function utilizes the first Saturday in each month to check if the objects day
	//is 7 or 8 days later. Then, since if it is the day must be a saturday or sunday, so 
	//the function will return true


	if (month == 9) {
		for (int i = 4; i <= 30; i = i + 7) {
			if (day == i || day == i + 1) {
				return true;
			}
		}
	}
	if (month == 10) {
		for (int i = 2; i <= 31; i = i + 7) {
			if (day == i || day == i + 1) {
				return true;
			}
		}
	}

	if (month == 11) {
		for (int i = 6; i <= 30; i = i + 7) {
			if (day == i || day == i + 1) {
				return true;
			}
		}
	}
	if (month == 12) {
		for (int i = 4; i <= 31; i = i + 7) {
			if (day == i || day == i + 1) {
				return true;
			}
		}
	}

	return false;
}


//uses the previously defined acceptable dates, isWeekend function and isHoliday function
 //to determine if the date is considered valid

bool Date::isValid(bool returnError) {
	bool validDate;

	if (month == 9) {
		validDate = day > 7 && day < 31;
	}
	else if (month == 10) {
		validDate = day > 0 && day < 32;
	}
	else if (month == 11) {
		validDate = day > 0 && day < 31;
	}
	else if (month == 12) {

		validDate = day > 0 && day < 32;
	}
	else {
		validDate = false;
	}


	//if the returnError parameter is true, also show the reason for invalidity
	if (returnError && (!validDate || isHoliday() || isWeekend())) {
		cout << "Invalid Entry. Reason:" << endl;
		if (!validDate) {
			cout << "Invalid month or day" << endl;
		}
		if (isHoliday()) {
			cout << "Date is a holiday" << endl;
		}
		if (isWeekend()) {
			cout << "Date is a weekend" << endl;
		}

	}

	return(validDate && !(isHoliday()) && !(isWeekend()));

}

//outputs the objects data to the passed in outs output stream
void Date::output(ostream& outs, int option) {
	outs << endl;

	//outputs the day and month and the...
	outs << "Date: " << int_to_Month(month) << " " << day << suffix(day) << endl;

	//skips the extra information if the option parameter is 1
	if (option == 1)
	{
		return;
	}

	//outputs if the day is a valid weekday and...
	outs << "Valid Weekday? ";
	if (isValid(false)) {
		outs << "Yes.";
	}
	else { outs << "No."; }

	//outputs if the day is a holiday and...
	outs << endl;
	outs << "Holiday? ";

	if (isHoliday()) {
		outs << "Yes.";
	}
	else { outs << "No."; }

	outs << endl;

	//outputs if the day is a weekend.
	outs << "Weekend? ";

	if (isWeekend()) {
		outs << "Yes.";
	}
	else { outs << "No. "; }

	outs << endl;

}

//converts month inputted as an integer to a month as a string
string Date::int_to_Month(int int_month) 
{	
	//the 9th month is September
	if (month == 9)
	{
		return "September";
	}
	//the 10th month is October
	if (month == 10)
	{
		return "October";
	}
	//the 11th month is November
	if (month == 11)
	{
		return "November";
	}
	//the 12th month is December. User can only input values from 0 to 9, therefore this will cause no errors
		return "December";
}

//returns suffix ending for any integer inputted as a string
string Date::suffix(int int_day)
{
	//the 11th, 12th, and 13th are special cases for ordinal numbers, return separately
	if (int_day >= 11 && int_day <= 13) 
	{
		return "th";
	}
	//determines the rightmost digit, and inputs into switch statement
	switch (int_day % 10)
	{
		case 1:  return "st";	// if rightmost digit is 1, return the suffix 'st'
		case 2:  return "nd";	// if rightmost digit is 2, return the suffix 'nd'
		case 3:  return "rd";	// if rightmost digit is 3, return the suffix 'rd'
		default: return "th";	// else, return the suffix 'th'
	}
}

//prints out all the free time slots in grid.
void Date::printFreeTimeSlots() {
	std::cout << "\n\nFree time slots:\n\n";
	int totalAppointments = 0;
	int tempCounter = 0;
	for (int i = 0; i < 48; i++) {
		//uses the appointed array to check for the free slots
		if (appointed[i] == false) {
			tempCounter++;
			totalAppointments++;
			printf("[%d] ", i + 1);
			std::cout << to_time(i) << "\t";

			//we create a newline if the tempCounter variable is equal or greater than 5
			//so the the grid is at max 5 entries wide
			if (tempCounter >= 5) {
				tempCounter = 0;
				std::cout << endl << endl;
			}
		}
	}

	//simply out outs that there are no free slots if there are none
	if (totalAppointments == 0) {
		cout << "There are no free slots.";
	}
	std::cout << endl;
}

//prints out all the booked time slots in grid.
void Date::printAppointedTimeSlots() {
	std::cout << "Booked time slots: \n\n";
	int totalAppointments = 0;
	int tempCounter = 0;
	for (int i = 0; i < 48; i++) {
		//uses the appointed array to check for the booked slots
		if (appointed[i] == true) {
			tempCounter++;
			totalAppointments++;
			std::cout << to_time(i) << "-" << to_time(i + 1) << "  ";

			//we create a newline if the tempCounter variable is equal or greater than 5
			//so the the grid is at max 5 entries wide
			if (tempCounter >= 5) {
				tempCounter = 0;
				std::cout << endl << endl;
			}
		}
	}

	//simply out outs that there are no booked slots if there are none
	if (totalAppointments == 0) {
		cout << "There are no booked slots.";
	}
	std::cout << endl;
}

//returns a unique integer value for an inputted date
int Date::unique_date(int month, int day) 
{	
	//since days of the month never surpass 100, we can create a unique value for each date by multiplying
	//the month by 100, and adding the day. The month will be stored in the 100's or 1000's place, while the day
	//is in the ones or tens place.
	int unique = (month * 100) + day;
	return unique;
}
