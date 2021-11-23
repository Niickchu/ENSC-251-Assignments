// Header file for time to set the time of appointment and also to check the validity of the time entered by the user.
#include <stdio.h>
#include <iostream>
#include <ostream>

using namespace std;

class TimeRange				
{

private:					
	int beginHour = 0;		// Appointment Start Hour variable declaration
	int	beginMinute = 0;	// Appointment Start Minute variable declaration
	int endHour = 0;		// Appointment End Hour variable declaration
	int endMinute = 0;		// Appointment End Minute variable declaration

public:
	TimeRange();
	//default constructor

	int		get_beginHour() const;	// API function that returns beginning hour of appointment slot
	int		get_beginMinute() const;	// API function that returns beginning hour of appointment slot
	int		get_endHour() const;		// API function that returns beginning hour of appointment slot
	int		get_endMinute() const;	// API function that returns beginning hour of appointment slot
	
	void	set_Time(int in_beginHour, int in_beginMinute, int in_endHour, int in_endMinute);
	//Precondition: arguments must form two timeslots. Must pass start and end times into function.
	//Initializes the time vairables according to the arguments

	int	Time_to_Index(int Hour, int Minute);
	//Precondition: arguments must form a single timeslot. Must pass hour and minutes into function.
	//Takes in a time, and returns the index to be used in appointed[] in Date class

	void output(ostream& outs);
	//function that outputs appointment times

	bool isValid(int b_hour, int b_minute, int e_hour, int e_minute);
	//function that determines if inputted timeslot is legal
};