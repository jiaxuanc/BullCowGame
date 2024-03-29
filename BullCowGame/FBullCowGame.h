/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>
// don't use namespace in header files since it's easy to lose track of

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

// strongly-typed enum
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EResetStatus
{
	Invalid_Status,
	Set_Hidden_Word,
	Exit
};

// all values intialized to 0
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

struct FDiffLevel
{	
	// TODO initialize
	int32 WordLength = 0;
	// int32 MaxTries = 0;
	// int32 NumHints = 0;
};

class FBullCowGame 
{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(FDiffLevel);
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	FString GenerateHiddenWord(int32);
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
