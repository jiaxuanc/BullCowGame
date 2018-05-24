#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) { return EGuessStatus::Not_Isogram; }							// if the guess isn't an isogram
	else if (!IsLowercase(Guess)) { return EGuessStatus::Not_Lowercase;	}					// if the guess isn't all lowercase
	else if (Guess.length() != GetHiddenWordLength()) { return EGuessStatus::Wrong_Length; } // if the guess length is wrong
	else { return EGuessStatus::OK; }														// otherwise
	
	return EGuessStatus::OK;		// TODO make actual error
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "ant";		// constexpr must have a literal type or a reference type
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// receives a VALID guess, increments turn, and return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{	
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = GetHiddenWordLength();	// assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { BullCowCount.Bulls++; }	// increment bulls if they're in the same place
				else { BullCowCount.Cows++; }					// increment cows if not
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) { bGameIsWon = true; }
	else { bGameIsWon = false; }

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{	
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;					// setup our map, default initializing to false
	for (auto Letter : Word)						// for all letters of the word
	{
		Letter = tolower(Letter);					// handle mixed case
		if (LetterSeen[Letter]) { return false; }	// if the letter is in the map, we do NOT have an isogram
		else { LetterSeen[Letter] = true; }			// otherwise, add the letter to the map as seen
	}

	return true;	// for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto letter : Word) 
	{
		if (!islower(letter)) { return false; }
	}

	return true;
}

