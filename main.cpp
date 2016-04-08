// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);
void sort(Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);
	sort(slavs, n);

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;

	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	srand(time(NULL));
	for (int i=0; i<n; i++)
		vectorOfSlavs.insert((vectorOfSlavs.end()-rand()%(i+1)), (slavs+i));

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze
	vector<Slav *>::iterator x=vectorOfSlavs.begin();
	for (; x!=vectorOfSlavs.end(); x++)
		cout<< (*x)->description() << endl;
	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.
	for(x=vectorOfSlavs.begin(); x!=vectorOfSlavs.end(); x++)
		setOfSlavs.insert(*x);
	vectorOfSlavs.erase(vectorOfSlavs.begin(),vectorOfSlavs.end());
	
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	set<Slav *>::iterator y=setOfSlavs.begin();
	for(;y!=setOfSlavs.end();)
	{
		mapOfSlavs.insert(pair<Slav *,Slav *>(*y,*(y++)));
		setOfSlavs.erase(setOfSlavs.begin(),++y);

	}
	
	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	for(map <Slav *, Slav *>::iterator z=mapOfSlavs.begin();z!=mapOfSlavs.end();z++)
		cout<< (*z).first->description() << " "<<(*z).second->description() <<endl;
	
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	for(int i=0; i<n; i++)
		queueOfSlavs.push((slavs+i));
	
	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.
	for(int i=0; i<n; i++)
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.
	for(int i=0; i<n; i++)
	{
		cout << stackOfSlavs.top()->description() << endl;
		stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;
}

void sort(Slav* slavs, int n)
{
	map < Sex, vector<Slav *>> sortmap;
	for(int i=0; i<n; i++)
		((slavs+i)->sex()==female)?sortmap[female].push_back((slavs+i)):sortmap[male].push_back((slavs+i));
	printf("## sort: women\n");
	for(vector<Slav *>::iterator x=sortmap[female].begin(); x!=sortmap[female].end(); x++)
		cout<<(*x)->description()<<endl;
	printf("## sort: men\n");
	for(vector<Slav *>::iterator x=sortmap[male].begin(); x!=sortmap[male].end(); x++)
		cout<<(*x)->description()<<endl;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}
