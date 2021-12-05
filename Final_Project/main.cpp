#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream> //formatted string processing
#include <cstdlib> //atof and atoi
#include "student.hpp"
#include "list.hpp"
#include "unit.hpp"
#include "spellcheck.hpp" // oops

extern string Countries[5];
extern string Provinces[13];

//function headers
int getint();
double getdouble();
float getfloat();
string getword();

int menu(){
  int user_input;
  bool open = true;//true = keep open, false = close program
    int userInput1;
    int userInput2;
    int userInput3;
    int fixed = 0;
    
    //for search function
    int userInputID;
    double userInputCGPA;
    float userInputScore;
    char userInputRemove_c;
    bool remove;
    string userInputName;
    string userInputRemove_s;

    //for new node
    string firstName;
    string lastName;
    float CGPA;
    int score;
    int ID;
    string country;
    //for international
    int reading;
    int listening;
    int speaking;
    int writing;

    //for deleting node
    int index;

    DSLinkedList domestic_students;
    ISLinkedList intern_students;
    string line;
    ifstream domesticFile("domestic-stu.txt");
    if (!domesticFile.is_open())
    {
        std::cout << "Unable to open file domestic-stu.txt" << endl;
        return -1;
    }

    //for searching merged list
    float cgpa_threshold;
    int researchScore_threshold;

    //Read the first line of domestic-stu.txt, which specifies
    //the file format. And then print it out to the screen
    getline(domesticFile, line);

    int stu_count = 1;
    while (getline(domesticFile, line))
    {
        istringstream ss(line);

        string firstName, lastName, province, s_cgpa, s_researchScore;
        float cgpa;
        int researchScore;

        //get firstName separated by comma
        getline(ss, firstName, ',');

        //get lastName separated by comma
        getline(ss, lastName, ',');

        //get province separated by comma
        getline(ss, province, ',');

        //get cpga separated by comma, and convert string to float
        getline(ss, s_cgpa, ',');
        cgpa = atof(s_cgpa.c_str());

        //get researchScore separated by comma, and convert it to int
        try {
            getline(ss, s_researchScore, ',');
            if (!ss) {
                throw 66;
            }
        }
        catch (...) {
            cout << "\nInput field for domestic student is missing\n\nExiting Program...\n";
            exit(66);
        }

        researchScore = atoi(s_researchScore.c_str());

        int temp_id = 20210000 + stu_count;

        DomesticStudent temp_student(firstName, lastName, cgpa, researchScore, temp_id, province);

        bool check = temp_student.Check_Valid_Province(temp_student);
        if (!check)
        {
            cout << "\n\nInvalid Province Inputted, Exiting Program...\n";
                exit(66);
        }

        domestic_students.AddNode(temp_student);

        // domestic_students.Sort();

        stu_count++;

        //bool valid = Check_Error_Domestics()
        //if (valid == false){
          //std::cout<<"\n\nExiting Program...\n\n";
          //exit(66); //exit failure
        //}
    }

    domesticFile.close();
    // domestic_students.print();

    string line2;
    ifstream InternationalFile("international-stu.txt");
    if (!InternationalFile.is_open())
    {
        cout << "Unable to open file international-stu.txt" << endl;
        return -1;
    }

    //Read the first line of international-stu.txt, which specifies
    //the file format. And then print it out to the screen
    getline(InternationalFile, line2);

    while (getline(InternationalFile, line2))
    {

        istringstream ss(line2);

        string firstName, lastName, country, s_cgpa, s_researchScore, s_r, s_l, s_s, s_w, temp_country;
        float cgpa;
        int researchScore;
        int r, l, s, w;
        bool error = 0;
        int _index = -1;

        //get firstName separated by comma
        getline(ss, firstName, ',');

        //get lastName separated by comma
        getline(ss, lastName, ',');

        //get province separated by comma
        getline(ss, country, ',');

        //get cpga separated by comma, and convert string to float
        getline(ss, s_cgpa, ',');
        cgpa = atof(s_cgpa.c_str());

        //get researchScore separated by comma, and convert it to int
        getline(ss, s_researchScore, ',');
        researchScore = atoi(s_researchScore.c_str());

        getline(ss, s_r, ',');
        r = atoi(s_r.c_str());

        getline(ss, s_l, ',');
        l = atoi(s_l.c_str());

        getline(ss, s_s, ',');
        s = atoi(s_s.c_str());

        try{getline(ss, s_w, ',');
        if (!ss) {
                throw 66;
            }
        }
        catch (...) {
            cout << "\nInput field for international student is missing\n\nExiting Program...\n";
            exit(66);
        }
        w = atoi(s_w.c_str());

        int temp_id = 20210000 + stu_count; //creates unique student # for each student

        InternationalStudent temp_student(firstName, lastName, cgpa, researchScore, temp_id, country, r, l, s, w); //creates new student
        int Unknown = Spell::spellingMistakeCountry(country, error, _index);
    if (error) {
        if (Unknown == 4) {
            cout << "\nUnknown Country was inputted, which could not be spell corrected."
                << "\nExiting program...\n\n\n";
            exit(66);
        }
        else
        {
            switch (_index)
            {
            case 0:
                temp_country = "Canada";
                break;
            case 1:
                temp_country = "China";
                break;
            case 2:
                temp_country = "India";
                break;
            case 3:
                temp_country = "Iran";
                break;
            case 4:
                temp_country = "Korea";
                break;
            }
            temp_student.set_country(temp_country);
            cout << "Spelling mistake detected: " << country << " was changed to " << temp_country << endl;
            fixed++;
        }
    }

        intern_students.AddNode(temp_student); //put new students into a vector

        stu_count++;
    }

    RemoveHeadTail(domestic_students);


  string ASCII_ART = " __          __  ______   _         _____    ____    __  __   ______     _ \n \\ \\        / / |  ____| | |       / ____|  / __ \\  |  \\/  | |  ____|   | |\n  \\ \\  /\\  / /  | |__    | |      | |      | |  | | | \\  / | | |__      | |\n   \\ \\/  \\/ /   |  __|   | |      | |      | |  | | | |\\/| | |  __|     | |\n    \\  /\\  /    | |____  | |____  | |____  | |__| | | |  | | | |____    |_|\n     \\/  \\/     |______| |______|  \\_____|  \\____/  |_|  |_| |______|   (_)\n                                                                           \n";

  if (fixed) {
      std::cout << "\n\n\nThere were " << fixed << " Spelling mistakes, that were fixed on start up\n\n\n";
  }
  cout << ASCII_ART;
  

  while (open){

    cout << "\n\n\n------------------------\n";
    cout << "Please enter your choice\nWould you like to sort, view and modify?\n";
    cout << "[1] The Domestic Students list\n OR\n";
		cout << "[2] The International Students list\n";
    cout << "OR\n";
    cout << "[3] Merge the Domestic Students list and the International Students list\n";
    cout << "[4] View unit tests\n";
    cout << "[0] Alternatively, enter 0 to exit program\n\n";
		cout << "Please enter either a number between 0 and 4: ";

    userInput1 = getint();
    switch (userInput1)
    {
      case 0:
      {
      cout << "\n\nExiting Program...\n";
      open = false;
      continue;
      }

      case 1:
      {
        cout << "\n\nWhat would you like to do?\n";
        cout << "[1] Search through existing Domestic Student List\n";
        cout << "[2] Create a new Domestic Student Node\n";
        cout << "[3] Delete existing Domestic Student Node\n";
        cout << "[4] Delete head and tail node from the existing Domestic Student List\n";
        cout << "[5] View full list\n";
        cout << "[0] Enter 0 to exit the program\n";
        cout << "Please enter a number between 0 and 5: ";
        
        userInput2 = getint();

        switch (userInput2)
        {
          case 0:
          {
            cout << "\n\nExiting Program\n";
            open = false;
            continue;
          }//end case 0

          case 1:
          {
            cout << "\n\nHow would you like to search the Domestic Student List?\n";
            cout << "[1] Application ID\n";
            cout << "[2] CGPA\n";
            cout << "[3] Research Score\n";
            cout << "[4] First and Last Name\n";
            cout << "Please enter a number between 1 and 4: ";

            userInput3 = getint();

            switch (userInput3)
            {
              case 1:
              {
                cout << "Input an ID: ";
                userInputID = getint();
                SearchID <DSLinkedList, DomesticStudent> (domestic_students, userInputID);
                continue;
              }//end case 1

              case 2:
              {
                cout << "Input a CGPA: ";
                userInputCGPA = getdouble();
                SearchCGPA <DSLinkedList, DomesticStudent> (domestic_students, userInputCGPA);
                continue;
              }//end case 2

              case 3:
              {
                cout << "Input a Research Score: ";
                userInputScore = getfloat();
                SearchScore <DSLinkedList, DomesticStudent> (domestic_students, userInputScore);
                continue;
              }//end case 3

              case 4:
              {
                //getting name
                cout << "Input a name: [FirstNameLastName]\n";
                userInputName = getword();

                //getting remove
                cout << "Would you like to remove this student from the list?(Y/N)\n";
                getline(cin, userInputRemove_s);

                //checking if the value inputted is invalid
                while (cin.fail() || cin.eof() || userInputRemove_s.find_first_not_of("YNyn") != string::npos || userInputRemove_s.empty())
                {
                  cout << "\nError, invalid input\nPlease enter a Y or N: ";

                  if (userInputRemove_s.find_first_not_of("YN") == string::npos) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                  }

                  getline(std::cin, userInputRemove_s);
                }
                userInputRemove_c = userInputRemove_s[0];

                //assigning remove based on user input
                if (userInputRemove_c == 'Y'){
                  remove = true;
                }else if (userInputRemove_c == 'N'){
                  remove = false;
                }
                SearchName <DSLinkedList, DomesticStudent> (domestic_students, userInputName, remove);
                continue;
              }//end case 4

              default:
              {
                cout << "Invalid Input, enter a number between 1 and 4: \nPress Enter to continue...";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
              }//end default
              continue;
            }//end userInput 3
          continue;
          }//end case 1

          case 2:
          {
            //getting first name
            cout << "Input a First Name: \n";
            firstName = getword();

            //getting last name
            cout << "Input a Last Name: \n";
            lastName = getword();

            //getting CGPA
            cout << "Input a CGPA: \n";
            CGPA = getfloat();

            //getting research score
            cout << "Input a Research Score: \n";
            score = getint();

            //getting ID
            cout << "Input an ID: \n";
            ID = getint();

            //getting country
            cout << "Input a Province: \n";
            country = getword();

            //creating object
            DomesticStudent newDomesticStudent(firstName, lastName, CGPA, score, ID, country);

            //adding node to list
            domestic_students.AddNode(newDomesticStudent);

            continue;
          }//end case 2

          case 3:
          {
            cout << "Input the index of the node you would like to delete: \n";
            index = getint();

            deleteNode <DSLinkedList, DomesticStudent>(domestic_students, index);
            continue;
          }//end case 3

          case 4:
          {
            domestic_students.RemoveHead();
            domestic_students.RemoveTail();
            continue;
          }//end case 4

          case 5:
          {
            domestic_students.print();
            continue;
          }//end case 5

          default:
          {
            cout << "Invalid Input, enter a number between 0 and 5\nPress enter to continue: ";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
          }//end default
        }//end userInput 2
        continue;
      }//end case 1

      case 2:
      {
        cout << "\n\nWhat would you like to do?\n";
        cout << "[1] Search through existing International Student List\n";
        cout << "[2] Create a new International Student Node\n";
        cout << "[3] Delete existing International Student Node\n";
        cout << "[4] Delete head and tail node from the existing International Student List\n";
        cout << "[5] View full list\n";
        cout << "[0] Enter 0 to exit the program\n";
        
        userInput2 = getint();

        switch (userInput2)
        {
          case 0:
          {
            cout << "\n\nExiting Program\n";
            open = false;
            continue;
          }//end case 0

          case 1:
          {
            cout << "\n\nHow would you like to search the International Student List?\n";
            cout << "[1] Application ID\n";
            cout << "[2] CGPA\n";
            cout << "[3] Research Score\n";
            cout << "[4] First and Last Name\n";

            userInput3 = getint();

            switch (userInput3)
            {
              case 1:
              {
                cout << "Input an ID:\n";
                userInputID = getint();
                SearchID <ISLinkedList, InternationalStudent> (intern_students, userInputID);
                continue;
              }//end case 1

              case 2:
              {
                cout << "Input a CGPA:\n";
                userInputCGPA = getdouble();
                SearchCGPA <ISLinkedList, InternationalStudent> (intern_students, userInputCGPA);
                continue;
              }//end case 2

              case 3:
              {
                cout << "Input a Research Score:\n";
                userInputScore = getfloat();
                SearchScore <ISLinkedList, InternationalStudent> (intern_students, userInputScore);
                continue;
              }//end case 3

              case 4:
              {
                cout << "Input a name: [FirstNameLastName]\n";
                userInputName = getword();

                cout << "Would you like to remove this student from the list?(Y/N)\n";
                getline(cin, userInputRemove_s);
                while (cin.fail() || cin.eof() || userInputRemove_s.find_first_not_of("YNyn") != string::npos || userInputRemove_s.empty())
                {
                  cout << "\nError, invalid input\nPlease enter a Y or N: ";

                  if (userInputRemove_s.find_first_not_of("YN") == string::npos) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                  }

                  getline(std::cin, userInputRemove_s);
                }
                userInputRemove_c = userInputRemove_s[0];
                if (userInputRemove_c == 'Y'){
                  remove = true;
                }else if (userInputRemove_c == 'N'){
                  remove = false;
                }
                SearchName <ISLinkedList, InternationalStudent> (intern_students, userInputName, remove);
                continue;
              }//end case 4

              default:
              {
                cout << "\nError, please enter a number between 1 and 4\nPlease press enter to continue: ";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
              }
            }//end userInput 3
            continue;
          }//end case 1

          case 2:
          {
            //getting first name
            cout << "Input a First Name: \n";
            firstName = getword();

            //getting last name
            cout << "Input a Last Name: \n";
            lastName = getword();

            //getting CGPA
            cout << "Input a CGPA: \n";
            CGPA = getfloat();

            //getting research score
            cout << "Input a Research Score: \n";
            score = getint();

            //getting ID
            cout << "Input an ID: \n";
            ID = getint();

            //getting country
            InputCountry_:
            cout << "Input a Country: \n";
            country = getword();

            string temp_country;
            bool error = 0;
            int _index = -1;
            int Unknown = Spell::spellingMistakeCountry(country, error, _index);
            if (error) {
                if (Unknown == 4) {
                    cout << "\nUnknown Country was inputted, which could not be spell corrected."
                        << "Please either input: Canada, China, India, Iran, or Korea\n\n";
                    goto InputCountry_;
                }
                else
                {
                    switch (_index)
                    {
                    case 0:
                        temp_country = "Canada";
                        break;
                    case 1:
                        temp_country = "China";
                        break;
                    case 2:
                        temp_country = "India";
                        break;
                    case 3:
                        temp_country = "Iran";
                        break;
                    case 4:
                        temp_country = "Korea";
                        break;
                    }
                    cout << "Spelling mistake detected: " << country << " was changed to " << temp_country << endl;
                    country = temp_country;
                }
            }


            //getting reading score
            cout << "Input a Reading Score: \n";
            reading = getint();

            //getting listening score
            cout << "Input a Listening Score: \n";
            listening = getint();

            //getting speaking score
            cout << "Input a Speaking Score: \n";
            speaking = getint();

            //getting writing score
            cout << "Input a Writing Score: \n";
            writing = getint();

            //creating object
            InternationalStudent newInternationalStudent(firstName, lastName, CGPA, score, ID, country, reading, listening, speaking, writing);

            //adding node to list
            intern_students.AddNode(newInternationalStudent);
            continue;
          }//end case 2

          case 3:
          {
            cout << "Input the index of the node you would like to delete: \n";
            index = getint();

            deleteNode <ISLinkedList, InternationalStudent>(intern_students, index);
            continue;
          }//end case 3

          case 4:
          {
            intern_students.RemoveHead();
            intern_students.RemoveTail();
            continue;
          }//end case 4

          case 5:
          {
            intern_students.print();
            continue;
          }//end case 5

          default:
          {
            cout << "\nError, please enter a number between 0 and 5\nPress enter to continue: \n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
          }
        }

      }//end case 2

      case 3:
      {
        //merging the two lists into one
        SLinkedList mergedList(domestic_students, intern_students);
        cout << "\n\nWhat would you like to do with this new merged list: \n";
        cout << "[1] Filter with CGPA\n";
        cout << "[2] Filter with Research Score\n";
        cout << "[3] View full list\n";

        userInput3 = getint();

        switch (userInput3)
        {
          case 1:
          {
            cout << "Input a CGPA: \n";
            cgpa_threshold = getfloat();

            FilterCGPA<SLinkedList, Student>(mergedList, cgpa_threshold);
            continue;
          }//end case 1

          case 2:
          {
            cout << "Input a Research Score: \n";
            researchScore_threshold = getint();

            FilterScore<SLinkedList, Student>(mergedList, researchScore_threshold);
            continue;
          }//end case 2

          case 3:
          {
            mergedList.print();
            continue;
          }//end case 3

          default:
          {
            cout << "\nError, please enter a number between 1 and 3\nPress enter to continue: \n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
          }//end default

        }//end userInput3
        continue;
      }//end case 3

      case 4:
      {
        call_all_tests();
      }//end case 4

      default:
      {
        cout << "\nError, please enter a number between 0 and 3\nPress enter to continue: \n";
        cin.clear();
        cin.ignore(1000, '\n');
        continue;
      }//end default case for first menu
    }//end user input 1
  }//end while(open) loop 
  return 0;
}

int main()
{
  menu();
  //call_all_tests();
  return 0;
}

//helper function to ensure that the user input is an integer
int getint(){
  string s;
  getline(cin, s);
  while (cin.fail() || cin.eof() || s.find_first_not_of("0123456789") != string::npos || s.empty())
  {
    cout << "\nError, invalid input\nPlease enter a number: ";

    if (s.find_first_not_of("0123456789") == string::npos) {
      cin.clear();
      cin.ignore(1000, '\n');
    }

    getline(cin, s);
  }

  string::size_type st;
  return stoi(s, &st);
}

//helper function to ensure that the user input is a number
double getdouble()
{
  string s;
  getline(cin, s);
  while (cin.fail() || cin.eof() || s.find_first_not_of("0123456789.") != string::npos || s.empty())
  {
    cout << "\nError, invalid input\nPlease enter a number: ";

    if (s.find_first_not_of("0123456789.") == string::npos) {
      cin.clear();
      cin.ignore(1000, '\n');
    }

    getline(cin, s);
  }

  string::size_type st;
  return stod(s, &st);
}

//helper function to ensure that the user input is a number
float getfloat()
{
  string s;
  getline(cin, s);
  while (cin.fail() || cin.eof() || s.find_first_not_of("0123456789.") != string::npos || s.empty())
  {
    cout << "\nError, invalid input\nPlease enter a number: ";

    if (s.find_first_not_of("0123456789.") == string::npos) {
      cin.clear();
      cin.ignore(1000, '\n');
    }

    getline(cin, s);
  }

  string::size_type st;
  return stof(s, &st);
}

//helper function to ensure that the user input is a word with no other symbols
string getword()
{
  string s;
  getline(cin, s);
  while (cin.fail() || cin.eof() || s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos || s.empty())
  {
    cout << "\nerror, invalid input\nPlease enter only letters: ";

    if (s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") == string::npos) {
      cin.clear();
      cin.ignore(1000, '\n');
    }

    getline(cin, s);
  }

  return s;
}