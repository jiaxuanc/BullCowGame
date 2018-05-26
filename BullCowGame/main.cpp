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
void PlayGame(EResetStatus);
FText GetValidGuess();
EResetStatus AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;	// instantiate a new game, which we re-use across plays

// the entry point of the application
int main() 
{	
	PrintIntro();
	EResetStatus eReset = EResetStatus::Init_Hidden_Word;
	do {
		// TODO add a function to choose difficulty level etc
		PlayGame(eReset);
		eReset = AskToPlayAgain();
	} while ( eReset != EResetStatus::Exit);	// enables the player to play as many times as he/she wants with same or different words

	return 0;									// exit the application
}

// TODO add more instructions and ASCII art
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
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame(EResetStatus eResetStatus)
{
	BCGame.Reset(eResetStatus);
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
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. (¨s¡ã¡õ¡ã£©¨s¦à ©ß©¥©ß \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. (¨s¡ã¡õ¡ã£©¨s¦à ©ß©¥©ß\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. (¨s¡ã¡õ¡ã£©¨s¦à ©ß©¥©ß\n\n";
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
	std::cout << "\nWould you like to play again? Three options: \n";
	std::cout << "  1 = Yes, I want to play with the same word again.\n";
	std::cout << "  2 = Yes, but I want to play with a different word. \n";
	std::cout << "  3 = No, I want to quit. \n";
	EResetStatus Status = EResetStatus::Invalid_Status;
	FText Response = "";

	do {
		std::cout << "Please enter your choice out of the three options (1-3): ";
		std::getline(std::cin, Response);
		
		switch (Response[0])
		{
		case '1':
			Status = EResetStatus::Same_Hidden_Word;
			break;
		case '2':
			Status = EResetStatus::Diff_Hidden_Word;
			break;
		case '3':
			Status = EResetStatus::Exit;
			break;
		default:
			// assume the response is invalid - not a number between 1 to 3
			break;
		};
	} while (Status == EResetStatus::Invalid_Status);	// keep looping until we get a valid choice
	return Status;
}

// TODO add ASCII art
void PrintGameSummary()
{
	if (BCGame.IsGameWon()) { std::cout << "WELL DONE - YOU WIN!\n"; }
	else { std::cout << "Better luck next time!\n"; }
}

