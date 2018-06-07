/* This is the console executable, that makes use of the FBullCowGame class
This acts as the view in a MVC pattern, and is responsbile for all user
interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
FDiffLevel AskDifficulty();
void PlayGame(FDiffLevel);
FText GetValidGuess();
EResetStatus AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;	// instantiate a new game, which we re-use across plays

// the entry point of the application
int main() 
{	
	PrintIntro();
	FDiffLevel DiffLevel;
	EResetStatus ResetStatus = EResetStatus::Set_Hidden_Word;
	do {
		DiffLevel = AskDifficulty();
		PlayGame(DiffLevel);
		ResetStatus = AskToPlayAgain();
	} while (ResetStatus != EResetStatus::Exit);	// enables the player to play as many times as he/she wants with same or different words

	return 0;									// exit the application
}

// TODO add more game instructions and ASCII art
void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game. \n";
	std::cout << R"(
 ____   __ __  _      _     _____      ____  ____   ___           __   ___   __    __  _____
|    \ |  |  || |    | |   / ___/     /    ||    \ |   \         /  ] /   \ |  |__|  |/ ___/
|  o  )|  |  || |    | |  (   \_     |  o  ||  _  ||    \       /  / |     ||  |  |  (   \_ 
|     ||  |  || |___ | |___\__  |    |     ||  |  ||  D  |     /  /  |  O  ||  |  |  |\__  |
|  O  ||  :  ||     ||     /  \ |    |  _  ||  |  ||     |    /   \_ |     ||  `  '  |/  \ |
|     ||     ||     ||     \    |    |  |  ||  |  ||     |    \     ||     | \      / \    |
|_____| \__,_||_____||_____|\___|    |__|__||__|__||_____|     \____| \___/   \_/\_/   \___|
                                                                                            
)" << std::endl;
	return;
}

FDiffLevel AskDifficulty()
{
	FText WordLength;
	do {
		std::cout << "Choose a word length to guess (at least 3 letters): ";
		std::getline(std::cin, WordLength);
	} while (stoi(WordLength) < 3);
	std::cout << std::endl;
	FDiffLevel DiffLevel = { stoi(WordLength) };	// TODO choose max # of tries, # of hints, etc.
	return DiffLevel;
}

// plays a single game to completion
void PlayGame(FDiffLevel DiffLevel)
{
	BCGame.Reset(DiffLevel);
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)	{
		
		FText Guess = GetValidGuess();		
		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
	
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		
		std::cout << std::endl;
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;	
	FText Guess = "";
	do {
		// get a guess from the player
		int32 CurrentTries = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTries << " of " << BCGame.GetMaxTries();
		std::cout << ". Please enter your guess: ";
		std::getline(std::cin, Guess);	// read through spaces, and discard the input stream once it reaches the new-line character
										// better than std::cin >> Guess, as this will not work properly 
										// if there are spaces between words, like "apple pen"
		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);	// keep looping until we get no errors
	return Guess;
}


EResetStatus AskToPlayAgain()
{
	std::cout << "\nWould you like to play again? Two options: \n";
	std::cout << "  1 = Yes, I want to play again.\n";
	std::cout << "  2 = No, I want to quit. \n";
	EResetStatus Status = EResetStatus::Invalid_Status;
	FText Response = "";

	do {
		std::cout << "Please enter your choice out of the two options (1-2): ";
		std::getline(std::cin, Response);
		
		switch (Response[0])
		{
		case '1':
			Status = EResetStatus::Set_Hidden_Word;
			break;
		case '2':
			Status = EResetStatus::Exit;
			break;
		default:
			// assume the response is invalid - not a number between 1 to 2
			break;
		};
	} while (Status == EResetStatus::Invalid_Status);	// keep looping until we get a valid choice
	std::cout << std::endl;
	return Status;
}

// TODO add ASCII art
void PrintGameSummary()
{
	if (BCGame.IsGameWon()) { std::cout << "WELL DONE - YOU WIN!\n"; }
	else { std::cout << "Better luck next time!\n"; }
}

