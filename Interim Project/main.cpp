//main.cpp, put your driver code here,
//you can manipulate your class objects here

#include <iostream> //cin and cout
#include <fstream>  //file processing
#include <sstream>  //formatted string processing
#include <cstdlib>  //atof and atoi
#include <vector>
#include "student.hpp"
#include "stu_sort.hpp"

void print_stu_vect(vector<DomesticStudent> in_vec);
void print_stu_vect(vector<InternationalStudent> in_vec);

string ASCII_ART = " __          __  ______   _         _____    ____    __  __   ______     _ \n \\ \\        / / |  ____| | |       / ____|  / __ \\  |  \\/  | |  ____|   | |\n  \\ \\  /\\  / /  | |__    | |      | |      | |  | | | \\  / | | |__      | |\n   \\ \\/  \\/ /   |  __|   | |      | |      | |  | | | |\\/| | |  __|     | |\n    \\  /\\  /    | |____  | |____  | |____  | |__| | | |  | | | |____    |_|\n     \\/  \\/     |______| |______|  \\_____|  \\____/  |_|  |_| |______|   (_)\n                                                                           \n";


int main()
{
  vector<DomesticStudent> domestic_students;
  vector<InternationalStudent> intern_students;
  //Read the domestic-stu.txt file and exit if failed

  string line;
  ifstream domesticFile("domestic-stu.txt");
  if (!domesticFile.is_open())
  {
    cout << "Unable to open file domestic-stu.txt" << endl;
    return -1;
  }

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
    getline(ss, s_researchScore, ',');
    researchScore = atoi(s_researchScore.c_str());

    int temp_id = 20210000 + stu_count;

    DomesticStudent temp_student(firstName, lastName, cgpa, researchScore, temp_id, province);

    domestic_students.push_back(temp_student);

    stu_count++;
  }

  domesticFile.close();

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

    string firstName, lastName, country, s_cgpa, s_researchScore, s_r, s_l, s_s, s_w;
    float cgpa;
    int researchScore;
    int r, l, s, w;

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

    getline(ss, s_w, ',');
    w = atoi(s_w.c_str());

    int temp_id = 20210000 + stu_count; //creates unique student # for each student

    InternationalStudent temp_student(firstName, lastName, cgpa, researchScore, temp_id, country, r, l, s, w); //creates new student

    intern_students.push_back(temp_student);  //put new students into a vector

    stu_count++;
  }
  InternationalFile.close();          

  cout<< ASCII_ART;
	while (true)
	{
		// User Menu
		int userInput1, userInput2;         //user inputted int values used for switch statement
		string userInput1_s, userInput2_s;  //used to check for concatenated characters to int values

    cout << "\n\n\n------------------------\n";
		cout << "Please enter your choice\nWould you like to sort and view\n";
		cout << "[1] the Domestic students\n";
		cout << "OR\n";
		cout << "[2] the International students \n";
    cout << "[0] Alternatively, enter 0 to exit program\n\n";
		cout << "please enter either a 1, 2 or 0: ";

    //user input is inputted into a string, and used to check for characters
		getline(std::cin, userInput1_s);
			while (std::cin.fail() || std::cin.eof() || userInput1_s.find_first_not_of("0123456789") != std::string::npos || userInput1_s.empty()) //check for characters and blanks
			{
				cout << "\nerror, invalid input\nPlease enter a number: ";

				if (userInput1_s.find_first_not_of("0123456789") == string::npos) { //for all integers
					cin.clear();
					cin.ignore(1000, '\n');
				}

				std::getline(std::cin, userInput1_s);
			}

		string::size_type st;
		userInput1 = std::stoi(userInput1_s, &st);  //convert string to integer for use in switch statement


		switch (userInput1) //switch used for first menu
		{

    case 0: //case 0, exit program
    cout << "\n\nExiting Program...\n";
    return 0;

		case 1: //case 1, sort domestic students
		{
      //menu
			cout << "\n\nWhat would you like to do? Sort the domestic students by either their...\n";
			cout << "[1] Option 1: CGPA \n";
			cout << "[2] Option 2: Research Scores   \n";
			cout << "[3] Option 3: First names   \n";
			cout << "[4] Option 4: Last names   \n";
			cout << "[5] Option 5: Do an overall sorting \n";
			cout << "[0] Or exit the program \n";
			cout << "Enter choice: \n";

      //user input is inputted into a string, and used to check for characters
			getline(std::cin, userInput2_s);
			while (std::cin.fail() || std::cin.eof() || userInput2_s.find_first_not_of("0123456789") != std::string::npos || userInput2_s.empty())//check for characters and blanks
			{
				cout << "\nerror, invalid input\nPlease enter a number: ";

				if (userInput2_s.find_first_not_of("0123456789") == string::npos) { //for all integers
					cin.clear();
					cin.ignore(1000, '\n');
				}

				std::getline(std::cin, userInput2_s);
			}
			string::size_type st;
			userInput2 = std::stoi(userInput2_s, &st); //convert string to integer for use in switch statement

			switch (userInput2)
			{
			case 1: //sort by CGPA
				sort_cgpa<DomesticStudent>(domestic_students);
				print_stu_vect(domestic_students);
				break;

			case 2: //sort by Research Score
				sort_score<DomesticStudent>(domestic_students);
				print_stu_vect(domestic_students);
				break;

			case 3: //sort by first names
				sort_firstname<DomesticStudent>(domestic_students);
				print_stu_vect(domestic_students);
				break;

			case 4: //sort by last names
				sort_lastname<DomesticStudent>(domestic_students);
				print_stu_vect(domestic_students);
				break;

			case 5: //sort by overall sorting
				Sort_All(domestic_students);
				print_stu_vect(domestic_students);
				break; //sortAll()

			case 0: //Exist program
				return 0;
				break;

			default: //default holds the invalid entry case
				std::cout << "Invalid Input, enter a number between 0 and 5\nPress enter to continue: " << std::endl;
				cin.clear();                              
        cin.ignore(1000, '\n');
			  break;
			}
			break;
    }

		case 2:   //case 2, sort the international students
		{
      //menu
			cout << "\n\nWhat would you like to do? Sort the international students by either their...\n";
			cout << "[1] Option 1: CGPA \n";
			cout << "[2] Option 2: Research Scores   \n";
			cout << "[3] Option 3: First names   \n";
			cout << "[4] Option 4: Last names   \n";
			cout << "[5] Option 5: Do an overall sorting   \n";
			cout << "[0] Or exit the program \n";
			cout << "Enter choice: \n";
      
      //user input is inputted into a string, and used to check for characters
			getline(std::cin, userInput2_s);
			while (std::cin.fail() || std::cin.eof() || userInput2_s.find_first_not_of("0123456789") != std::string::npos || userInput2_s.empty()) //check for characters and blanks
			{
				cout << "\nerror, invalid input\nPlease enter a number: ";

				if (userInput2_s.find_first_not_of("0123456789") == string::npos) { //for all integers
					cin.clear();
					cin.ignore(1000, '\n');
				}

				std::getline(std::cin, userInput2_s);
			}
			string::size_type st;
			userInput2 = std::stoi(userInput2_s, &st); //convert string to integer for use in switch statement

			vector<InternationalStudent> temp_intern; //temporary vector for use in switch statements

			switch (userInput2)
			{

			case 1: //sort by CGPA
				sort_cgpa<InternationalStudent>(intern_students);
				print_stu_vect(intern_students);
				break;

			case 2: //sort by Research Score
				sort_score<InternationalStudent>(intern_students);
				print_stu_vect(intern_students);
				break;

			case 3: //sort by first names
				sort_firstname<InternationalStudent>(intern_students);
				print_stu_vect(intern_students);
				break;

			case 4: //sort by last names
				sort_lastname<InternationalStudent>(intern_students);
				print_stu_vect(intern_students);
				break;

			case 5: //sort by overall sorting
				temp_intern = Sort_All(intern_students);
				print_stu_vect(temp_intern);
				break; 

			case 0: //exits program
				return 0;
				break;

			default:  //default holds the invalid entry case
			std::cout << "Invalid Input, enter a number between 0 and 5\nPress enter to continue: " << std::endl;
      cin.clear();                              
      cin.ignore(1000, '\n');
			break;
			}
			break;

		}// end case 2

		default:  //if user didn't enter 1,2 or 0 in the first menu
		{
      cout << "\nerror, please enter either 1, 2, or 0\nPress enter to continue: ";
      cin.clear();                              
      cin.ignore(1000, '\n');

		}//end default for first menu
		}//end user input 1
	}//end while loop
} //end main

//function that prints out all of the domestic students info
void print_stu_vect(vector<DomesticStudent> in_vec)
{
  for (auto i : in_vec)
  {
    std::cout << i;
  }
}
//function that prints out all of the international students info
void print_stu_vect(vector<InternationalStudent> in_vec)
{
  for (auto i : in_vec)
  {
    std::cout << i;
  }
}