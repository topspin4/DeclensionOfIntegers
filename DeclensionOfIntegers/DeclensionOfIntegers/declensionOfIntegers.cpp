#include "declensionOfIntegers.h"

DeclensionOfIntegers::DeclensionOfIntegers()
{

}

DeclensionOfIntegers::~DeclensionOfIntegers()
{
    
}

string DeclensionOfIntegers::declInts(long long number, string sGender, string sCase) // 3 2 1 0 - слои
{
    string result = "";

    vector<int> fork = getFork(number, sGender, sCase);

    if (fork[0] == -1 || fork[1] == -1)
    {
        return "err";
    }
    else
    {
        vector<vector<int>> layers = getNumbers(number);
        vector<vector<string>> sLayers;

        int layerNumber;

        for (int layer = 0; layer < layers.size(); layer++)
        {
            sLayers.insert(sLayers.begin(), analyzeLayer(layers[layer], layer, fork));
        }

        reverse(layers.begin(), layers.end());

        for (int layer = 0; layer < sLayers.size(); layer++)
        {
            layerNumber = sLayers.size() - 1 - layer;

            for (int word = 0; word < sLayers[layer].size(); word++)
            {
                result += sLayers[layer][word];

                if (word != sLayers[layer].size() - 1)
                {
                    result += " ";
                }
                else
                {
                    result += " " + layersWord(layers[layer], layerNumber, fork) + " ";
                }
            }
        }
    }

    return result;
}

vector<int> DeclensionOfIntegers::getFork(long long &number, string &sGender, string &sCase)
{
    vector<int> result;

    if (number < maxNumber)
    {
        bool finded = false;

        for (int i = 0; i < cases.size(); i++)
        {
            if (sCase == cases[i])
            {
                result.push_back(i);

                finded = true;

                break;
            }
        }

        if (!finded)
        {
            result.push_back(int(-1));
        }
        else
        {
            finded = false;
        }

        for (int i = 0; i < genders.size(); i++)
        {
            if (sGender == genders[i])
            {
                result.push_back(i);

                finded = true;

                break;
            }
        }

        if (!finded)
        {
            result.push_back(int(-1));
        }
    }
    else
    {
        result.push_back(int(-1));
        result.push_back(int(-1));
    }

    return result;
}

vector<vector<int>> DeclensionOfIntegers::getNumbers(long long &number)
{
    vector<vector<int>> result;

    string num = to_string(number);

    vector<int> v;
    int layerCounter = 0;

    for (int i = num.size() - 1; i >= 0; i--)
    {
        if (layerCounter == 3)
        {
            result.push_back(v);

            layerCounter = 0;
            v.clear();
        }

        layerCounter++;
        v.push_back((int)(num[i] - '0'));
    }

    if (v.size() != 0)
    {
        result.push_back(v);
    }

    return result;
}

vector<string> DeclensionOfIntegers::analyzeLayer(vector<int> layer, int &layerNumber, vector<int> &fork)
{
    vector<string> result;

    switch (layer.size())
    {
        case 1:
        {
            if (layer[0] != 0)
            {
                result.push_back(easy(layer[0], layerNumber, fork));
            }
            else
            {
                result.push_back(сZero[fork[0]]);
            }
        }
        break;

        case 2:
        {
            if (layer[1] != 0)
            {
                result = decade(layer, layerNumber, fork);
            }
            else
            {
                if (layer[0] != 0)
                {
                    result.push_back(easy(layer[0], layerNumber, fork));
                }
            }
        }
        break;

        case 3:
        {
            if (layer[2] != 0)
            {
                result = century(layer, layerNumber, fork);
            }
            else
            {
                if (layer[1] != 0)
                {
                    result = decade(layer, layerNumber, fork);
                }
                else
                {
                    if (layer[0] != 0)
                    {
                        result.push_back(easy(layer[0], layerNumber, fork));
                    }
                }
            }
        }
        break;
    }

    return result;
}

string DeclensionOfIntegers::easy(int &number, int &layerNumber, vector<int> &fork)
{
    string result = "";

    if (number == 1 || number == 2)
    {
        int genderNumber = fork[1];

        if (layerNumber == 1)
        {
            genderNumber = 1;
        }
        else if (layerNumber > 1)
        {
            genderNumber = 0;
        }

        if (number == 1)
        {
            result = gcOne[fork[0]][genderNumber];
        }
        else if (number == 2)
        {
            result = gcTwo[fork[0]][genderNumber];
        }
    }

    else if (number > 2 && number < 5)
    {
        if (number == 3)
        {
            result = сThree[fork[0]];
        }
        else if (number == 4)
        {
            result = сFour[fork[0]];
        }
    }

    else if ( (number >= 5 && number < 21) || number == 30)
    {
        string rootW = "";

        if (number < 11)
        {
            rootW = rootsNumbers[number];

            result = declFiveAndOther(rootW, fork);
        }
        else if (number > 10)
        {
            rootW = makeEasyDecWordFromRoot(number);

            result = declFiveAndOther(rootW, fork);
        }
    }

    return result;
}

vector<string> DeclensionOfIntegers::decade(vector<int> &layer, int &layerNumber, vector<int> &fork)
{
    vector<string> result;

    if (layer[1] == 1)
    {
        int number = 0;
        stringstream ss;

        ss << layer[1] << layer[0] ;
        ss >> number;

        result.push_back(easy(number, layerNumber, fork));
    }
    else
    {
        result.push_back(analyzeDecade(layer[1], layerNumber, fork));

        if (layer[0] != 0)
        {
            result.push_back(easy(layer[0], layerNumber, fork));
        }
    }

    return result;
}

vector<string> DeclensionOfIntegers::century(vector<int> &layer, int &layerNumber, vector<int> &fork)
{
    vector<string> result;

    result.push_back(analyzeCentury(layer[2], layerNumber, fork));

    if (layer[1] != 0)
    {
        vector<string> resultDecade = decade(layer, layerNumber, fork);

        for (int i = 0; i < resultDecade.size(); i++)
        {
            result.push_back(resultDecade[i]);
        }
    }
    else
    {
        if (layer[0] != 0)
        {
            result.push_back(easy(layer[0], layerNumber, fork));
        }
    }

    return result;
}

string DeclensionOfIntegers::makeEasyDecWordFromRoot(int &number)
{
    string word = "";

    if (number == 20 || number == 30)
    {
        if (number == 20)
        {
            word = rootsNumbers[2];
            word += "а";
        }
        else
        {
            word = rootsNumbers[3];
            word += "и";
        }

        word += rootOfDecimals;
    }
    else
    {
        word = rootsNumbers[number - 10];

        if (number == 12 || number == 13)
        {
            if (number == 12)
            {
                word += "е";
            }
            else
            {
                word += "и";
            }
        }

        word += prefixOfDecimals;
        word += rootOfDecimals;
    }

    return word;
}

string DeclensionOfIntegers::analyzeDecade(int &decade, int &layerNumber, vector<int> &fork)
{
    string rootW = "";

    int number;

    if (decade == 2)
    {
        number = 20;

        return easy(number, layerNumber, fork);
    }
    else if (decade == 3)
    {
        number = 30;

        return easy(number, layerNumber, fork);
    }
    else if (decade == 4)
    {
        rootW = "сорок";
    }
    else if (decade == 9)
    {
        rootW = "девяносто";
    }
    else if ( (decade > 4 && decade < 9) )
    {
        rootW = rootsNumbers[decade];
    }

    return declDecade(rootW, fork);
}

string DeclensionOfIntegers::analyzeCentury(int &century, int &layerNumber, vector<int> &fork)
{
    string rootW = "";

    if (century == 1)
    {
        rootW = "сто";

        return declDecade(rootW, fork);
    }
    else if (century > 1 && century < 5)
    {
        if (century == 2)
        {
            rootW = gcTwo[fork[0]][1]; //1 - т.к. двойка нужна в Ж роде
        }
        else if (century == 3)
        {
            rootW = сThree[fork[0]];
        }
        else if (century == 4)
        {
            rootW = сFour[fork[0]];
        }

        return declCentury1(rootW, fork);
    }
    else if (century > 4 && century <= 9)
    {
        rootW = rootsNumbers[century];

        rootW = declFiveAndOther(rootW, fork);

        return declCentury2(rootW, fork);
    }
}

string DeclensionOfIntegers::declFiveAndOther(string &rootW, vector<int> &fork)
{
    if (fork[0] == 1 || fork[0] == 2 || fork[0] == 5)
    {
        if (rootW != "восемь")
        {
            rootW.pop_back(); rootW.pop_back(); //т.к. одна буква - 2 байта
            rootW += "и";
        }
        else
        {
            rootW = "восьми";
        }
    }
    else if (fork[0] == 4)
    {
        if (rootW == "восемь")
        {
            rootW = "восьмью";
        }
        else
        {
            rootW += "ю";
        }
    }
    else if (rootW == rootsNumbers[10])
    {
        rootW.pop_back(); rootW.pop_back();
    }

    return rootW;
}

string DeclensionOfIntegers::declDecade(string &rootW, vector<int> &fork)
{
    if (find(rootsNumbers.begin(), rootsNumbers.end(), rootW) != rootsNumbers.end())
    {
        string ten = rootsNumbers[10];

        rootW = declFiveAndOther(rootW, fork);
        rootW += declFiveAndOther(ten, fork); //Приклеиваем склонённую десятку
    }
    else
    {
        if (fork[0] != 0 && fork[0] != 3)
        {
            if (rootW == "сорок")
            {
                rootW += "а";
            }
            else
            {
                rootW.pop_back(); rootW.pop_back();
                rootW += "а";
            }
        }
    }

    return rootW;
}

string DeclensionOfIntegers::declCentury1(string &rootW, vector<int> &fork)
{
    string result = "";

    if (fork[0] == 0 || fork[0] == 3 )
    {
        if (rootW == "две")
        {
            rootW += "сти";
        }
        else
        {
            rootW += "ста";
        }
    }
    else if (fork[0] == 1)
    {
        rootW += "сот";
    }
    else if (fork[0] == 2)
    {
        rootW += "стам";
    }
    else if (fork[0] == 4)
    {
        rootW += "стами";
    }
    else if (fork[0] == 5)
    {
        rootW += "стах";
    }

    result = rootW;

    return result;
}

string DeclensionOfIntegers::declCentury2(string &rootW, vector<int> &fork)
{
    string result = "";

    if (fork[0] == 0 || fork[0] == 1 || fork[0] == 3 )
    {
        rootW += "сот";
    }
    else if (fork[0] == 2)
    {
        rootW += "стам";
    }
    else if (fork[0] == 4)
    {
        rootW += "стами";
    }
    else if (fork[0] == 5)
    {
        rootW += "стах";
    }

    result = rootW;

    return result;
}

string DeclensionOfIntegers::layersWord(vector<int> &layer, int &layerNumber, vector<int> &fork)
{
    string result = "";

    if (layerNumber == 1)
    {
        result = "тысяч";

        if (layer[0] == 1)
        {
            if (layer.size() > 1)
            {
                if (layer[1] == 1)
                {
                    result += ctThousand[fork[0]][0][1];
                }
                else
                {
                    result += ctThousand[fork[0]][0][0];
                }
            }
            else
            {
                result += ctThousand[fork[0]][0][0];
            }
        }
        else if (layer[0] > 1 && layer[0] < 5)
        {
            if (layer.size() > 1)
            {
                if (layer[1] == 1)
                {
                    result += ctThousand[fork[0]][1][1];
                }
                else
                {
                    result += ctThousand[fork[0]][1][0];
                }
            }
            else
            {
                result += ctThousand[fork[0]][1][0];
            }
        }
        else
        {
            if (layer.size() > 1)
            {
                if (layer[1] == 1)
                {
                    result += ctThousand[fork[0]][2][1];
                }
                else
                {
                    result += ctThousand[fork[0]][2][0];
                }
            }
            else
            {
                result += ctThousand[fork[0]][2][0];
            }
        }
    }
    else if (layerNumber != 0)
    {
        if (layerNumber == 2)
        {
            result = "миллион";
        }
        else if (layerNumber == 3)
        {
            result = "миллиард";
        }

        if (layer[0] == 1)
        {
            if (layer.size() > 1)
            {
                if (layer[1] == 1)
                {
                    result += ctMBillion[fork[0]][0][1];
                }
                else
                {
                    result += ctMBillion[fork[0]][0][0];
                }
            }
            else
            {
                result += ctMBillion[fork[0]][0][0];
            }
        }
        else if (layer[0] > 1 && layer[0] < 5)
        {
            if (layer.size() > 1)
            {
                if (layer[1] == 1)
                {
                    result += ctMBillion[fork[0]][1][1];
                }
                else
                {
                    result += ctMBillion[fork[0]][1][0];
                }
            }
            else
            {
                result += ctMBillion[fork[0]][1][0];
            }
        }
        else
        {
            if (layer.size() > 1)
            {
                if (layer[1] == 1)
                {
                    result += ctMBillion[fork[0]][2][1];
                }
                else
                {
                    result += ctMBillion[fork[0]][2][0];
                }
            }
            else
            {
                result += ctMBillion[fork[0]][2][0];
            }
        }
    }

    return result;
}
