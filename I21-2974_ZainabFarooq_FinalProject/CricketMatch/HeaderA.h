#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
using namespace std;

string **showTeamA();

void genBallSeqTeamB_A(int oversPerBowler, std::string** balls, string** bowler);

void battingNowTeam_A(
			int &ballNumber, //current deliverd ball number
			int &currentBatsmanBattingEnd, 
			int &currentBatsman_BowlingEnd, 
			string** balls, 
			string** teamABatsman, 
			string battingScoreCardArrayLeft [][2], 
			int battingScoreCardArrayRight [11][6], 
			string bowlingScoreCardArrayLeft[5][1], 
			int bowlingScoreCardArrayRight[][7], 
			string **teamBbowler,			
			float &oversBowled ,		//current overs bowled
			int &totalScore,			//calculate total score
			float &runRate,			//current run rate
			string &fallOfWickets,	// current fall of wicket 
			string &bowlerOfMatch,
			string &batsmanOftheMatch,
			string &winningTeam,
			string &matchSummary,
			int &falledWicket,			//how many wickets falled till now
			string &lastBatsManOut,
			int &batsmanIndex,		//converting string to int		
			string &bowlerName,
			int &bowlerIndex,
			int &bowlerOverNumber,
			int totalBalls,
			int oversToExecuteAtOnce
					 );

void battingNowTeam_B(
	int &ballNumber, 
	int &currentBatsmanBattingEnd, 
	int &currentBatsman_BowlingEnd, 
	string** balls, 
	string** teamABatsman, 
	string battingScoreCardArrayLeft [][2], 
	int battingScoreCardArrayRight [11][6], 
	string bowlingScoreCardArrayLeft[5][1], 
	int bowlingScoreCardArrayRight[][7],
	int oversToExecuteAtOnce
);

void insertScore_A(
	int &bowlerIndex, 
	int bowlingScoreCardArrayRight[][7], 
	int &batsmanIndex, 
	int battingScoreCardArrayRight [11][6],
	int &totalScore,	// total team score
	int score,			// current score made by the batsman
	int &ballNumber,
	int &bowlerOverNumber
);

void insertMaiden_A(int& bowlerIndex, int score, int  bowlingScoreCardArrayRight[][7]);

void insertNoBall_A(int &bowlerIndex, 
					int bowlingScoreCardArrayRight[][7],
					int battingScoreCardArrayRight[][6],
					int &batsmanIndex
					);

void insertWideBall_A(int &bowlerIndex, 
					int bowlingScoreCardArrayRight[][7],
					int battingScoreCardArrayRight[][6],
					int &batsmanIndex
					);

void insertOut_A(
	int &batsmanIndex, 
	string battingScoreCardArrayLeft[][2], 
	int &bowlerIndex, 
	string &bowlerName, 
	int bowlingScoreCardArrayRight[][7], 
	int &ballNumber, 
	string** teamABatsman,
	float &oversBowled ,		//current overs bowled
	int &totalScore,			//calculate total score
	float &runRate,			//current run rate
	string &fallOfWickets,	// current fall of wicket 
	string &bowlerOfMatch,
	string &batsmanOftheMatch,
	string &winningTeam,
	string &matchSummary,
	int &falledWicket,			//how many wickets falled till now
	string &lastBatsManOut,
	int battingScoreCardArrayRight [][6]
	);

void showFullBattingScoreBoard_A(
	int[][6], 
	string** teamA,
	float &oversBowled ,		//current overs bowled
	int &totalScore,			//calculate total score
	float &runRate,			//current run rate
	string &fallOfWickets,	// current fall of wicket 
	string &bowlerOfMatch,
	string &batsmanOftheMatch,
	string &winningTeam,
	string &matchSummary,
	int &falledWicket			//how many wickets falled till now
	
	);

void showFullBowlingScoreBoard_A(string[][1], int[][7], string** teamBbowler);

bool setNextBatsman_A (int &currentBatsmanBattingEnd, int &currentBatsman_BowlingEnd, string** teamABatsman);

void intializeMatchData (char choice_match_start);

void showTotalBar_A(int &totalScore, float &oversBowled, int &ballNumber, float &runRate);

void showFallOfWicket_A(
	int &falledWicket,			//how many wickets falled till now
	int &totalScore,			//current score
	string &lastBatsManOut,		// name of Batsman
	float &oversBowled,			//overs bowled so far
	string &fallOfWickets,		//string to be prepared for cout
	bool isBatsmanOutNow
	
	);

float getOverBowled_A (int ballNumber);

float getRunRate_A (int &totalScore ,int &totalBalls);

bool isOverChanged_A(int& bowlerIndex);

void swapBatsman_A(int& currentBatsmanBattingEnd, int& currentBatsman_BowlingEnd);