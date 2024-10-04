// Michael Algarin
// mla0060
// project2_Algarin_mla0060_v1.cpp
// Compiler: g++
// Run: ./a.out

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

// Variables

const double  totalRuns = 10000, aHitChance = 100/3, bHitChance = 50;
double  aWins1 = 0, aWins2 = 0, bWins = 0, cWins = 0;
bool A_alive = true, B_alive = true, C_alive = true;

// Methods

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
void test_at_least_two_alive(void);
bool shoot_target(int probability);

int main()
{
	srand(time(0));
	cout << "*** Welcome to Algarin's Duel Simulator ***\n";


// Strategy 1
/* Description of Strategy 1
 *  - In this strategy there is a 33% chance that Aaron shoots Charlie first turn. If that occurs, Bob will have the chance to shoot Aaron, possibly giving Aaron less turns to shoot. Logically for Aaron, strategy two guarantees him shooting after Bob/Charlie shoot. 
 */

	cout << "Ready to test strategy 1 (run 10000 times):\n";
	cout << "Press Enter to continue...";
	cin.ignore().get();

	for(int i = 0; i < totalRuns; i++)
	{
		A_alive = true;
		B_alive = true;
		C_alive = true;
		while(at_least_two_alive(A_alive, B_alive, C_alive))
		{
			// Duel //

			if(A_alive)
				Aaron_shoots1(B_alive, C_alive);
			if(B_alive)
				Bob_shoots(A_alive, C_alive);
			if(C_alive)
				Charlie_shoots(A_alive, B_alive);
		}
		if(A_alive)
			aWins1++;
		if(B_alive)
			bWins++;
		if(C_alive)
			cWins++;
	}

	cout << "Aaron won " << aWins1 << "/10000 duels or " << static_cast<double>(aWins1)/totalRuns*100 << "%\n"
		<< "Bob won " << bWins << "/10000 duels or " << static_cast<double>(bWins)/totalRuns*100 << "%\n"
		<< "Charlie won " << cWins << "/10000 duels or " << static_cast<double>(cWins)/totalRuns*100 << "%\n"
	        << endl;

// Strategy 2 //

/* Description of Strategy 2
 *  - As according to logic, all 3 people - if they hit their shot - will aim and kill the person with the best aim. In Strategy 2, Aaron purposefully misses his first shot in order to let Bob and Charlie fight it out between each other. Either Bob will kill Charlie at a 50% chance, or Charlie will guaranteed kill Bob - neither will aim at Aaron as there is someone with a higher hit chance. Regardless of which person lives between Bob and Charlie, the duel code brings it back to Aaron's turn, relying on only his hit chance and one other person (if it's Bob, then the duel will go until one of them wins, as neither have a perfect hit chance. if it's Charlie, then the duel will end if the turn goes back to Charlie). Regardless, this strategy guarantees that Aaron will have a chance to shoot, before having to worry about dying.
 */	
	cout << "Ready to test strategy 2 (run 10000 times):\n";
	bWins = 0, cWins = 0;
	cout << "Press Enter to continue...";
	cin.ignore().get();

	for(int i = 0; i < totalRuns; i++)
	{
		A_alive = true;
		B_alive = true;
		C_alive = true;

		while(at_least_two_alive(A_alive, B_alive, C_alive))
		{
			if(A_alive)
				Aaron_shoots2(B_alive, C_alive);
			if(B_alive)
				Bob_shoots(A_alive, C_alive);
			if(C_alive)
				Charlie_shoots(A_alive, B_alive);
		}
		if(A_alive)
			aWins2++;
		if(B_alive)
			bWins++;
		if(C_alive)
			cWins++;

	}

	cout << "Aaron won " << aWins2 << "/10000 duels or " << static_cast<double>(aWins2)/totalRuns*100 << "%\n"
                << "Bob won " << bWins << "/10000 duels or " << static_cast<double>(bWins)/totalRuns*100 << "%\n"
                << "Charlie won " << cWins << "/10000 duels or " << static_cast<double>(cWins)/totalRuns*100 << "%\n"
                << endl;

	if(aWins1 > aWins2)
		cout << "Strategy 1 is better than strategy 2.\n";
	else
		cout << "Strategy 2 is better than strategy 1.\n";

	return 0;
}
			
// Implementation //

bool at_least_two_alive(bool aaronAlive, bool bobAlive, bool charlieAlive)
{
	return ((aaronAlive && bobAlive) || (bobAlive && charlieAlive) || (aaronAlive && charlieAlive));
}

void Aaron_shoots1(bool& bobAlive, bool& charlieAlive)
{
	assert(A_alive == true);
	bool hit = shoot_target(aHitChance);
	if (hit && charlieAlive)
       	{
		charlieAlive = false;
		return;
	}
	if (hit && bobAlive)
       	{
		bobAlive = false;
		return;
	}
}

void Bob_shoots(bool& aaronAlive, bool& charlieAlive)
{
	assert(B_alive == true);
	bool hit = shoot_target(bHitChance);
	if (hit && charlieAlive)
       	{
		charlieAlive = false;
		return;
	}
	if (hit && aaronAlive)
       	{
		aaronAlive = false;
		return;
	}
}

void Charlie_shoots(bool& aaronAlive, bool& bobAlive)
{
	assert(C_alive == true);
	if (bobAlive)
       	{
		bobAlive = false;
		return;
	}
	if (aaronAlive)
       	{
		aaronAlive = false;
		return;
	}
}

void Aaron_shoots2(bool& bobAlive, bool& charlieAlive)
{
	bool hit;	
	if (charlieAlive && bobAlive)
	{
		hit = false;
	} 
	else
       	{
		hit = shoot_target(aHitChance);
	}
	if (hit && charlieAlive)
       	{
		charlieAlive = false;
		return;
	}
	if (hit && bobAlive)
       	{
		bobAlive = false;
		return;
	}
}

bool shoot_target(int probability)
{
        int result = rand()%100;
        return result <= probability;
}
