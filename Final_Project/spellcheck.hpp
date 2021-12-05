#ifndef spellcheck_hpp
#define spellcheck_hpp

#include <string> 
#include <ostream>
#include <iomanip>
using namespace std;

class Spell
{
public:

    static int spellingMistakeCountry(string str, bool& Error, int& index);
    static bool isAnagram(string str, string str2);
    static int rawInputCountry(string str, bool& value);
    static int extraInputCountry(string str, bool& value);
    static int missingInputCountry(string str, bool& value);
    //static bool exchangedInputCountry(string str);

};

#endif