#ifndef DECLENSIONOFINTEGERS_H
#define DECLENSIONOFINTEGERS_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class DeclensionOfIntegers 
{
private:
    inline static const vector<string> сZero {"нуль", "нуля", "нулю", "нуль", "нулём", "нуле"};

    inline static const vector<vector<string>> gcOne {{"один", "одна", "одно"},
                                                      {"одного", "одной", "одного"},
                                                      {"одному", "одной", "одному"},
                                                      {"один", "одну", "один"},
                                                      {"одним", "одной", "одной"},
                                                      {"одном", "одной", "одном"}};

    inline static const vector<vector<string>> gcTwo {{"два", "две", "два"},
                                                      {"двух", "двух", "двух"},
                                                      {"двум", "двум", "двум"},
                                                      {"два", "две", "два"},
                                                      {"двумя", "двумя", "двумя"},
                                                      {"двух", "двух", "двух"}};

    inline static const vector<string> сThree {"три", "трёх", "трём", "три", "тремя", "трёх"};

    inline static const vector<string> сFour {"четыре", "четырёх", "четырём", "четыре", "четырьмя", "четырёх"};

    inline static const vector<string> rootsNumbers {"нуль", "один", "дв", "тр", "четыр", "пять",
                                                     "шесть", "семь", "восемь", "девять", "деcять"};

    inline static const string prefixOfDecimals = "на";
    inline static const string rootOfDecimals = "дцать";

    inline static const vector<vector<vector<string>>> ctThousand {{{"а",""},    {"и",""},     {"",""}},  //падеж, окончание, десяток
                                                                   {{"и",""},    {"",""},      {"",""}},
                                                                   {{"е","ам"},  {"ам","ам"},  {"ам","ам"}},
                                                                   {{"у",""},    {"и",""},     {"",""}},
                                                                   {{"ей","ами"},{"ами","ами"},{"ами","ами"}},
                                                                   {{"е","ах"},  {"ах","ах"},  {"ах","ах"}}};

    inline static const vector<vector<vector<string>>> ctMBillion {{{"","ов"},   {"а","ов"},   {"ов","ов"}},
                                                                   {{"а","ов"},  {"ов","ов"},  {"ов","ов"}},
                                                                   {{"у","ам"},  {"ам","ам"},  {"ам","ам"}},
                                                                   {{"","ов"},   {"а","ов"},   {"ов","ов"}},
                                                                   {{"ом","ами"},{"ами","ами"},{"ами","ами"}},
                                                                   {{"е","ах"},  {"ах","ах"},  {"ах","ах"}}};

    static vector<int> getFork(long long &number, string &sGender, string &sCase); //case-gender

    static vector<vector<int>> getNumbers(long long &number);

    static vector<string> analyzeLayer(vector<int> layer, int &layerNumber, vector<int> &fork);

    static string easy(int &number, int &layerNumber, vector<int> &fork);
    static vector<string> decade(vector<int> &layer, int &layerNumber, vector<int> &fork);
    static vector<string> century(vector<int> &layer, int &layerNumber, vector<int> &fork);

    static string makeEasyDecWordFromRoot(int &number);

    static string analyzeDecade(int &decade, int &layerNumber, vector<int> &fork);
    static string analyzeCentury(int &century, int &layerNumber, vector<int> &fork);

    static string declFiveAndOther(string &rootW, vector<int> &fork);
    static string declDecade(string &rootW, vector<int> &fork);
    static string declCentury1(string &rootW, vector<int> &fork);
    static string declCentury2(string &rootW, vector<int> &fork);

    static string layersWord(vector<int> &layer, int &layerNumber, vector<int> &fork);

public:
    explicit DeclensionOfIntegers();
    virtual ~DeclensionOfIntegers();

    static const long long maxNumber = 1000000000000;

    inline static const vector<string> genders {"М", "Ж", "С"};
    inline static const vector<string> cases {"И", "Р", "Д", "В", "Т", "П"};

    static string declInts(long long number, string sGender, string sCase);
};

#endif // DECLENSIONOFINTEGERS_H
