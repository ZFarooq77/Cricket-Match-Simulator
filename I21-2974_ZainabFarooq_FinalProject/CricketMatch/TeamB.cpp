#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include "HeaderB.h"
using namespace std;

string ** showTeamB(){

string **ptrB = new string *[11];

	for (int i = 0; i < 11; i++)
	{
		ptrB[i] = new string [2];
	}		

	 ptrB [0][0] = "Player 1";  ptrB [0][1] = "Batsman"; 
	 ptrB [1][0] = "Player 2";  ptrB [1][1]="Batsman";
	 ptrB [2][0]= "Player 3";  ptrB [2][1]= "Batsman";

	 ptrB [3][0]= "Player 4";  ptrB [3][1]="Batsman";
	 ptrB [4][0]= "Player 5";  ptrB [4][1]="Batsman";
	 ptrB [5][0]= "Player 6";  ptrB [5][1]= "WicketKeeper";

	 ptrB [6][0]= "Player 7";  ptrB [6][1]="Bowler";
	 ptrB [7][0]= "Player 8";  ptrB [7][1]="Bowler";
	 ptrB [8][0]= "Player 9";  ptrB [8][1]="Bowler";
	 ptrB [9][0]= "Player 10";  ptrB [9][1]="Bowler";
	 ptrB [10][0]= "Player 11";  ptrB [10][1]="Bowler";
	 	 
		
	return ptrB;	
}











