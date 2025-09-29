#include <iostream>
#include <string>
#include <regex>
#include <ctime>

using namespace std;

class Automobile
{
public:
    Automobile();
    Automobile(string name, string manufacturer, int model_year);
    int modelYear();
    void setModelYear(int model_year);
    string manufacturer();
    void setManufacturer(string manufacturer);
    string name();
    void setName(string name);
    string getDescription();
    int getModelYears();

private:
    int _model_year;
    string _manufacturer;
    string _name;
    bool isValidName(string name);
};


int getCurrentYear()
{
    time_t t = time(nullptr);
    tm *const pTInfo = std::localtime(&t);
    return 1900 + pTInfo->tm_year;
}

int main()
{
    Automobile chevrolet_impala = Automobile("Impala", "Chevrolet", 1957);
    cout << chevrolet_impala.getDescription() << endl;
    cout << chevrolet_impala.getModelYears() << endl;
    return 0;
}


string Automobile::name()
{
    return _name;
}

void Automobile::setName(string name)
{
    if (isValidName(name))
    {
        /* code */
        _name = name;
        return;
    }
}

string Automobile::manufacturer()
{
    return _manufacturer;
}

void Automobile::setManufacturer(string manufacturer)
{
    if (isValidName(manufacturer))
    {
        /* code */
        _manufacturer = manufacturer;
        return;
    }
}

int Automobile::modelYear()
{
    return _model_year;
}

void Automobile::setModelYear(int year)
{
    _model_year = year;
}

Automobile::Automobile(string name, string manufacturer, int model_year)
{
    setName(name);
    setManufacturer(manufacturer);
    setModelYear(model_year);
}

// Test if the given string has anything not in A-Za-z0-9_
bool Automobile::isValidName(string str)
{

    // Make own character set
    regex regx("[@_!#$%^&*()<>?/|}{~:]");

    // Pass the string in regex_search
    // method
    return (regex_search(str, regx) == 0);
}

Automobile::Automobile()
{
    setName("");
    setManufacturer("");
    setModelYear(0);
}

string Automobile::getDescription()
{
    return to_string(this->modelYear()) + " " + this->manufacturer() + " " + this->name();
}

int Automobile::getModelYears()
{
    return getCurrentYear() - this->modelYear();
}