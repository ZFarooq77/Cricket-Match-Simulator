#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
using namespace std;

string **showTeamB();

void genBallSeqTeamB_B(int oversPerBowler, std::string** balls, string** bowler);

void battingNowTeam_B(
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

void battingNowTeamB_B(int &ballNumber, int &currentBatsmanBattingEnd, int &currentBatsman_BowlingEnd, string** balls, string** teamABatsman, string battingScoreCardArrayLeft [][2], int battingScoreCardArrayRight [11][6], string bowlingScoreCardArrayLeft[5][1], int bowlingScoreCardArrayRight[][7], int oversToExecuteAtOnce);

void insertScore_B(
	int &bowlerIndex, 
	int bowlingScoreCardArrayRight[][7], 
	int &batsmanIndex, 
	int battingScoreCardArrayRight [11][6],
	int &totalScore,	// total team score
	int score,			// current score made by the batsman
	int &ballNumber,
	int &bowlerOverNumber
);

void insertMaiden_B(int& bowlerIndex, int score, int  bowlingScoreCardArrayRight[][7]);

void insertNoBall_B(int &bowlerIndex, 
					int bowlingScoreCardArrayRight[][7],
					int battingScoreCardArrayRight[][6],
					int &batsmanIndex
					);

void insertWideBall_B(int &bowlerIndex, 
					int bowlingScoreCardArrayRight[][7],
					int battingScoreCardArrayRight[][6],
					int &batsmanIndex
					);

void insertOut_B(
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

void showFullBattingScoreBoard_B(
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

void showFullBowlingScoreBoard_B(string[][1], int[][7], string** teamBbowler);

bool setNextBatsman_B (int &currentBatsmanBattingEnd, int &currentBatsman_BowlingEnd, string** teamABatsman);

void intializeMatchData (char choice_match_start);

void showTotalBar_B(int &totalScore, float &oversBowled, int &ballNumber, float &runRate);

void showFallOfWicket_B(
	int &falledWicket,			//how many wickets falled till now
	int &totalScore,			//current score
	string &lastBatsManOut,		// name of Batsman
	float &oversBowled,			//overs bowled so far
	string &fallOfWickets,		//string to be prepared for cout
	bool isBatsmanOutNow
	
	);

float getOverBowled_B (int ballNumber);

float getRunRate_B (int &totalScore ,int &totalBalls);

bool isOverChanged_B(int& bowlerIndex);

void swapBatsman_B(int& currentBatsmanBattingEnd, int& currentBatsman_BowlingEnd);