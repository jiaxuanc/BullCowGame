/* This is the console executable, that makes use of the FBullCowGame class
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
	std::cout << "Welcome to Bulls and Cows, a fun word game. \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();

	// loop for the number of turns asking for guesses
	int32 MaxTries = BCGame.GetMaxTries();	 // TODO change from FOR to WHILE loop once we are validating tries
	for (int32 i = 1; i <= MaxTries; i++) {
		FText Guess = GetValidGuess();		

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

		std::cout << std::endl;

		// continue the game if guess is wrong within max # of tries

	}
	
	// TODO summarize game

	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;	
	do {
		// get a guess from the player
		int32 CurrentTries = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTries << ". Please enter your guess: ";
		FText Guess = "";
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
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);	// keep looping until we get no errors
}

bool AskToPlayAgain()
{
	std::cout << "Would you like to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);	// TODO check validity of the response
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
