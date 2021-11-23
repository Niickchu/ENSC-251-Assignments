#include "date.hpp"

#include <stdio.h>
#include <iostream>
#include <ostream>

#include "calendar.hpp"

Calendar::Calendar(){			//initializes date objects in the Calendar
    for(int i = 0; i < 31; i++){
        Sep[i].set_date(i+1, 9);
    }
    for(int i = 0; i < 31; i++){
        Oct[i].set_date(i+1, 10);
    }
    for(int i = 0; i < 31; i++){
        Nov[i].set_date(i+1, 11);
    }
    for(int i = 0; i < 31; i++){
        Dec[i].set_date(i+1, 12);
    }
}

vector<int> Booked_Sept,	//global vectors that stores indices of the above arrays if they are booked.
            Booked_Oct,		//When an appointment is booked for a given date, the corresponding month array
            Booked_Nov,		//stores the array index of the booked date
            Booked_Dec;		

//cancels all appointments within the input TimeRange on the input Date, also return info of cancelled appointments
bool Calendar::cancel(const Date &date, const TimeRange &time){
    Date tempDate = date;		//assigns the values of the passed in objects to temporary ones, so we dont have to worry about changing the passes in ones
    TimeRange tempTime = time;



    vector<int> booked_appointments; // local vector to hold the indices of appointments to be cancelled

    cout << "\nThe Following are Overlapping Appointments and Will be Cancelled: \n";

    switch (date.get_month()) //	switches through the months and assigns the returned indices from the check_for_appointments function
        {		      //	to a local vector
        case 9:
            booked_appointments = Sep[date.get_day()-1].check_for_appointments(tempTime, true);
            break;
        case 10:
            booked_appointments = Oct[date.get_day()-1].check_for_appointments(tempTime, true);
            break;
        case 11:
            booked_appointments = Nov[date.get_day()-1].check_for_appointments(tempTime, true);
            break;
        case 12:
            booked_appointments = Dec[date.get_day()-1].check_for_appointments(tempTime, true);
            break;
        default:
            return false;
            break;
        }
        

        if(booked_appointments.size() > 0){ //	if the local vector has more than zero elements, then erase the appointments at that index
            switch (date.get_month()) // switch through the month to make sure the changes are to the right array
                    {
                    case 9:
                        for(auto i : booked_appointments){
                            Sep[date.get_day()-1].set_appointment(Sep[date.get_day()-1].day_apps[i].start_time,Sep[date.get_day()-1].day_apps[i].end_time, false);
                        }

                        for(auto i : booked_appointments){
                            
                            Sep[date.get_day()-1].day_apps.erase(Sep[date.get_day()-1].day_apps.begin()+i);
                        }
                        break;
                    case 10:
                        for(auto i : booked_appointments){ 

                            Oct[date.get_day()-1].set_appointment(Oct[date.get_day()-1].day_apps[i].start_time,Oct[date.get_day()-1].day_apps[i].end_time, false);
                        }
                        for(auto i : booked_appointments){
                            Oct[date.get_day()-1].day_apps.erase(Oct[date.get_day()-1].day_apps.begin()+i);
                        }
                        break;
                    case 11:
                        for(auto i : booked_appointments){
                            Nov[date.get_day()-1].set_appointment(Nov[date.get_day()-1].day_apps[i].start_time,Nov[date.get_day()-1].day_apps[i].end_time, false);
                        }
                        for(auto i : booked_appointments){
                            Nov[date.get_day()-1].day_apps.erase(Nov[date.get_day()-1].day_apps.begin()+i);
                        }
                        break;
                    case 12:
                        for(auto i : booked_appointments){
                            Dec[date.get_day()-1].set_appointment(Dec[date.get_day()-1].day_apps[i].start_time,Dec[date.get_day()-1].day_apps[i].end_time, false);
                        }
                        for(auto i : booked_appointments){
                            Dec[date.get_day()-1].day_apps.erase(Dec[date.get_day()-1].day_apps.begin()+i);
                        }
                        break;
                    default:
                        return false;
                        break;
                    }
                    return true; // returns true if appointments are cancelled
        }
        
        cout << "\nNo overlapping appointments\n"; // if there are no overlapping appointments then simply print such.

        return false; // return false if no appoihtments are cancelled


}

//prints all appointments overlapping with the input TimeRange on the input Date
bool Calendar::query(const Date &date, const TimeRange &time){
    Date tempDate = date;		//assigns the values of the passed in objects to temporary ones, so we dont have to worry about changing the passes in ones
    TimeRange tempTime = time;


    vector<int> booked_appointments; // local vector to hold the indices of appointments to be cancelled

    cout << "\nThe following are overlapping appointments: \n\n";

    switch (date.get_month())	//	switches through the months and assigns the returned indices from the check_for_appointments function
        {			//	to a local vector. The info of the query will be outputted since the check_for_appointments function
        case 9:			//	prints out info of appointments overlapping with the passed in time
            booked_appointments = Sep[date.get_day()-1].check_for_appointments(tempTime, true);
            break;
        case 10:
            booked_appointments = Oct[date.get_day()-1].check_for_appointments(tempTime, true);
            break;
        case 11:
            booked_appointments = Nov[date.get_day()-1].check_for_appointments(tempTime, true);
            break;
        case 12:
            booked_appointments = Dec[date.get_day()-1].check_for_appointments(tempTime, true);
            break;
        default:
            return false;
            break;
        }
        
	// uses the size of the local vector to print amount of overlapping appointments
        if(booked_appointments.size() > 0){
            cout << booked_appointments.size() << " overlapping appointments \n\n";
            return true;	// return true if there are overlapping appointments

        }
        
        cout << "\nNo overlapping appointments\n";
        return false;	// return false if there are no overlapping appointments
	

}

//books appointment at input TimeRange and Date. Only if it is completely available, also returns information of overlapped appointments
bool Calendar::book(const Date &date, const TimeRange &time){

    Date tempDate = date;
    TimeRange tempTime = time;

    int temp_month = date.get_month();	//creates a temporary month variable to determine which global vector to write to
    int temp_day = date.get_day();	//creates a temporary day variable to use as input for the index (since the array index is always one value below the date)

    switch (temp_month) {	//uses temporary month variable to determine which vector to write to
        case 9:
            Booked_Sept.push_back(temp_day - 1);	//A September vector gets the corresponding index for a day inputted into it
            break;
        case 10:
            Booked_Oct.push_back(temp_day - 1);		//An October vector gets the corresponding index for a day inputted into it
            break;
        case 11:
            Booked_Nov.push_back(temp_day - 1);		//A November vector gets the corresponding index for day inputted into it
            break;
        case 12:
            Booked_Dec.push_back(temp_day - 1);		//A December vector gets the corresponding index for a day inputted into it
            break;
    }	//no need for default case, as input validation has already occured

    int begin_index, end_index;
	begin_index = tempTime.Time_to_Index(tempTime.get_beginHour(), tempTime.get_beginMinute()); //	assign temporary indices to use in the set_appointment function
	end_index = tempTime.Time_to_Index(tempTime.get_endHour(), tempTime.get_endMinute());


    switch (date.get_month())	//	switch through the passed in Date's month to and if the there are no overlapping appointments, book that time in the in the 
        {			//	corresponding day's appointed array, and add that info for the given day
        case 9:
            if (Sep[date.get_day() - 1].check_for_appointments(tempTime, true).size() > 0){
                return false;
            }
            Sep[date.get_day() - 1].set_appointment(begin_index, end_index, true);;
            Sep[date.get_day()-1].add_app_info(begin_index, end_index);
            
            break;
        case 10:
        if (Oct[date.get_day() - 1].check_for_appointments(tempTime, true).size() > 0){
                return false;
            }
            Oct[date.get_day() - 1].set_appointment(begin_index, end_index, true);;
            Oct[date.get_day()-1].add_app_info(begin_index, end_index);
            break;
        case 11:
            if (Nov[date.get_day() - 1].check_for_appointments(tempTime, true).size() > 0){
                return false;
            }
            Nov[date.get_day() - 1].set_appointment(begin_index, end_index, true);
            Nov[date.get_day()-1].add_app_info(begin_index, end_index);
            break;
        case 12:
            if (Dec[date.get_day() - 1].check_for_appointments(tempTime, true).size() > 0){
                return false;
            }
            Dec[date.get_day() - 1].set_appointment(begin_index, end_index, true);;
            Dec[date.get_day()-1].add_app_info(begin_index, end_index);
            break;
        default:
            return false;
            break;
        }

        cout << "\nAppointment Booked for: ";
        tempDate.output(cout, true);	//  print the info of the day the appointment was booked

        cout << endl;			//  print the time of the new appointment
        tempTime.output(cout);
        cout << endl;
        return true;
}

//prints a list of all days that have an open appointment slot
void Calendar::printFreeDays() {

    vector<int> Free_Sept,	//creates temporary vectors for each month, utilized for output
        Free_Oct,		
        Free_Nov,		
        Free_Dec,		
        Output_Vector;		

    string month_String;	//creates string utilized for output

    int tempCounter = 0;

	//linear search through September for days with free appointments
    for (int i = 7; i < 30; i++) //check days between days 8 and 30
    { 	
        if (Sep[i].isValid(false)) //if day to check is a valid day
	{ 			
            for (int j = 0; j < 48; j++) //check indices between 0 and 47 (indices of appointed array[])
	    { 		
                if (Sep[i].get_appointment(j) == 0) //if free slot anywhere in appointed[]
		{	
                    Free_Sept.push_back(i + 1); //put day in Free_Sep
                    break;  			//break to first loop
                }
            }
        }
    }

	//linear search through October for days with free appointments
    for (int i = 0; i < 31; i++) //check days between 1 and 31
    { 
        if (Oct[i].isValid(false))  //if day to check is a valid day
	{
            for (int j = 0; j < 48; j++) //check indices between 0 and 47 (indices of appointed array[])
	    { 
                if (Oct[i].get_appointment(j) == 0) //if free slot anywhere in appointed[]
		{ 
                    Free_Oct.push_back(i + 1); 	//put day in Free_Oct
                    break;  			//break to first loop
                }
            }
        }
    }

	//linear search through November for days with free appointments
    for (int i = 0; i < 30; i++) //check days between 1 and 30
    { 
        if (Nov[i].isValid(false)) //if day to check is a valid day
	{ 
            for (int j = 0; j < 48; j++) //check indices between 0 and 47 (indices of appointed array[])
	    { 
                if (Nov[i].get_appointment(j) == 0) //if free slot anywhere in appointed[]
		{ 
                    Free_Nov.push_back(i + 1); 	//put day in Free_Nov
                    break;  			//break to first loop
                }
            }
        }
    }

	//linear search through December for days with free appointments
    for (int i = 0; i < 7; i++)  //check days between 1 and 7
    {
        if (Dec[i].isValid(false)) //if day to check is a valid day
	{
            for (int j = 0; j < 48; j++) //check indices between 0 and 47 (indices of appointed array[])
	    { 
                if (Dec[i].get_appointment(j) == 0) {//if free slot anywhere in appointed[]
			
                    Free_Dec.push_back(i + 1); 	//put day in Free_Dec
                    break;  			//break to first loop
                }
            }
        }
    }

    for (int k = 0; k < 4; k++)	//used to generalize output code. Each k value represents a month. Loop through months September to December
    {
        if (k == 0) {
            month_String = "September";	// k == 0 represents September. Assign the output string: 'month_String' the string: "September"
            Output_Vector = Free_Sept;	// Copies the gvector Free_Sept, into local vector Output_Vector. Output_Vector now holds the free days for September
        }
        else if (k == 1) {
            month_String = "October";	// k == 1 represents October. Assign the output string: 'month_String' the string: "October"
            Output_Vector = Free_Oct;	// Copies the vector Free_Oct, into local vector Output_Vector. Output_Vector now holds the free days for October
        }
        else if (k == 2) {
            month_String = "November";	// k == 2 represents November. Assign the output string: 'month_String' the string: "November"
            Output_Vector = Free_Nov;	// Copies the vector Free_Nov, into local vector Output_Vector. Output_Vector now holds the free days for November
        }
        else {
            month_String = "December";	// k == 3 represents December. Assign the output string: 'month_String' the string: "December"
            Output_Vector = Free_Dec;	// Copies the vector Free_Dec, into local vector Output_Vector. Output_Vector now holds the free days for December
        }

        tempCounter = 0;	
        cout << "\n\nThese Days in " << month_String << " have free days:\n\n";	//outputs the month that the following days belong to

        for (int i = 0; i < Output_Vector.size(); i++)	//Output_Vector holds the days, loop through the entire output vector
        {

            cout << Output_Vector[i] << Date::suffix(Output_Vector[i]) << ", ";  //outputs the day in ordinal numbers, ie 12th, 21st, 7th              
            tempCounter++;
            if (tempCounter >= 5) {	//every 5 outputs, start a new line
                tempCounter = 0;
                std::cout << endl << endl;
            }

        }
    }
}

//prints the free timeslots for a given date
void Calendar::printFreeTimeSlots(const Date& date){
    Date printFTS = date;		//takes in user inputted date, and copies to temporary date: printFTS
    printFTS.printFreeTimeSlots();	//uses temporary date to print out the free timeslots for a given date using the printFreeTimeSlots function
}

// << operation overloader for Calendar class
ostream& operator <<(ostream& Output, Calendar& cal)
{
    vector<int> Output_Vector;	//creates a temporary output vector used for output
    string month_String;	//creates a string for output

    bool skipSeptember = 0;	//creates bools for each month, to determine if each month should be skipped in output
    bool skipOctober = 0;	//set to 0 means that it will not be skipped
    bool skipNovember = 0;
    bool skipDecember = 0;

    if (Booked_Sept.empty()) {	//if global vector is empty, set skipSeptember to true. September output is now skipped
        skipSeptember = true;
    }
    if (Booked_Oct.empty()) {	//if global vector is empty, set skipOctober to true. October output is now skipped
        skipOctober = true;
    }
    if (Booked_Nov.empty()) {	//if global vector is empty, set skipNovember to true. November output is now skipped
        skipNovember = true;
    }
    if (Booked_Dec.empty()) {	//if global vector is empty, set skipDecember to true. December output is now skipped
        skipDecember = true;
    }

    if ((skipDecember && skipNovember) && (skipOctober && skipSeptember)) {	//if all bools are set to be skipped, there should be no outputted days
        Output << "There are no booked slots\n\n";	//output to user
        return Output;	
    }

    for (int Selected_month = 9; Selected_month <= 12; Selected_month++) //used to generalize output code. Loop through months September to December
    {
        switch (Selected_month) 
        {
        case 9:
            month_String = "September ";	//if selected month is September, assign local output variables the corresponding correct values
            Output_Vector = Booked_Sept;
            break;
        case 10:
            month_String = "October ";		//if selected month is October, assign local output variables the corresponding correct values
            Output_Vector = Booked_Oct;
            break;
        case 11:
            month_String = "November ";		//if selected month is November, assign local output variables the corresponding correct values
            Output_Vector = Booked_Nov;
            break;
        case 12:
            month_String = "December ";		//if selected month is December, assign local output variables the corresponding correct values
            Output_Vector = Booked_Dec;
            break;

        }



        for (int i = 0; i < Output_Vector.size(); i++)	//Output_Vector holds the booked days, loop through the entire output vector
        {

            if ((Selected_month == 9) && (!skipSeptember))	//if month is september, and not set to be skipped
            {
                Output << "\n\nAppointment info for " << month_String << Output_Vector[i]+1 << Date::suffix(Output_Vector[i]+1); //outputs the date that the following appointments belong to
                Output << "\n-----------------------------------\n";
                cal.Sep[Output_Vector[i]].getAppointmentInfo(Output); //print out appointment info from Sep[x] where x is a index of a day with an appointment
                continue;
            }

            if ((Selected_month == 10) && (!skipOctober))	//if month is october, and not set to be skipped
            {
                Output << "Appointment info for " << month_String << Output_Vector[i]+1 << Date::suffix(Output_Vector[i]+1); //outputs the date that the following appointments belong to
                Output << "\n-----------------------------------\n";
                cal.Oct[Output_Vector[i]].getAppointmentInfo(Output); //print out appointment info from Oct[x] where x is a index of a day with an appointment
                continue;
            }

            if ((Selected_month == 11) && (!skipNovember))	//if month is november, and not set to be skipped
            {
                Output << "Appointment info for " << month_String << Output_Vector[i]+1 << Date::suffix(Output_Vector[i]+1); //outputs the date that the following appointments belong to
                Output << "\n-----------------------------------\n";
                cal.Nov[Output_Vector[i]].getAppointmentInfo(Output); //print out appointment info from Nov[x] where x is a index of a day with an appointment
                continue;
            }

            if ((Selected_month == 12) && (!skipDecember))	//if month is december, and not set to be skipped
            {
                Output << "Appointment info for " << month_String << Output_Vector[i]+1 << Date::suffix(Output_Vector[i]+1); //outputs the date that the following appointments belong to
                Output << "\n-----------------------------------\n";
                cal.Dec[Output_Vector[i]].getAppointmentInfo(Output); //print out appointment info from Dec[x] where x is a index of a day with an appointment
                continue;
            }
        }
    }
    return Output; //return output. This has all information from above loop
}
