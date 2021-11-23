//time.cpp to implement your class
#include "time.hpp"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

TimeRange::TimeRange() {

}
// default constructor

int TimeRange::get_beginHour() { return beginHour; };		//API function that returns the value of the private variable beginHour
int	TimeRange::get_beginMinute() { return beginMinute; };	//API function that returns the value of the private variable beginMinute
int	TimeRange::get_endHour() { return endHour; };			//API function that returns the value of the private variable endHour
int	TimeRange::get_endMinute() { return endMinute; };		//API function that returns the value of the private variable endMinute


int TimeRange::Time_to_Index(int Hour, int Minute)	//function that returns an index correlated with the arguments passed in
{
	int index = (60 * Hour + Minute) / 30;			//converting hours to minutes, then adding minutes all divided by 30 returns an index value

	return index;
}


void TimeRange::set_Time(int in_beginHour, int in_beginMinute, int in_endHour, int in_endMinute) //function that sets a value to private variables
{ 
	beginHour = in_beginHour;		// sets beginning hour
	beginMinute = in_beginMinute;	// sets beginning minute
	endHour = in_endHour;			// sets ending hour
	endMinute = in_endMinute;		// sets ending minute
}


bool TimeRange::isValid(int b_hour, int b_minute, int e_hour, int e_minute)	//function that determines if inputted time is valid
{
	if ((b_hour < 0) || (b_hour >= 24)) //Checks if beginning time is between 00:00 and 23:00
	{
		cout << "\n\nError: Please select a start time between 00:00 and 23:30\n\n";
		return 0;	//return false (invalid) if start time is past 23:30
	}

	if ((e_hour < 0) || (e_hour > 24)) //Checks if ending hours are between 0 and 24
	{
		cout << "\n\nError: Please select an ending time between 00:30 and 24:00\n\n";
		return 0;	//return false (invalid) if end time is before 00:30 or past 24:00
	}

	if (!(b_minute == 0 || b_minute == 30))	//Checks if beginning minutes are either 0 or 30
	{
		cout << "\n\nError: Please input either 0 or 30 for beginning minutes\n\n";
		return 0;	//return false (invalid) if beginning minutes are not 0 or 30
	}

	if (!(e_minute == 0 || e_minute == 30)) //Checks if ending minutes are 00 or 30
	{
		cout << "\n\nError: Please input either 0 or 30 for ending minutes\n\n";
		return 0;	//return false (invalid) if beginning minutes are not 0 or 30
	}

	if ((e_hour < b_hour) || ((e_hour == b_hour) && (e_minute < b_minute))) //checks if end time is before start time
	{
		cout << "\n\nError: Selected ending time is before the beginning time\n\n";
		return 0;	//return false (invalid) if end time is before start time
	}

	else if ((b_hour == e_hour) && (b_minute == e_minute)) //checks if beginning time = end time
	{
		cout << "\n\nError: Selected ending time is the same as the selected beginning time\n\n";
		return 0;	//return false (invalid) if end time is equal to start time
	}

	else if ((e_hour == 24) && (e_minute == 30))	//Special case. checks if client attempted to book for 24:30
	{
		cout << "\n\nError: Selected appointment cannot end past 24:00\n\n";
		return 0; //returns false (invalid) if end time is 24:30 
	}

	else 
	{
		return 1;
	}
}



void TimeRange::output(ostream& outs) //function that outputs the start and end times
{

	string temp_beginhour;	//declare begin hour output string
	string temp_beginmins;	//declare begin minute output string

	if (beginHour < 10)		//if beginning hour is a single digit, add a leading 0
	{

		temp_beginhour = "0" + to_string(beginHour);	//adds string "0" to beginning hour. Beginning hour outputted as a string

	}
	else { temp_beginhour = to_string(beginHour); }		//if hour is two digits, output beginning hour as a string
	if (beginMinute < 30)	//if beginning minute is 0, add a leading 0
	{

		temp_beginmins = "0" + to_string(beginMinute); //adds string "0" to beginning minute. Beginning minute outputted as a string

	}
	else { temp_beginmins = to_string(beginMinute); }	//if beginning minute is 30, output beginning minute as a string
	outs << "Your beginning time is:\t " << temp_beginhour << ":" << temp_beginmins << endl;

	string temp_endhour;		//declare end hour output string
	string temp_endmins;		//declare end minute output string

	if (endHour < 10)			//if ending hour is a single digit, add a leading 0
	{

		temp_endhour = "0" + to_string(endHour);	//adds string "0" to ending hour. Ending hour outputted as a string

	}
	else { temp_endhour = to_string(endHour); }		//if hour is two digits, output ending hour as a string
	if (endMinute < 30)			//if ending minute is 0, add a leading 0
	{

		temp_endmins = "0" + to_string(endMinute);	//adds string "0" to ending minute. Ending minute outputted as a string

	}
	else { temp_endmins = to_string(endMinute); }	//if beginning minute is 30, output beginning minute as a string
	
	outs << "Your ending time is:\t " << temp_endhour << ":" << temp_endmins << endl; // output stream
}