#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <stdio.h>
#include<sstream>
#include <chrono>
#include <thread>

#include "HeaderA.h" 
#include "HeaderB.h"

using namespace std;

//Function proptoypes used in this file
void playMatch(char choice_match_start, int totalOvers);
void teamB_Batting(int oversPerBowler_B, std::string** balls_B, std::string** teamB_B, int& ballNumber_B, int totalBalls_B, int& currentBatsmanIndex_BattingEnd_B, int& currentBatsmanIndex_BowlingEnd_B, std::string** teamA_B, std::string  battingScoreCardArrayLeft_B[11][2], int  battingScoreCardArrayRight_B[11][6], std::string  bowlingScoreCardArrayLeft_B[5][1], int  bowlingScoreCardArrayRight_B[11][7], float& oversBowled_B, int& totalScore_B, float& runRate_B, std::string& fallOfWickets_B, std::string& bowlerOfMatch_B, std::string& batsmanOftheMatch_B, std::string& winningTeam_B, std::string& matchSummary_B, int& falledWicket_B, std::string& lastBatsManOut_B, int& batsmanIndex_B, std::string& bowlerName_B, int& bowlerIndex_B, int& bowlerOverNumber_B, int oversToExecuteAtOnce);
void teamABatting(int oversPerBowler_A, std::string** balls_A, std::string** teamB_A, int& ballNumber_A, int totalBalls_A, int& currentBatsmanIndex_BattingEnd_A, int& currentBatsmanIndex_BowlingEnd_A, std::string** teamA_A, std::string  battingScoreCardArrayLeft_A[11][2], int  battingScoreCardArrayRight_A[11][6], std::string  bowlingScoreCardArrayLeft_A[5][1], int  bowlingScoreCardArrayRight_A[11][7], float& oversBowled_A, int& totalScore_A, float& runRate_A, std::string& fallOfWickets_A, std::string& bowlerOfMatch_A, std::string& batsmanOftheMatch_A, std::string& winningTeam_A, std::string& matchSummary_A, int& falledWicket_A, std::string& lastBatsManOut_A, int& batsmanIndex_A, std::string& bowlerName_A, int& bowlerIndex_A, int& bowlerOverNumber_A, int oversToExecuteAtOnce);
bool getToss();

/*
*Calls playMatch()
*/
int main() {

	/*
	* Declaring Variables
	*/
	char choice_match_start = ' ';
	int totalOvers = 0;	
	char char_array[3];
	//load choice_match_start from configuation file here
	fstream myfile;
	myfile.open("Text.txt", ios::in);//read

	// opning ConfigurationFile
	if (myfile.is_open()) 
	{		
		string line;
		string iFile[4] ;
		int counter = 0;
		
		while (!myfile.eof()) 
		{
			getline(myfile, line);
			iFile[counter] = line;
			counter++;		

		}//end while
		
		// copying the contents of the
		// string to char array
		strcpy_s(char_array, iFile[0].c_str());
		choice_match_start = char_array[0];
		totalOvers =  stoi(iFile[1]);

	} //enf if

	cout << "Loading n for new match and d for loading previous match " << endl;
	cout << "Loaded " << choice_match_start << " from configuration file" << endl << endl;
	//cout << choice_match_start << endl;
	cin.get();
	//system("pause");

	//passing choice_match_start to playMatch
	playMatch(choice_match_start, totalOvers);

	return 0;
	} //end main
	
void playMatch(char choice_match_start, int totalOvers) {

	/**************************************************
	* initialing variables and arrays for Team A Batting
	***************************************************/
	int oversPerBowler_A, totalBalls_A; //, j = 1

	//intiatlising balls array
	string** balls_A;
	
	int battingScoreCardArrayRight_A[11][6] = { 0 };
	string battingScoreCardArrayLeft_A[11][2] = { " " }; // not being used
	int bowlingScoreCardArrayRight_A[11][7] = { 0 };
	string bowlingScoreCardArrayLeft_A[5][1] = { " " }; // not being used

	//get TeamA players array
	string** teamA_A = showTeamA();//creates Team A for Batting

	//get TeamB players array
	string** teamB_A = showTeamB();//creates Team B for Bowling

	//Rubrics based parameters
	int ballNumber_A = 0;			//current deliverd ball number
	float oversBowled_A = 0;		//overs bowled so far
	int totalScore_A = 0;			//calculate total score
	float runRate_A = 0;			//current run rate
	string fallOfWickets_A = "";	// current fall of wicket 
	string bowlerOfMatch_A = "";
	string batsmanOftheMatch_A = "";
	string winningTeam_A = "";
	string matchSummary_A = "";
	int falledWicket_A = 0;			//how many wickets falled till now
	string lastBatsManOut_A = "";		// name of Batsman
	int batsmanIndex_A = 0;			//converting string to int		
	string bowlerName_A = "";
	int bowlerIndex_A = 0;
	int bowlerOverNumber_A = 0;

	int currentBatsmanIndex_BattingEnd_A = 0;
	int currentBatsmanIndex_BowlingEnd_A = 1;

	/**************************************************
	* initialing variables and arraysfor Team B Batting
	***************************************************/
	int oversPerBowler_B, totalBalls_B,  oversToExecuteAtOnce = 0;

	//intiatlising balls array
	string** balls_B;

	int battingScoreCardArrayRight_B[11][6] = { 0 };
	string battingScoreCardArrayLeft_B[11][2] = { " " }; // not being used
	int bowlingScoreCardArrayRight_B[11][7] = { 0 };
	string bowlingScoreCardArrayLeft_B[5][1] = { " " }; // not being used

	//get TeamA players array
	string** teamA_B = showTeamA();//creates Team B for Batting 

	//get TeamB players array
	string** teamB_B = showTeamB();//creates Team A for Bowling

	//Rubrics based parameters
	int ballNumber_B = 0;			//current deliverd ball number
	float oversBowled_B = 0;		//overs bowled so far
	int totalScore_B = 0;			//calculate total score
	float runRate_B = 0;			//current run rate
	string fallOfWickets_B = "";	// current fall of wicket 
	string bowlerOfMatch_B = "";
	string batsmanOftheMatch_B = "";
	string winningTeam_B = "";
	string matchSummary_B = "";
	int falledWicket_B = 0;			//how many wickets falled till now
	string lastBatsManOut_B = "";		// name of Batsman
	int batsmanIndex_B = 0;			//converting string to int		
	string bowlerName_B = "";
	int bowlerIndex_B = 0;
	int bowlerOverNumber_B = 0;

	int currentBatsmanIndex_BattingEnd_B = 0;
	int currentBatsmanIndex_BowlingEnd_B = 1;

	/*************************************************************************************/

	/*******************************
	* Deciding action based on Choice
	********************************/

	switch (choice_match_start)
	{

	case ('n'): // New Match

		//get no of overs from user
		cout << "Loading " << totalOvers <<" overs from configuration file (Text.txt) " << endl;
		cout << endl << endl;

		cin.get();

		cout << "Press the over number (e.g., 2) for which you want to continuosly run the program" << endl <<
			"After that progam will run ball by ball" <<endl <<
			"Press 0, If you want the program to run ball by ball, right from the start" << endl << endl;

		cin >> oversToExecuteAtOnce;

		//system("pause");
		/********************************************************/
		//intiatlising balls array for Team A
		// 
		//calculate no of balls and oversPerBowler
		totalBalls_A = totalOvers * 6;
		oversPerBowler_A = totalOvers / 5;

		
		balls_A = new string * [totalBalls_A];
		for (int i = 0; i < totalBalls_A; i++)
		{
			balls_A[i] = new string[10];
		}
		
		/********************************************************/
		// intialising balls array for Team B
		//
		//calculate no of balls and oversPerBowler
		totalBalls_B = totalOvers * 6;
		oversPerBowler_B = totalOvers / 5;

		
		balls_B = new string * [totalBalls_B];
		for (int i = 0; i < totalBalls_B; i++)
		{
			balls_B[i] = new string[10];
		}
		//get toss by random function
		//getToss()
		if (getToss())
		{	
			// Team A Wins the toss
			cout << " **********************************" << endl;
			cout << " Team A  going to start Batting Now" << endl;
			cout << " **********************************" << endl;
			cin.get();
			//system("pause");

			teamABatting(
				oversPerBowler_A, 
				balls_A, 
				teamB_A, 
				ballNumber_A, 
				totalBalls_A, 
				currentBatsmanIndex_BattingEnd_A, 
				currentBatsmanIndex_BowlingEnd_A, 
				teamA_A, 
				battingScoreCardArrayLeft_A, 
				battingScoreCardArrayRight_A, 
				bowlingScoreCardArrayLeft_A, 
				bowlingScoreCardArrayRight_A, 
				oversBowled_A, 
				totalScore_A, 
				runRate_A, 
				fallOfWickets_A, 
				bowlerOfMatch_A, 
				batsmanOftheMatch_A, 
				winningTeam_A, 
				matchSummary_A, 
				falledWicket_A, 
				lastBatsManOut_A, 
				batsmanIndex_A, 
				bowlerName_A, 
				bowlerIndex_A, 
				bowlerOverNumber_A,
				oversToExecuteAtOnce
			);
			system("CLS");
			cout << " **********************************" << endl;
			cout << " Team B  going to start Bowling Now" << endl;
			cout << " **********************************" << endl;
			cin.get();
			//system("pause");
			teamB_Batting(oversPerBowler_B, balls_B, teamB_B, ballNumber_B, totalBalls_B, currentBatsmanIndex_BattingEnd_B, currentBatsmanIndex_BowlingEnd_B, teamA_B, battingScoreCardArrayLeft_B, battingScoreCardArrayRight_B, bowlingScoreCardArrayLeft_B, bowlingScoreCardArrayRight_B, oversBowled_B, totalScore_B, runRate_B, fallOfWickets_B, bowlerOfMatch_B, batsmanOftheMatch_B, winningTeam_B, matchSummary_B, falledWicket_B, lastBatsManOut_B, batsmanIndex_B, bowlerName_B, bowlerIndex_B, bowlerOverNumber_B,  oversToExecuteAtOnce);

		} //if (getToss())

		else {
			//TeamB Wins the Toss
			system("CLS");
			cout << " **********************************" << endl;
			cout << " Team B  going to start Batting Now" << endl;
			cout << " **********************************" << endl;
			cin.get();
			
			cout << "sleeping 5 sec" << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			//system("pause");

			teamB_Batting(oversPerBowler_B, balls_B, teamB_B, ballNumber_B, totalBalls_B, currentBatsmanIndex_BattingEnd_B, currentBatsmanIndex_BowlingEnd_B, teamA_B, battingScoreCardArrayLeft_B, battingScoreCardArrayRight_B, bowlingScoreCardArrayLeft_B, bowlingScoreCardArrayRight_B, oversBowled_B, totalScore_B, runRate_B, fallOfWickets_B, bowlerOfMatch_B, batsmanOftheMatch_B, winningTeam_B, matchSummary_B, falledWicket_B, lastBatsManOut_B, batsmanIndex_B, bowlerName_B, bowlerIndex_B, bowlerOverNumber_B, oversToExecuteAtOnce);
			system("CLS");
			cout << " **********************************" << endl;
			cout << " Team A  going to start Bowling Now" << endl;
			cout << " **********************************" << endl;
			cin.get();
			//system("pause");
			
			teamABatting(
				oversPerBowler_A,
				balls_A,
				teamB_A,
				ballNumber_A,
				totalBalls_A,
				currentBatsmanIndex_BattingEnd_A,
				currentBatsmanIndex_BowlingEnd_A,
				teamA_A,
				battingScoreCardArrayLeft_A,
				battingScoreCardArrayRight_A,
				bowlingScoreCardArrayLeft_A,
				bowlingScoreCardArrayRight_A,
				oversBowled_A,
				totalScore_A,
				runRate_A,
				fallOfWickets_A,
				bowlerOfMatch_A,
				batsmanOftheMatch_A,
				winningTeam_A,
				matchSummary_A,
				falledWicket_A,
				lastBatsManOut_A,
				batsmanIndex_A,
				bowlerName_A,
				bowlerIndex_A,
				bowlerOverNumber_A,
				oversToExecuteAtOnce
			);
		}

		break;
	case ('d'): // Old match to load
		cout << "File loading not implemented please. Sorry for inconvenience..." << endl << endl;
		break;
	default:
		break;
	}//switch (choice_match_start)
	
	 //pause match after match
	cin.get();
	//system("pause");

}			// end play match

void teamB_Batting(int oversPerBowler_B, std::string** balls_B, std::string** teamB_B, int& ballNumber_B, int totalBalls_B, int& currentBatsmanIndex_BattingEnd_B, int& currentBatsmanIndex_BowlingEnd_B, std::string** teamA_B, std::string  battingScoreCardArrayLeft_B[11][2], int  battingScoreCardArrayRight_B[11][6], std::string  bowlingScoreCardArrayLeft_B[5][1], int  bowlingScoreCardArrayRight_B[11][7], float& oversBowled_B, int& totalScore_B, float& runRate_B, std::string& fallOfWickets_B, std::string& bowlerOfMatch_B, std::string& batsmanOftheMatch_B, std::string& winningTeam_B, std::string& matchSummary_B, int& falledWicket_B, std::string& lastBatsManOut_B, int& batsmanIndex_B, std::string& bowlerName_B, int& bowlerIndex_B, int& bowlerOverNumber_B, int oversToExecuteAtOnce)
{
	genBallSeqTeamB_B(oversPerBowler_B, balls_B, teamB_B);//call			

		  /*******************************
		  * Starting innings of Team B from here
			*******************************/

		  // Picking 11 bastmen of Team B one by one
	for (int i = 1; i < 11; i++)
	{
		if (ballNumber_B < totalBalls_B)
		{
			battingNowTeam_B(
				ballNumber_B, //current ball number
				currentBatsmanIndex_BattingEnd_B,
				currentBatsmanIndex_BowlingEnd_B,
				balls_B,
				teamA_B,
				battingScoreCardArrayLeft_B,
				battingScoreCardArrayRight_B,
				bowlingScoreCardArrayLeft_B,
				bowlingScoreCardArrayRight_B,
				teamB_B,
				oversBowled_B,		//current overs bowled
				totalScore_B,			//calculate total score
				runRate_B,			//current run rate
				fallOfWickets_B,		// current fall of wicket 
				bowlerOfMatch_B,
				batsmanOftheMatch_B,
				winningTeam_B,
				matchSummary_B,
				falledWicket_B,			//how many wickets falled till now
				lastBatsManOut_B,
				batsmanIndex_B,			//converting string to int		
				bowlerName_B,
				bowlerIndex_B,
				bowlerOverNumber_B,
				totalBalls_B,
				oversToExecuteAtOnce
			);

		}
	}
}

void teamABatting(int oversPerBowler_A, std::string** balls_A, std::string** teamB_A, int& ballNumber_A, int totalBalls_A, int& currentBatsmanIndex_BattingEnd_A, int& currentBatsmanIndex_BowlingEnd_A, std::string** teamA_A, std::string  battingScoreCardArrayLeft_A[11][2], int  battingScoreCardArrayRight_A[11][6], std::string  bowlingScoreCardArrayLeft_A[5][1], int  bowlingScoreCardArrayRight_A[11][7], float& oversBowled_A, int& totalScore_A, float& runRate_A, std::string& fallOfWickets_A, std::string& bowlerOfMatch_A, std::string& batsmanOftheMatch_A, std::string& winningTeam_A, std::string& matchSummary_A, int& falledWicket_A, std::string& lastBatsManOut_A, int& batsmanIndex_A, std::string& bowlerName_A, int& bowlerIndex_A, int& bowlerOverNumber_A, int oversToExecuteAtOnce)
{

	//Filling Balling order of TeamB Bowlers in balls[][] array			
	genBallSeqTeamB_A(oversPerBowler_A, balls_A, teamB_A);//call			

	  /*******************************
	  * Starting innings of Team A from here
	  ********************************/

	 // Picking 11 bastmen of Team A one by one
	for (int i = 1; i < 11; i++)
	{
		if (ballNumber_A < totalBalls_A)
		{
			battingNowTeam_A(
				ballNumber_A, //current ball number
				currentBatsmanIndex_BattingEnd_A,
				currentBatsmanIndex_BowlingEnd_A,
				balls_A,
				teamA_A,
				battingScoreCardArrayLeft_A,
				battingScoreCardArrayRight_A,
				bowlingScoreCardArrayLeft_A,
				bowlingScoreCardArrayRight_A,
				teamB_A,
				oversBowled_A,		//current overs bowled
				totalScore_A,			//calculate total score
				runRate_A,			//current run rate
				fallOfWickets_A,		// current fall of wicket 
				bowlerOfMatch_A,
				batsmanOftheMatch_A,
				winningTeam_A,
				matchSummary_A,
				falledWicket_A,			//how many wickets falled till now
				lastBatsManOut_A,
				batsmanIndex_A,			//converting string to int		
				bowlerName_A,
				bowlerIndex_A,
				bowlerOverNumber_A,
				totalBalls_A,
				oversToExecuteAtOnce
			);
		}
	}
}

bool getToss() {
	//returning either 0 or 1
	srand((unsigned int)time(NULL));
	return  ((rand() % 2) == 1);

}


