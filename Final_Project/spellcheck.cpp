#include "spellcheck.hpp"
#include "student.hpp"
#include <algorithm> //used for spellcheck only

char Alphabet[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
extern string Countries[5];
extern string Provinces[13];

//function that checks if a string is an anagram
bool Spell::isAnagram(string country1, string country2)
{
  //first check if length is the same
	if (country1.length() != country2.length()) {
		return false;
	}

  //sort the countries for comparison
	std::sort(country1.begin(), country1.end());
	std::sort(country2.begin(), country2.end());

  //check if each character is the same
	for (int j = 0; j < country1.length(); j++)
		if (country1[j] != country2[j])
		{

			return false; //if they're different, return false
		}
	return true;  //else return true
}

//Function used for inputting unaltered input into the anagram function
int Spell::rawInputCountry(string inCountry, bool& value)
{
	bool check = false;
	for (int i = 0; i < 5; i++)
	{
		check = isAnagram(inCountry, Countries[i]);
		if (check == true)
		{
			value = true;
			return i;
		}
	}
  return 0;
}

//Function that checks if there was an extra character in the input
int Spell::extraInputCountry(string str, bool& value)
{
	int length = str.size();
	string shortened;
	bool temp = 0;

	for (int i = 0; i < length; i++)
	{
		shortened = str;
		shortened.erase(shortened.begin() + i);
		int x = rawInputCountry(shortened, temp);
		if (temp == true)
		{
			value = true;
			return x;
		}
	}
}

//Function that checks if there was a missing character in the input
int Spell::missingInputCountry(string str, bool& value)
{
	bool temp = 0;
	string lengthened;

	for (int i = 0; i < 26; i++)
	{
		lengthened = str;
		lengthened.push_back(Alphabet[i]);	//adds new character to every input
		int x = rawInputCountry(lengthened, temp);
		if (temp == true)
		{
			value = true;
			return x;
		}
	}
	return 0;
}

//call this function to determine if there was a spelling mistake, and get a suggested spelling correction
//Input string should be a country name, either Canada, India, Iran, Korea or China
//Error returns 1 if there was a spelling error, returns 0 if input has no errors
//Index returns the index of the suggested country, where:
//0 == Canada
//1 == China
//2 == India
//3 == Iran
//4 == Korea
int Spell::spellingMistakeCountry(string str, bool& Error, int& index)
{
	to_lowercase(str);
	bool check = false;
	index = 0;
	int error = false;

	//1 first check if strings are the same
	for (int i = 0; i < 5; i++)
	{
		if (!(str.compare(Countries[i])))
		{
			Error = false;
			return 0;
		}
	}
	Error = true;
	//Check if strings are same but in wrong order
	index = rawInputCountry(str, check);
	if (check)
	{
		return 1;
	}
	//Check if missing input
	index = missingInputCountry(str, check);
	if (check)
	{
		return 2;
	}

	//Check if extra input
	index = extraInputCountry(str, check);
	if (check)
	{
		return 3;
	}
	return 4;
}
