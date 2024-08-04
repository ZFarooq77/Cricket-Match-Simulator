#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <fstream>
#include<sstream>
#include "HeaderB.h" 
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
void genBallSeqTeamB_B(int oversPerBowler_B, std::string** balls_B, string** bowler_B)
{
	
	int count = 0;
	int overNumber = 0;
	for (int k = 0; k < oversPerBowler_B; k++) {
		overNumber++;
		for (int j = 10; j > 5; j--)
		{
			int x = count + 6;
			int i = count;
			for (; i < x; i++)// 6balls
			{
				balls_B[i][0] = bowler_B[j][0]; //add bowler name
				balls_B[i][1] = bowler_B[j][1]; //add bowler type
				balls_B[i][2] = to_string(j); //add bowler index
				balls_B[i][3] = to_string(overNumber); //add over number of the bowler
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
int ballFunction_B(bool isBowler_B) {

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
		if (isBowler_B == true) {
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
void battingNowTeam_B(
	int& ballNumber_B,
	int& currentBatsman_BattingEnd_B,
	int& currentBatsman_BowlingEnd_B,
	string** balls_B,
	string** teamABatsman_B,
	string battingScoreCardArrayLeft_B[][2],
	int battingScoreCardArrayRight_B[][6],
	string bowlingScoreCardArrayLeft_B[][1],
	int bowlingScoreCardArrayRight_B[][7],
	string** teamBbowler_B,
	float& oversBowled_B,		//current overs bowled
	int& totalScore_B,			//calculate total score
	float& runRate_B,				//current run rate
	string& fallOfWickets_B,		// current fall of wicket 
	string& bowlerOfMatch_B,
	string& batsmanOftheMatch_B,
	string& winningTeam_B,
	string& matchSummary_B,
	int& falledWicket_B,			//how many wickets falled till now
	string& lastBatsManOut_B,
	int& batsmanIndex_B,			//converting string to int		
	string& bowlerName_B,
	int& bowlerIndex_B,
	int& bowlerOverNumber_B,
	int totalBalls_B,
	int oversToExecuteAtOnce
)
{
	int score_B; //variable for switch block
	bool isBatsmanOutNow_B = false;
	//Strike rate = (runs scored / balls faced) × 100
	float ballFacedbyNewBatsman_B = 0;
	float runsByNewBatsman_B = 0;

	//inser playing for both current batsmen
	teamABatsman_B[currentBatsman_BattingEnd_B][2] = "Playing...  ";
	cout << "currentBatsman_BattingEnd" << teamABatsman_B[currentBatsman_BattingEnd_B][0];
	teamABatsman_B[currentBatsman_BowlingEnd_B][2] = "Playing...  ";
	cout << "currentBatsman_BowlingEnd" << teamABatsman_B[currentBatsman_BowlingEnd_B][0];
	//loop will work untill a batsman gets out
	do
	{
		//string** batsmenArrayTeamA = showTeamA();
		string strCurrentBM_B = teamABatsman_B[currentBatsman_BattingEnd_B][0];
		string strCurrentBMType_B = teamABatsman_B[currentBatsman_BattingEnd_B][1];

		//increment ball ballNumber
		ballNumber_B++;
		

		batsmanIndex_B = currentBatsman_BattingEnd_B;
		bowlerName_B = balls_B[ballNumber_B - 1][0];
		bowlerIndex_B = std::stoi(balls_B[ballNumber_B - 1][2]);
		bowlerOverNumber_B = std::stoi(balls_B[ballNumber_B - 1][3]);

		bool isBowler_B; //is batsman a bowler?

		//check if batsman is bowler 
		int res = strCurrentBMType_B.compare("Bowler");
		if (res == 0) // if bowler
			isBowler_B = true;
		else //For Batsman or WicketKeeper
			isBowler_B = false;

		//if over is changed, swap batsman
		if (isOverChanged_B(bowlerIndex_B))
		{
			swapBatsman_B(currentBatsman_BattingEnd_B, currentBatsman_BowlingEnd_B);
		}

		score_B = ballFunction_B(isBowler_B);		//Get score from ball function

		switch (score_B)
		{
			//out = -1
			//Wide ball = -2
			//No ball =  -3
			//Regular =  actual score (0 - 6)
			//score = 3;//wideball

		case -1:
			insertOut_B(
				currentBatsman_BattingEnd_B, //batsmanIndex
				battingScoreCardArrayLeft_B,
				bowlerIndex_B,
				bowlerName_B,
				bowlingScoreCardArrayRight_B,
				ballNumber_B,
				teamABatsman_B,
				oversBowled_B,		//current overs bowled
				totalScore_B,			//calculate total score
				runRate_B,			//current run rate
				fallOfWickets_B,	// current fall of wicket 
				bowlerOfMatch_B,
				batsmanOftheMatch_B,
				winningTeam_B,
				matchSummary_B,
				falledWicket_B,			//how many wickets falled till now
				lastBatsManOut_B,
				battingScoreCardArrayRight_B
			);

			//set the index of next batsman in reference variables
			if (!setNextBatsman_B(
				currentBatsman_BattingEnd_B,
				currentBatsman_BowlingEnd_B,
				teamABatsman_B)
											)
			{
				break; // break if last player is also out
			}

			isBatsmanOutNow_B = true;
			break;
		case -2:
			insertWideBall_B(bowlerIndex_B,
				bowlingScoreCardArrayRight_B,
				battingScoreCardArrayRight_B,
				batsmanIndex_B

			);
			break;
		case -3:
			insertNoBall_B(bowlerIndex_B,
				bowlingScoreCardArrayRight_B,
				battingScoreCardArrayRight_B,
				batsmanIndex_B

			);
			break;
		default: // if score is between 0-6
			insertScore_B(
				bowlerIndex_B,
				bowlingScoreCardArrayRight_B,
				batsmanIndex_B,
				battingScoreCardArrayRight_B,
				totalScore_B,
				score_B,
				ballNumber_B,
				bowlerOverNumber_B
			);

			if (score_B == 1 || score_B == 3 || score_B == 5)
			{
				swapBatsman_B(currentBatsman_BattingEnd_B, currentBatsman_BowlingEnd_B);
			}
			break;
		}	// end switch	

		system("CLS");// clear screen before displaying both score boards
		
		cout << " **********************************" << endl;
		cout << "    Team B  Batting Now" << endl;
		cout << " **********************************" << endl;

		cout << "Ball No: " << ballNumber_B << endl;
		cout << "Total Score: " << totalScore_B << endl;

		cout << "currentBatsman_BattingEnd" << teamABatsman_B[currentBatsman_BattingEnd_B][0] << endl;
		//teamABatsman[currentBatsman_BowlingEnd][2] = "Playing...  ";
		cout << "currentBatsman_BowlingEnd" << teamABatsman_B[currentBatsman_BowlingEnd_B][0] << endl;

		showFullBattingScoreBoard_B(
			battingScoreCardArrayRight_B,
			teamABatsman_B,
			oversBowled_B,		//current overs bowled
			totalScore_B,			//calculate total score
			runRate_B,			//current run rate
			fallOfWickets_B,	// current fall of wicket 
			bowlerOfMatch_B,
			batsmanOftheMatch_B,
			winningTeam_B,
			matchSummary_B,
			falledWicket_B			//how many wickets falled till now			

		);
		oversBowled_B = getOverBowled_B(ballNumber_B);//float(ballNumber)/6


		//show horizontal bar below batting score card before bowling score card
		showTotalBar_B(totalScore_B, oversBowled_B, ballNumber_B, runRate_B);

		//show fall of wickets below total only batsman in out

		showFallOfWicket_B(
			falledWicket_B,			//how many wickets falled till now
			totalScore_B,			//current score
			lastBatsManOut_B,		// name of Batsman
			oversBowled_B,			//overs bowled so far
			fallOfWickets_B,		//string to be prepared for cout
			isBatsmanOutNow_B
		);

		cout << endl << endl << "------------------------------------------------------" << endl;

		cout << " **********************************" << endl;
		cout << "    Team A  Bowling Now" << endl;
		cout << " **********************************" << endl;

		showFullBowlingScoreBoard_B(bowlingScoreCardArrayLeft_B, bowlingScoreCardArrayRight_B, teamBbowler_B);
		
		// executing overs at once

		if (ballNumber_B >= oversToExecuteAtOnce*6)
		{
			cin.get();
		}

	} while (score_B != -1 && ballNumber_B < totalBalls_B);//loop will break, if score is -1, i.e., batsman is out




}

void insertScore_B(
	int& bowlerIndex_B, //current bowler
	int bowlingScoreCardArrayRight_B[][7],
	int& batsmanIndex_B,
	int battingScoreCardArrayRight_B[11][6],
	int& totalScore_B,	// total team score
	int score_B,			// current score made by the batsman
	int& ballNumber_B,
	int& bowlerOverNumber_B
)
{
	insertMaiden_B(bowlerIndex_B, score_B, bowlingScoreCardArrayRight_B);

	bowlingScoreCardArrayRight_B[bowlerIndex_B][0] = bowlerOverNumber_B; // insert overs
	bowlingScoreCardArrayRight_B[bowlerIndex_B][2] = bowlingScoreCardArrayRight_B[bowlerIndex_B][2] + score_B; // insert Score
	battingScoreCardArrayRight_B[batsmanIndex_B][0] = battingScoreCardArrayRight_B[batsmanIndex_B][0] + score_B; // Run Coloumn 0
	battingScoreCardArrayRight_B[batsmanIndex_B][1] = battingScoreCardArrayRight_B[batsmanIndex_B][1] + 1; // Bowles played Coloumn 0

	//ECO: Economy rate in cricket is the average number of runs conceded per over bowled
	bowlingScoreCardArrayRight_B[bowlerIndex_B][4] = bowlingScoreCardArrayRight_B[bowlerIndex_B][2] / bowlingScoreCardArrayRight_B[bowlerIndex_B][0];

	// Strike Rate  = (runs scored / balls faced) × 100
	battingScoreCardArrayRight_B[batsmanIndex_B][5] = (battingScoreCardArrayRight_B[batsmanIndex_B][0] / battingScoreCardArrayRight_B[batsmanIndex_B][1]) * 100;

	//inser 4 in battingScoreCardArrayRight[batsmanIndex][3]
	if (score_B == 4)
		battingScoreCardArrayRight_B[batsmanIndex_B][3] = battingScoreCardArrayRight_B[batsmanIndex_B][3] + 1;

	//inser 6 in battingScoreCardArrayRight[batsmanIndex][4]
	if (score_B == 6)
		battingScoreCardArrayRight_B[batsmanIndex_B][4] = battingScoreCardArrayRight_B[batsmanIndex_B][4] + 1;

	totalScore_B = totalScore_B + score_B; // add to total score
	
}

void insertMaiden_B(int& bowlerIndex_B, int score_B, int  bowlingScoreCardArrayRight_B[][7])
{

	//count deleveries of each bowler seperately
	static int previousBowlerIndex_B = bowlerIndex_B;
	static int overScore_B = 0;
	//score = 0;//testing maiden

	if (previousBowlerIndex_B == bowlerIndex_B)
	{
		overScore_B = overScore_B + score_B;
	}
	else
	{
		// insert Maiden Over
		if (overScore_B == 0)
			bowlingScoreCardArrayRight_B[previousBowlerIndex_B][1] = bowlingScoreCardArrayRight_B[previousBowlerIndex_B][1] + 1;
		overScore_B = 0;
		previousBowlerIndex_B = bowlerIndex_B; //update value
	}
}

void insertNoBall_B(int& bowlerIndex_B,
	int bowlingScoreCardArrayRight_B[][7],
	int battingScoreCardArrayRight_B[][6],
	int& batsmanIndex_B
)
{
	//insert increment out by 1 in WICKETS column
	bowlingScoreCardArrayRight_B[bowlerIndex_B][6] = bowlingScoreCardArrayRight_B[bowlerIndex_B][6] + 1;

	//increase played balls
	battingScoreCardArrayRight_B[batsmanIndex_B][1] = battingScoreCardArrayRight_B[batsmanIndex_B][1] + 1; // Bowles played Coloumn 0

}

void insertWideBall_B(int& bowlerIndex_B,
	int bowlingScoreCardArrayRight_B[][7],
	int battingScoreCardArrayRight_B[][6],
	int& batsmanIndex_B
)
{
	//insert increment out by 1 in WICKETS column
	bowlingScoreCardArrayRight_B[bowlerIndex_B][5] = bowlingScoreCardArrayRight_B[bowlerIndex_B][5] + 1;

	//increase played balls
	battingScoreCardArrayRight_B[batsmanIndex_B][1] = battingScoreCardArrayRight_B[batsmanIndex_B][1] + 1; // Bowles played Column 0

}
/*
* batsmanIndex: for filling up the rows of int arrays accordingly
* battingScoreCardArrayLeft: to print the name of batsman and bowler currently playing
* bowlerIndex: for filling up rows of int array to genrate score of bowler score board
* bowlerName: for displaying the the scores of bowler infront of him
* bowlingScoreCardArrayRight: to generate scores of bowler
* insertOut(int batsmanIndex, string battingScoreCardArrayLeft[][2], int bowlerIndex, string bowlerName, int bowlingScoreCardArrayRight[][7]);
*/
void insertOut_B(
	int& currentBatsman_BattingEnd_B, //batsmanIndex
	string battingScoreCardArrayLeft_B[][2],
	int& bowlerIndex_B,
	string& bowlerName_B,
	int bowlingScoreCardArrayRight_B[][7],
	int& ballNumber_B,
	string** teamABatsman_B,
	float& oversBowled_B,		//current overs bowled
	int& totalScore_B,			//calculate total score
	float& runRate_B,			//current run rate
	string& fallOfWickets_B,	// current fall of wicket 
	string& bowlerOfMatch_B,
	string& batsmanOftheMatch_B,
	string& winningTeam_B,
	string& matchSummary_B,
	int& falledWicket_B,			//how many wickets falled till now
	string& lastBatsManOut_B,
	int battingScoreCardArrayRight_B[][6]
)
{
	//string** teamABatsman = showTeamA();//get all batsman in an array

	//insert bowler name in the index position of batsman [batsmanIndex][1] in batsmen array
	teamABatsman_B[currentBatsman_BattingEnd_B][2] = "b " + bowlerName_B;

	//cout << teamABatsman [batsmanIndex][2]<<endl;

	//insert no of over in OVERS column in bowler array
	bowlingScoreCardArrayRight_B[bowlerIndex_B][0] = ballNumber_B / 6; //over will be incremented after completion

	//insert increment out by 1 in WICKETS column
	bowlingScoreCardArrayRight_B[bowlerIndex_B][3] = bowlingScoreCardArrayRight_B[bowlerIndex_B][3] + 1;

	//increment falledWicket by one
	falledWicket_B++;

	//insert last batman out
	lastBatsManOut_B = teamABatsman_B[currentBatsman_BattingEnd_B][0];

	//increment ball faced
	battingScoreCardArrayRight_B[currentBatsman_BattingEnd_B][1] = battingScoreCardArrayRight_B[currentBatsman_BattingEnd_B][1] + 1; // Bowles faced Coloumn 0


	//increment ball ballNumber
	//ballNumber++;
}

void showFullBattingScoreBoard_B(
	int battingScoreCardArrayRight_B[][6],
	string** teamA_B,
	float& oversBowled_B,		//current overs bowled
	int& totalScore_B,			//calculate total score
	float& runRate_B,			//current run rate
	string& fallOfWickets_B,	// current fall of wicket 
	string& bowlerOfMatch_B,
	string& batsmanOftheMatch_B,
	string& winningTeam_B,
	string& matchSummary_B,
	int& falledWicket_B			//how many wickets falled till now	

)
{	
	cout << "Batsman" << setw(45) << "Runs" << setw(15) << "balls" << setw(17) << "Matches" << setw(15) << "4's" << setw(16) << "6's" << setw(13) << "SR" << endl;
	for (int i = 0; i < 11; i++)
	{

		cout << teamA_B[i][0] << "\t\t" << teamA_B[i][2] << "\t\t" << battingScoreCardArrayRight_B[i][0] << "\t\t" << battingScoreCardArrayRight_B[i][1] << "\t\t" << battingScoreCardArrayRight_B[i][2] << "\t\t" <<
			battingScoreCardArrayRight_B[i][3] << "\t\t" << battingScoreCardArrayRight_B[i][4] << "\t\t" << battingScoreCardArrayRight_B[i][5] << endl;

	}

}
void showFullBowlingScoreBoard_B(
	string bowlingScoreCardArrayLeft_B[][1],
	int bowlingScoreCardArrayRight_B[][7],
	string** teamBbowler_B
)
{
	cout << "Bowlers" << setw(20) << "Overs" << "\t\t" << "Maiden" << "\t\t" << "Runs" << "\t\t" << "Wickets" << setw(13) << "ECON" << setw(15) << "Wide" << setw(15) << "NoBall" << endl;
	for (int i = 10; i >= 6; i--)
	{

		cout << teamBbowler_B[i][0] << "\t\t" << bowlingScoreCardArrayRight_B[i][0] << "\t\t" << bowlingScoreCardArrayRight_B[i][1] << "\t\t" << bowlingScoreCardArrayRight_B[i][2] << "\t\t" <<
			bowlingScoreCardArrayRight_B[i][3] << "\t\t" << bowlingScoreCardArrayRight_B[i][4] << "\t\t" << bowlingScoreCardArrayRight_B[i][5] << "\t\t" << bowlingScoreCardArrayRight_B[i][6] << endl;
	}
}

/*
* Sets new batsman after getting out
* Returns true if nxt batting is available
* Returns false if not more batting is left
*/
bool setNextBatsman_B(
	int& currentBatsmanBattingEnd_B,
	int& currentBatsman_BowlingEnd_B,
	string **teamABatsman_B
)
{
	//return the highest index value + 1
	if (currentBatsmanBattingEnd_B < currentBatsman_BowlingEnd_B)
		currentBatsmanBattingEnd_B = currentBatsman_BowlingEnd_B + 1;
	else
		currentBatsmanBattingEnd_B = currentBatsmanBattingEnd_B + 1;

	//inser playing... for current batsmen
	if (currentBatsmanBattingEnd_B < 11) 
	{
		teamABatsman_B[currentBatsmanBattingEnd_B][2] = "Playing...  ";
		return true;
	}
	else
	{
		currentBatsmanBattingEnd_B--;
		return false; // no more batting. Quit batting of the team return false
	}
}

/*
* Swaps batsman after getting Odd run: 1, 3, 5 or after over completion of an Over
*/
void swapBatsman_B(int& currentBatsmanBattingEnd_B, int& currentBatsman_BowlingEnd_B)
{

	int tempIndexForSwap_B = currentBatsmanBattingEnd_B;

	currentBatsmanBattingEnd_B = currentBatsman_BowlingEnd_B;

	currentBatsman_BowlingEnd_B = tempIndexForSwap_B;

}

/*
Prints the horizontal bar displaying Total:	<overs> (RR <curentscore/overs>)	<curentscore>
*/
void showTotalBar_B(int& totalScore_B, float& oversBowled_B, int& ballNumber_B, float& runRate_B)
{
	runRate_B = getRunRate_B(totalScore_B, ballNumber_B); // of the Team

	cout << endl << "TOTAL:	" << oversBowled_B << " Overs " << "(RR: " << runRate_B << " )" << "    Score:   " << totalScore_B << endl;
}

/*
Display
Fall of Wickets: 1-6 (<batsmanName, <overbowled> ov), <wicketNo-scoreAtThatTime> (<batsmanName, <overbowled> ov),....
*/
void showFallOfWicket_B(
	int& falledWicket_B,			//how many wickets falled till now
	int& totalScore_B,			//current score
	string & lastBatsManOut_B,		// name of Batsman
	float& oversBowled_B,			//overs bowled so far
	string & fallOfWickets_B,		//string to be prepared for cout
	bool isBatsmanOutNow_B
)
{
	static int count = 0;
	string fallofWicketNow_B;

	fallofWicketNow_B = to_string(falledWicket_B) + "-" + to_string(totalScore_B) + "(" + lastBatsManOut_B + ", " + to_string(oversBowled_B) + "ov)";

	if (isBatsmanOutNow_B) //Prepare string, if batsman is out 
	{
		if (count == 0)
		{
			fallOfWickets_B = fallOfWickets_B + fallofWicketNow_B;
			count++;
		}
		else
			fallOfWickets_B = fallOfWickets_B + ", " + fallofWicketNow_B;//for all other turns				
	}

	cout << "Fall of Wickets: " << fallOfWickets_B << endl;

}

float getOverBowled_B(int ballNumber_B)
{
	return float(ballNumber_B) / 6;
}

//
float getRunRate_B(int& totalScore_B, int& totalBalls_B)
{
	//Run Rate Team = (Run scored by the Team / total balls faced) × 100
	return (float(totalScore_B) / totalBalls_B * 100);
}

//Batting strike rate (s/r) is defined for a batter as the average number of runs scored per 100 balls faced


bool isOverChanged_B(int& bowlerIndex_B)
{

	//count deleveries of each bowler seperately
	static int previousBowlerIndex_B = bowlerIndex_B;

	if (previousBowlerIndex_B != bowlerIndex_B)
	{
		previousBowlerIndex_B = bowlerIndex_B; //update value
		return true;
	}
	return false;
}
