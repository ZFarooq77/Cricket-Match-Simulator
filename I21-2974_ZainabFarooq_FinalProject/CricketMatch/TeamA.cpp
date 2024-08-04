#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include "HeaderA.h"

using namespace std;


string ** showTeamA(){
	
	static string **ptrA = new string *[11];

	for (int i = 0; i < 11; i++)
	{
		ptrA[i] = new string [3];
	}	
																				
	ptrA[0][0] = "Player 1";		ptrA[0][1] = "Batsman";			ptrA[0][2] = "Did_Not_Bat ";
	ptrA[1][0] = "Player 2";		ptrA[1][1] = "Batsman";			ptrA[1][2] = "Did_Not_Bat ";
	ptrA[2][0] = "Player 3";		ptrA[2][1] = "Batsman";			ptrA[2][2] = "Did_Not_Bat ";

	 ptrA [3][0]= "Player 4";		ptrA [3][1]="Batsman";			ptrA[3][2] = "Did_Not_Bat ";
	 ptrA [4][0]= "Player 5";		ptrA [4][1]="Batsman";			ptrA[4][2] = "Did_Not_Bat ";
	 ptrA [5][0]= "Player 6";		ptrA [5][1]= "WicketKeeper";	ptrA[5][2] = "Did_Not_Bat ";

	 ptrA [6][0]= "Player 7";		ptrA [6][1]="Bowler";			ptrA[6][2] = "Did_Not_Bat ";
	 ptrA [7][0]= "Player 8";		ptrA [7][1]="Bowler";			ptrA[7][2] = "Did_Not_Bat ";
	 ptrA [8][0]= "Player 9";		ptrA [8][1]="Bowler";			ptrA[8][2] = "Did_Not_Bat ";
	 ptrA [9][0]= "Player 10";		ptrA [9][1]="Bowler";			ptrA[9][2] = "Did_Not_Bat ";
	 ptrA [10][0]= "Player 11";	ptrA [10][1]="Bowler";			ptrA[10][2] = "Did_Not_Bat ";

	return ptrA;
}
