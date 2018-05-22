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
	} while (AskToPlayAgain());

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

	// loop for the number of turns asking for guesses
	int MaxTries = BCGame.GetMaxTries();
	for (int i = 1; i <= MaxTries; i++) {
		std::string Guess = GetGuess();
		std::cout << "Your guess was: " << Guess << std::endl;
		std::cout << std::endl;
	}

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
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
