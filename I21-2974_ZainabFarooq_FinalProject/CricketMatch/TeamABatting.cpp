#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <fstream>
#include<sstream>
#include "HeaderA.h" 
using namespace std;

/*
*	Calls:
*		batTeamA()
*		batTeamB()
*/



/*
* Generated BallSequnce in Dynamic array  std::string** balls
				balls[i][0] ; //add bowler name
				balls[i][1] ; //add bowler type "bowler"
				balls[i][2] ; //add bowler index from TeamB players 11-6
				balls[i][3] ; //add over number of the bowler will bowl
*/ 
void genBallSeqTeamB_A(int oversPerBowler_A, std::string** balls_A, string** bowler_A)
{
	
	int count = 0;
	int overNumber = 0;
	for (int k = 0; k < oversPerBowler_A; k++) {
		overNumber++;
		for (int j = 10; j > 5; j--)
		{
			int x = count + 6;
			int i = count;
			for (; i < x; i++)// 6balls
			{
				balls_A[i][0] = bowler_A[j][0]; //add bowler name
				balls_A[i][1] = bowler_A[j][1]; //add bowler type
				balls_A[i][2] = to_string(j); //add bowler index
				balls_A[i][3] = to_string(overNumber); //add over number of the bowler
				count = count + 1;
				//cout << balls[i][0]<< balls[i][1] <<  balls[i][2] <<balls[i][3]<<endl;
			}
		}
	}
}
/*
		//out = -1
		//Wide ball = -2
		//No ball =  -3
		//Regular =  actual score (0 - 6)
		//Wide ball probability = 10%		return -2
		//No ball probability = 10%			return -3
		//Regular ball probability = 80%	return actual score
*/
int ballFunction_A(bool isBowler_A) {

	int randOutput; //, outProbOfBatsman;// score
	bool isRegularBall = false;
	srand((unsigned int)time(NULL));

	randOutput = rand() % 101;
	cout << "randOutput: " << randOutput << endl;

	if (randOutput >= 0 && randOutput <= 10) {
		//wide ball
		return -2;

	}
	else if (randOutput > 10 && randOutput <= 20) {
		//no ball
		return -3;
	}
	else
	{		
		isRegularBall = true;// regular ball		
	}

	// regular bal pobability 80%
	if (isRegularBall) {
		if (isBowler_A == true) {
			if (randOutput >= 0 && randOutput <= 50) {
				return -1;//out
				//cout << "score: " << score << endl;
			}
			else if (randOutput > 50 && randOutput <= 100) {
				srand((unsigned int)time(NULL));
				return rand() % 7;//not out
				//cout << "score: " << score << endl;

			}
		}
		else { // if Batsman
			if (randOutput >= 0 && randOutput <= 30) { // 30% probability
				return -1;
			}
			else if (randOutput > 30 && randOutput <= 100) {
				srand((unsigned int)time(NULL));
				return rand() % 7;
				//cout << "score: " << score << endl;
			}
		}
	}	
}


/*batting score array
* column 0 = Runs
* column 1 = Balls
* column 2 = Matches
* column 3 = 4s
* column 4 = 6s
* column 5 = Strike Rate
*/
void battingNowTeam_A(
	int& ballNumber_A,
	int& currentBatsman_BattingEnd_A,
	int& currentBatsman_BowlingEnd_A,
	string** balls_A,
	string** teamABatsman_A,
	string battingScoreCardArrayLeft_A[][2],
	int battingScoreCardArrayRight_A[][6],
	string bowlingScoreCardArrayLeft_A[][1],
	int bowlingScoreCardArrayRight_A[][7],
	string** teamBbowler_A,
	float& oversBowled_A,		//current overs bowled
	int& totalScore_A,			//calculate total score
	float& runRate_A,				//current run rate
	string& fallOfWickets_A,		// current fall of wicket 
	string& bowlerOfMatch_A,
	string& batsmanOftheMatch_A,
	string& winningTeam_A,
	string& matchSummary_A,
	int& falledWicket_A,			//how many wickets falled till now
	string& lastBatsManOut_A,
	int& batsmanIndex_A,			//converting string to int		
	string& bowlerName_A,
	int& bowlerIndex_A,
	int& bowlerOverNumber_A,
	int totalBalls_A,
	int oversToExecuteAtOnce
)
{
	int score_A; //variable for switch block
	bool isBatsmanOutNow_A = false;
	//Strike rate = (runs scored / balls faced) × 100
	float ballFacedbyNewBatsman_A = 0;
	float runsByNewBatsman_A = 0;

	//inser playing for both current batsmen
	teamABatsman_A[currentBatsman_BattingEnd_A][2] = "Playing...  ";
	cout << "currentBatsman_BattingEnd" << teamABatsman_A[currentBatsman_BattingEnd_A][0];
	teamABatsman_A[currentBatsman_BowlingEnd_A][2] = "Playing...  ";
	cout << "currentBatsman_BowlingEnd" << teamABatsman_A[currentBatsman_BowlingEnd_A][0];
	//loop will work untill a batsman gets out
	do
	{
		//string** batsmenArrayTeamA = showTeamA();
		string strCurrentBM_A = teamABatsman_A[currentBatsman_BattingEnd_A][0];
		string strCurrentBMType_A = teamABatsman_A[currentBatsman_BattingEnd_A][1];

		//increment ball ballNumber
		ballNumber_A++;
		

		batsmanIndex_A = currentBatsman_BattingEnd_A;
		bowlerName_A = balls_A[ballNumber_A - 1][0];
		bowlerIndex_A = std::stoi(balls_A[ballNumber_A - 1][2]);
		bowlerOverNumber_A = std::stoi(balls_A[ballNumber_A - 1][3]);

		bool isBowler_A; //is batsman a bowler?

		//check if batsman is bowler 
		int res = strCurrentBMType_A.compare("Bowler");
		if (res == 0) // if bowler
			isBowler_A = true;
		else //For Batsman or WicketKeeper
			isBowler_A = false;

		//if over is changed, swap batsman
		if (isOverChanged_A(bowlerIndex_A))
		{
			swapBatsman_A(currentBatsman_BattingEnd_A, currentBatsman_BowlingEnd_A);
		}

		score_A = ballFunction_A(isBowler_A);		//Get score from ball function

		switch (score_A)
		{
			//out = -1
			//Wide ball = -2
			//No ball =  -3
			//Regular =  actual score (0 - 6)
			//score = 3;//wideball

		case -1:
			insertOut_A(
				currentBatsman_BattingEnd_A, //batsmanIndex
				battingScoreCardArrayLeft_A,
				bowlerIndex_A,
				bowlerName_A,
				bowlingScoreCardArrayRight_A,
				ballNumber_A,
				teamABatsman_A,
				oversBowled_A,		//current overs bowled
				totalScore_A,			//calculate total score
				runRate_A,			//current run rate
				fallOfWickets_A,	// current fall of wicket 
				bowlerOfMatch_A,
				batsmanOftheMatch_A,
				winningTeam_A,
				matchSummary_A,
				falledWicket_A,			//how many wickets falled till now
				lastBatsManOut_A,
				battingScoreCardArrayRight_A
			);

			//set the index of next batsman in reference variables
			if (!setNextBatsman_A(
				currentBatsman_BattingEnd_A,
				currentBatsman_BowlingEnd_A,
				teamABatsman_A)
											)
			{
				break; // break if last player is also out
			}

			isBatsmanOutNow_A = true;
			break;
		case -2:
			insertWideBall_A(bowlerIndex_A,
				bowlingScoreCardArrayRight_A,
				battingScoreCardArrayRight_A,
				batsmanIndex_A

			);
			break;
		case -3:
			insertNoBall_A(bowlerIndex_A,
				bowlingScoreCardArrayRight_A,
				battingScoreCardArrayRight_A,
				batsmanIndex_A

			);
			break;
		default: // if score is between 0-6
			insertScore_A(
				bowlerIndex_A,
				bowlingScoreCardArrayRight_A,
				batsmanIndex_A,
				battingScoreCardArrayRight_A,
				totalScore_A,
				score_A,
				ballNumber_A,
				bowlerOverNumber_A
			);

			if (score_A == 1 || score_A == 3 || score_A == 5)
			{
				swapBatsman_A(currentBatsman_BattingEnd_A, currentBatsman_BowlingEnd_A);
			}
			break;
		}	// end switch	

		system("CLS");// clear screen before displaying both score boards

		cout << " **********************************" << endl;
		cout << "    Team A  Batting Now" << endl;
		cout << " **********************************" << endl;


		cout << "Ball No: " << ballNumber_A << endl;
		cout << "Total Score: " << totalScore_A << endl;

		cout << "currentBatsman_BattingEnd" << teamABatsman_A[currentBatsman_BattingEnd_A][0] << endl;
		//teamABatsman[currentBatsman_BowlingEnd][2] = "Playing...  ";
		cout << "currentBatsman_BowlingEnd" << teamABatsman_A[currentBatsman_BowlingEnd_A][0] << endl;

		showFullBattingScoreBoard_A(
			battingScoreCardArrayRight_A,
			teamABatsman_A,
			oversBowled_A,		//current overs bowled
			totalScore_A,			//calculate total score
			runRate_A,			//current run rate
			fallOfWickets_A,	// current fall of wicket 
			bowlerOfMatch_A,
			batsmanOftheMatch_A,
			winningTeam_A,
			matchSummary_A,
			falledWicket_A			//how many wickets falled till now			

		);
		oversBowled_A = getOverBowled_A(ballNumber_A);//float(ballNumber)/6


		//show horizontal bar below batting score card before bowling score card
		showTotalBar_A(totalScore_A, oversBowled_A, ballNumber_A, runRate_A);

		//show fall of wickets below total only batsman in out

		showFallOfWicket_A(
			falledWicket_A,			//how many wickets falled till now
			totalScore_A,			//current score
			lastBatsManOut_A,		// name of Batsman
			oversBowled_A,			//overs bowled so far
			fallOfWickets_A,		//string to be prepared for cout
			isBatsmanOutNow_A
		);

		cout << endl << endl << "------------------------------------------------------" << endl;

		cout << " **********************************" << endl;
		cout << "    Team B  Bowling Now" << endl;
		cout << " **********************************" << endl;

		showFullBowlingScoreBoard_A(bowlingScoreCardArrayLeft_A, bowlingScoreCardArrayRight_A, teamBbowler_A);
		
		//cin.get();
		//system("pause");

		if (ballNumber_A >= oversToExecuteAtOnce*6)
		{
			cin.get();
		}

	} while (score_A != -1 && ballNumber_A < totalBalls_A);//loop will break, if score is -1, i.e., batsman is out




}

void insertScore_A(
	int& bowlerIndex_A, //current bowler
	int bowlingScoreCardArrayRight_A[][7],
	int& batsmanIndex_A,
	int battingScoreCardArrayRight_A[11][6],
	int& totalScore_A,	// total team score
	int score_A,			// current score made by the batsman
	int& ballNumber_A,
	int& bowlerOverNumber_A
)
{
	insertMaiden_A(bowlerIndex_A, score_A, bowlingScoreCardArrayRight_A);

	bowlingScoreCardArrayRight_A[bowlerIndex_A][0] = bowlerOverNumber_A; // insert overs
	bowlingScoreCardArrayRight_A[bowlerIndex_A][2] = bowlingScoreCardArrayRight_A[bowlerIndex_A][2] + score_A; // insert Score
	battingScoreCardArrayRight_A[batsmanIndex_A][0] = battingScoreCardArrayRight_A[batsmanIndex_A][0] + score_A; // Run Coloumn 0
	battingScoreCardArrayRight_A[batsmanIndex_A][1] = battingScoreCardArrayRight_A[batsmanIndex_A][1] + 1; // Bowles played Coloumn 0

	//ECO: Economy rate in cricket is the average number of runs conceded per over bowled
	bowlingScoreCardArrayRight_A[bowlerIndex_A][4] = bowlingScoreCardArrayRight_A[bowlerIndex_A][2] / bowlingScoreCardArrayRight_A[bowlerIndex_A][0];

	// Strike Rate  = (runs scored / balls faced) × 100
	battingScoreCardArrayRight_A[batsmanIndex_A][5] = (battingScoreCardArrayRight_A[batsmanIndex_A][0] / battingScoreCardArrayRight_A[batsmanIndex_A][1]) * 100;

	//inser 4 in battingScoreCardArrayRight[batsmanIndex][3]
	if (score_A == 4)
		battingScoreCardArrayRight_A[batsmanIndex_A][3] = battingScoreCardArrayRight_A[batsmanIndex_A][3] + 1;

	//inser 6 in battingScoreCardArrayRight[batsmanIndex][4]
	if (score_A == 6)
		battingScoreCardArrayRight_A[batsmanIndex_A][4] = battingScoreCardArrayRight_A[batsmanIndex_A][4] + 1;

	totalScore_A = totalScore_A + score_A; // add to total score
	
}

void insertMaiden_A(int& bowlerIndex_A, int score_A, int  bowlingScoreCardArrayRight_A[][7])
{

	//count deleveries of each bowler seperately
	static int previousBowlerIndex_A = bowlerIndex_A;
	static int overScore_A = 0;
	//score = 0;//testing maiden

	if (previousBowlerIndex_A == bowlerIndex_A)
	{
		overScore_A = overScore_A + score_A;
	}
	else
	{
		// insert Maiden Over
		if (overScore_A == 0)
			bowlingScoreCardArrayRight_A[previousBowlerIndex_A][1] = bowlingScoreCardArrayRight_A[previousBowlerIndex_A][1] + 1;
		overScore_A = 0;
		previousBowlerIndex_A = bowlerIndex_A; //update value
	}
}

void insertNoBall_A(int& bowlerIndex_A,
	int bowlingScoreCardArrayRight_A[][7],
	int battingScoreCardArrayRight_A[][6],
	int& batsmanIndex_A
)
{
	//insert increment out by 1 in WICKETS column
	bowlingScoreCardArrayRight_A[bowlerIndex_A][6] = bowlingScoreCardArrayRight_A[bowlerIndex_A][6] + 1;

	//increase played balls
	battingScoreCardArrayRight_A[batsmanIndex_A][1] = battingScoreCardArrayRight_A[batsmanIndex_A][1] + 1; // Bowles played Coloumn 0

}

void insertWideBall_A(int& bowlerIndex_A,
	int bowlingScoreCardArrayRight_A[][7],
	int battingScoreCardArrayRight_A[][6],
	int& batsmanIndex_A
)
{
	//insert increment out by 1 in WICKETS column
	bowlingScoreCardArrayRight_A[bowlerIndex_A][5] = bowlingScoreCardArrayRight_A[bowlerIndex_A][5] + 1;

	//increase played balls
	battingScoreCardArrayRight_A[batsmanIndex_A][1] = battingScoreCardArrayRight_A[batsmanIndex_A][1] + 1; // Bowles played Column 0

}
/*
* batsmanIndex: for filling up the rows of int arrays accordingly
* battingScoreCardArrayLeft: to print the name of batsman and bowler currently playing
* bowlerIndex: for filling up rows of int array to genrate score of bowler score board
* bowlerName: for displaying the the scores of bowler infront of him
* bowlingScoreCardArrayRight: to generate scores of bowler
* insertOut(int batsmanIndex, string battingScoreCardArrayLeft[][2], int bowlerIndex, string bowlerName, int bowlingScoreCardArrayRight[][7]);
*/
void insertOut_A(
	int& currentBatsman_BattingEnd_A, //batsmanIndex
	string battingScoreCardArrayLeft_A[][2],
	int& bowlerIndex_A,
	string& bowlerName_A,
	int bowlingScoreCardArrayRight_A[][7],
	int& ballNumber_A,
	string** teamABatsman_A,
	float& oversBowled_A,		//current overs bowled
	int& totalScore_A,			//calculate total score
	float& runRate_A,			//current run rate
	string& fallOfWickets_A,	// current fall of wicket 
	string& bowlerOfMatch_A,
	string& batsmanOftheMatch_A,
	string& winningTeam_A,
	string& matchSummary_A,
	int& falledWicket_A,			//how many wickets falled till now
	string& lastBatsManOut_A,
	int battingScoreCardArrayRight_A[][6]
)
{
	//string** teamABatsman = showTeamA();//get all batsman in an array

	//insert bowler name in the index position of batsman [batsmanIndex][1] in batsmen array
	teamABatsman_A[currentBatsman_BattingEnd_A][2] = "b " + bowlerName_A;

	//cout << teamABatsman [batsmanIndex][2]<<endl;

	//insert no of over in OVERS column in bowler array
	bowlingScoreCardArrayRight_A[bowlerIndex_A][0] = ballNumber_A / 6; //over will be incremented after completion

	//insert increment out by 1 in WICKETS column
	bowlingScoreCardArrayRight_A[bowlerIndex_A][3] = bowlingScoreCardArrayRight_A[bowlerIndex_A][3] + 1;

	//increment falledWicket by one
	falledWicket_A++;

	//insert last batman out
	lastBatsManOut_A = teamABatsman_A[currentBatsman_BattingEnd_A][0];

	//increment ball faced
	battingScoreCardArrayRight_A[currentBatsman_BattingEnd_A][1] = battingScoreCardArrayRight_A[currentBatsman_BattingEnd_A][1] + 1; // Bowles faced Coloumn 0


	//increment ball ballNumber
	//ballNumber++;
}

void showFullBattingScoreBoard_A(
	int battingScoreCardArrayRight_A[][6],
	string** teamA_A,
	float& oversBowled_A,		//current overs bowled
	int& totalScore_A,			//calculate total score
	float& runRate_A,			//current run rate
	string& fallOfWickets_A,	// current fall of wicket 
	string& bowlerOfMatch_A,
	string& batsmanOftheMatch_A,
	string& winningTeam_A,
	string& matchSummary_A,
	int& falledWicket_A			//how many wickets falled till now	

)
{	
	cout << "Batsman" << setw(45) << "Runs" << setw(15) << "balls" << setw(17) << "Matches" << setw(15) << "4's" << setw(16) << "6's" << setw(13) << "SR" << endl;
	for (int i = 0; i < 11; i++)
	{

		cout << teamA_A[i][0] << "\t\t" << teamA_A[i][2] << "\t\t" << battingScoreCardArrayRight_A[i][0] << "\t\t" << battingScoreCardArrayRight_A[i][1] << "\t\t" << battingScoreCardArrayRight_A[i][2] << "\t\t" <<
			battingScoreCardArrayRight_A[i][3] << "\t\t" << battingScoreCardArrayRight_A[i][4] << "\t\t" << battingScoreCardArrayRight_A[i][5] << endl;

	}

}
void showFullBowlingScoreBoard_A(
	string bowlingScoreCardArrayLeft_A[][1],
	int bowlingScoreCardArrayRight_A[][7],
	string** teamBbowler_A
)
{
	cout << "Bowlers" << setw(20) << "Overs" << "\t\t" << "Maiden" << "\t\t" << "Runs" << "\t\t" << "Wickets" << setw(13) << "ECON" << setw(15) << "Wide" << setw(15) << "NoBall" << endl;
	for (int i = 10; i >= 6; i--)
	{

		cout << teamBbowler_A[i][0] << "\t\t" << bowlingScoreCardArrayRight_A[i][0] << "\t\t" << bowlingScoreCardArrayRight_A[i][1] << "\t\t" << bowlingScoreCardArrayRight_A[i][2] << "\t\t" <<
			bowlingScoreCardArrayRight_A[i][3] << "\t\t" << bowlingScoreCardArrayRight_A[i][4] << "\t\t" << bowlingScoreCardArrayRight_A[i][5] << "\t\t" << bowlingScoreCardArrayRight_A[i][6] << endl;
	}
}

/*
* Sets new batsman after getting out
* Returns true if nxt batting is available
* Returns false if not more batting is left
*/
bool setNextBatsman_A(
	int& currentBatsmanBattingEnd_A,
	int& currentBatsman_BowlingEnd_A,
	string **teamABatsman_A
)
{
	//return the highest index value + 1
	if (currentBatsmanBattingEnd_A < currentBatsman_BowlingEnd_A)
		currentBatsmanBattingEnd_A = currentBatsman_BowlingEnd_A + 1;
	else
		currentBatsmanBattingEnd_A = currentBatsmanBattingEnd_A + 1;

	//inser playing... for current batsmen
	if (currentBatsmanBattingEnd_A < 11) 
	{
		teamABatsman_A[currentBatsmanBattingEnd_A][2] = "Playing...  ";
		return true;
	}
	else
	{
		currentBatsmanBattingEnd_A--;
		return false; // no more batting. Quit batting of the team return false
	}
}

/*
* Swaps batsman after getting Odd run: 1, 3, 5 or after over completion of an Over
*/
void swapBatsman_A(int& currentBatsmanBattingEnd_A, int& currentBatsman_BowlingEnd_A)
{

	int tempIndexForSwap_A = currentBatsmanBattingEnd_A;

	currentBatsmanBattingEnd_A = currentBatsman_BowlingEnd_A;

	currentBatsman_BowlingEnd_A = tempIndexForSwap_A;

}

/*
Prints the horizontal bar displaying Total:	<overs> (RR <curentscore/overs>)	<curentscore>
*/
void showTotalBar_A(int& totalScore_A, float& oversBowled_A, int& ballNumber_A, float& runRate_A)
{
	runRate_A = getRunRate_A(totalScore_A, ballNumber_A); // of the Team

	cout << endl << "TOTAL:	" << oversBowled_A << " Overs " << "(RR: " << runRate_A << " )" << "    Score:   " << totalScore_A << endl;
}

/*
Display
Fall of Wickets: 1-6 (<batsmanName, <overbowled> ov), <wicketNo-scoreAtThatTime> (<batsmanName, <overbowled> ov),....
*/
void showFallOfWicket_A(
	int& falledWicket_A,			//how many wickets falled till now
	int& totalScore_A,			//current score
	string & lastBatsManOut_A,		// name of Batsman
	float& oversBowled_A,			//overs bowled so far
	string & fallOfWickets_A,		//string to be prepared for cout
	bool isBatsmanOutNow_A
)
{
	static int count = 0;
	string fallofWicketNow_A;

	fallofWicketNow_A = to_string(falledWicket_A) + "-" + to_string(totalScore_A) + "(" + lastBatsManOut_A + ", " + to_string(oversBowled_A) + "ov)";

	if (isBatsmanOutNow_A) //Prepare string, if batsman is out 
	{
		if (count == 0)
		{
			fallOfWickets_A = fallOfWickets_A + fallofWicketNow_A;
			count++;
		}
		else
			fallOfWickets_A = fallOfWickets_A + ", " + fallofWicketNow_A;//for all other turns				
	}

	cout << "Fall of Wickets: " << fallOfWickets_A << endl;

}

float getOverBowled_A(int ballNumber_A)
{
	return float(ballNumber_A) / 6;
}

//
float getRunRate_A(int& totalScore_A, int& totalBalls_A)
{
	//Run Rate Team = (Run scored by the Team / total balls faced) × 100
	return (float(totalScore_A) / totalBalls_A * 100);
}

//Batting strike rate (s/r) is defined for a batter as the average number of runs scored per 100 balls faced


bool isOverChanged_A(int& bowlerIndex_A)
{

	//count deleveries of each bowler seperately
	static int previousBowlerIndex_A = bowlerIndex_A;

	if (previousBowlerIndex_A != bowlerIndex_A)
	{
		previousBowlerIndex_A = bowlerIndex_A; //update value
		return true;
	}
	return false;
}
