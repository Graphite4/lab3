#include "Slav.h"
#include <fstream>
#include <iterator>
#include <time.h>
#include <string>
#include <cstdlib>



using namespace std;

vector <string> Slav::names;
int Slav::_counter = 0;

void Slav::init()
{
	srand(time(NULL));
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

Slav::Slav()
{
	static int amountOfNames = (init(), names.size()); 
	// leniwa inicjalizacja - dzięki static operacja (zimportowanie imion 
	//i przypisanie zmiennej ich liczby) wykona się tylko raz i dopiero
	//wtedy (w ostatnim możliwym momencie), gdy będzie potrzebna (to jest
	//przy tworzeniu pierwszego Słowianina)

	_name = names[rand() % amountOfNames];
	_id = _counter++;
}

string Slav::description()
{
	return string("  ") + _name + " [" + to_string(_id) + "]";
}

Sex Slav::sex()
{
	return ((_name[_name.length()-1]=='a')? female: male);
}