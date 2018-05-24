#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false) {							// if the guess isn't an isogram
		return EGuessStatus::Not_Isogram;
	} else if (false)						// if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	} else if (Guess.length() != GetHiddenWordLength()) {		// if the guess length is wrong
		return EGuessStatus::Wrong_Length;
	} else {								// otherwise
		return EGuessStatus::OK;
	}
	
	return EGuessStatus::OK;		// TODO make actual error
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "ant";		// constexpr must have a literal type or a reference type
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

// receives a VALID guess, increments turn, and return count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{	
	// increment the turn number
	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) 
	{
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) 
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) BullCowCount.Bulls++;	// increment bulls if they're in the same place
				else BullCowCount.Cows++;	// increment cows if not
			}
		}
	}
	return BullCowCount;
}

