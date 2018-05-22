#pragma once
#include <string>

// don't use namespace in header files, easy to lose track of
class FBullCowGame {
public:
	FBullCowGame();

	int GetMaxTries() const;
	int GetCurrentTry() const;
	bool IsGameWon() const;

	void Reset(); // TODO make a more rich return value.
	bool CheckGuessValidity(std::string); // TODO make a more rich return value.
	// provide a method for counting bulls & cows, and increasing try #

// Please try and ignore this and focus on the private section.
private:
	int MyCurrentTry;
	int MyMaxTries;
};
