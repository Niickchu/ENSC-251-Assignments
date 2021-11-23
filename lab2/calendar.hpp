using namespace std;

class Calendar {
private:
    
public:
    Date Sep[31];   //create public Date objects in arrays
    Date Oct[31];
    Date Nov[31];
    Date Dec[31];
    Calendar();

    //cancels all appointments within the input TimeRange on the input Date, also return info of cancelled appointments
    bool cancel(const Date &date, const TimeRange &time);
    
    //prints all appointments overlapping with the input TimeRange on the input Date
    bool query(const Date &date, const TimeRange &time);
    
    //books appointment at input TimeRange and Date. Only if it is completely available, also returns information of overlapped appointments
    bool book(const Date &date, const TimeRange &time);
    
    //prints a list of all days that have an open appointment slot
    void printFreeDays();
    
    //prints the free timeslots for a given date
    void printFreeTimeSlots(const Date& date);
    
    // << operation overloader for Calendar class
    friend ostream &operator <<(ostream &Output, Calendar &cal);
};
