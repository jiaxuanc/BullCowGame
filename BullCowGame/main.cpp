/* This is the console executable, that makes use of the FBullCowGame class.
This acts as the view in a MVC pattern, and is responsbile for all user
interaction. For game logic see the FBullCowGame class.
*/


#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;	// instantiate a new game

// the entry point of the application
int main() 
{
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());	// enables the player to play as many times as he/she wants

	return 0;	// exit the application
}


// introduce the game
void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game. \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)	{
	
		FText Guess = GetValidGuess();		

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print number of bulls and cows
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
		std::cout << "Try " << CurrentTries << ". Please enter your guess: ";
		std::getline(std::cin, Guess);	// read through spaces, and discard the input stream once it reaches the new-line character
									// better than std::cin >> Guess, as this will not work properly 
									// if there are spaces between words, like "apple pen"

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);	// keep looping until we get no errors
	return Guess;
}


bool AskToPlayAgain()
{
	std::cout << "Would you like to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);	// TODO check validity of the response
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) { std::cout << "WELL DONE - YOU WIN!\n"; }
	else { std::cout << "Better luck next time!\n"; }
}
