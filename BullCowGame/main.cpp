#include <iostream>
#include <string>
#include "FBullCowGame.h"

void PrintIntro();
void PlayGame();
std::string GetGuess();
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
	constexpr int WORD_LENGTH = 9;
	std::cout << "Welcome to Bulls and Cows, a fun word game. \n";
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	// loop for the number of turns asking for guesses
	int MaxTries = BCGame.GetMaxTries();
	for (int i = 1; i <= MaxTries; i++) {
		std::string Guess = GetGuess();		// TODO check validity of the guess

		// submit valid guess to the game
		// print number of bulls and cows
		// continue the game if guess is wrong within max # of tries
		std::cout << "Your guess was: " << Guess << std::endl;
		std::cout << std::endl;
	}
	
	// TODO summarize game

	return;
}

std::string GetGuess()
{
	int CurrentTries = BCGame.GetCurrentTry();
	// get a guess from the player
	std::cout << "Try "<< CurrentTries << ". Please enter your guess: ";
	std::string Guess = "";
	std::getline(std::cin, Guess);	// read through spaces, and discard the input stream once it reaches the new-line character
								// better than std::cin >> Guess, as this will not work properly 
								// if there are spaces between words, like "apple pen"

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Would you like to play again? (y/n) ";
	std::string Response = "";
	std::getline(std::cin, Response);	// TODO check validity of the response
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
