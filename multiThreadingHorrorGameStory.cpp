/*
Travieon Fields
Assignment 4.1 Horror Story with MultiTreading

I Wanted to make a choose your own adventure with using multiThread

*/


//Liberies
#include <iostream>
#include <string>
#include <thread>
//This on is for the "wait" function i use to slow the text 
#include<Windows.h>
#include<time.h>

using namespace std;



int gameloopChecker();
//this is for pausing the game before choices 
int pauseForEffect(int timeForPausing);
//Function for checking the players choices
int ChoicePlayerMade(char playerChoice);
//Monster Choice
int MonsterNumberChoice();

//Checking if monster found player
bool didMonsterFindPlayer();

//Writting a gameover Text Box
string GameOver(string playerDeadName);

// Made players choice a global varible so i could use it to in different methods
//Set the player choice to 10 so that it isn't The Same as the monsters in the begining of the game
int playerChoiceIntForm = 10;
//Players Name
string playerName;
//Monster choice And if it found the player
int monstersChoice;
//Makes the story go up based on if the monster finds you
int progressStory;
char playerChoice;
bool storyFinished = false;

//A  way to set the text for output by geting the handle and setting it to h
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

//Main interctions
int main()
{
	
	
	while (monstersChoice != playerChoiceIntForm && storyFinished == false)
	{
		if (storyFinished == false)
		{

			//Checks to see if the monster found you or not

			//Check to see if you get a game over.

			gameloopChecker();
			//Runs The Monster choice As well as The players Choice
			thread monsterNumber(MonsterNumberChoice);
			//This is the players Choice code Ran at the same time as the Monsters
			thread playersOptionChoice(ChoicePlayerMade, playerChoice);
			SetConsoleTextAttribute(h, 4);


			monsterNumber.join();
			playersOptionChoice.join();

			didMonsterFindPlayer();
		}
		else {
			
			break;
		}
		
	}
	return 0;
}


int gameloopChecker() {

	switch (progressStory)
	{
	case 0:
	{
		// Sets up the Choice game and makes the player put there name
		SetConsoleTextAttribute(h, 2);
		cout << "You wake up in a very dark room You can't remember Anything" << endl;
		//Pauses for effect are spread out in the code.
		pauseForEffect(3);
		cout << "something seems to be written on your hand. It says Remember your name is. . (Please Enter Your players Name) ";
		//Sets name to whatever player typed
		cin >> playerName;

		pauseForEffect(2);
		cout << "Thats right! your name is " + playerName << endl;
		pauseForEffect(2);
		cout << "As you look around you can barely make out a frame of a door." << endl;
		pauseForEffect(2);
		cout << "As you get close to the door you can hear a faint whisper. . ." << endl;
		pauseForEffect(2);
		SetConsoleTextAttribute(h, 4);
		cout << playerName + " . . . .  " + playerName + " . . . . its ok . . .Im here.  .help you. ." + playerName << endl;
		pauseForEffect(2);
		//Sets up players first choice
		SetConsoleTextAttribute(h, 6);
		cout << "What will you do?" << endl;
		cout << "A) Swing open the door and Make a Run for it as fast as you can" << endl;
		cout << "B) wait for the whispers to fade and slowly open the door, and sneak your way around" << endl;
		cin >> playerChoice;

		
	}
	break;

	case 1:
	{
		SetConsoleTextAttribute(h, 2);
		cout << "That was a close call" << endl;
		pauseForEffect(2);
		cout << "You continue down the hall." << endl;
		pauseForEffect(2);
		cout << "Every step you take you almost feel like you are being watch or maybe even . . ." << endl;
		pauseForEffect(2);
		SetConsoleTextAttribute(h, 4);
		cout << "Followed . . ." << endl;
		pauseForEffect(2);
		SetConsoleTextAttribute(h, 2);
		cout << "You make it to the kicthen, the smell is unbearable, however. . ." << endl;
		pauseForEffect(2);
		SetConsoleTextAttribute(h, 4);
		cout << "You can hear something down the hall heading its way towards you." << endl;
		pauseForEffect(3);

		SetConsoleTextAttribute(h, 6);
		cout << "You Need To hide" << endl;
		cout << "A) Hide under the table and try not to make a sound" << endl;
		cout << "B) Get in the cabinet And leave some room to peep out" << endl;
		cin >> playerChoice;
	}
	break;
	case 2:
	{
		pauseForEffect(2);
		SetConsoleTextAttribute(h, 2);
		cout << "You can't believe what you see. . ." << endl;
		SetConsoleTextAttribute(h, 4);
		pauseForEffect(2);
		cout << "Its you. . But that cant be right . . cause you are you!. . .arent you?" << endl;
		pauseForEffect(2);
		cout << "it scans the room and gurgles out" << endl;
		pauseForEffect(3);
		cout << playerName + " y . . .ou. .u " + playerName + " . . h . . ide . . .Im here. . .to  .help me. ." + playerName << endl;

		SetConsoleTextAttribute(h, 6);
		cout << "You can see The backdoor the creature's Back is Turned away from you." << endl;
		cout << "A) Try to knock the monster down And race out the Backdoor" << endl;
		cout << "B) Sneak out as quietly as you can, dont make A SOUND." << endl;
		cin >> playerChoice;
	}
	break;






	default:
	{
		pauseForEffect(3);
		SetConsoleTextAttribute(h, 2);
		cout << "You never ran so fast in your life. . . ." << endl;
		pauseForEffect(2);
		cout << "You had to have ran for hours. when you made it to a police station. ." << endl;
		pauseForEffect(2);
		cout << "You explain everything that happen. hysterical couldn't begin to describe your words" << endl;
		SetConsoleTextAttribute(h, 4);
		pauseForEffect(2);
		cout << "The look on the faces say they don't believe you" << endl;
		SetConsoleTextAttribute(h, 2);
		pauseForEffect(2);
		cout << " but You know what you saw or rather" << endl;
		SetConsoleTextAttribute(h, 4);
		pauseForEffect(2);
		cout << "You know who you saw. . . . . ." << endl;
		SetConsoleTextAttribute(h, 9);
		pauseForEffect(2);
		cout << "End" << endl;
		storyFinished = true;
		cout << "Thank you for playing!" << endl;
	}
		break;
	}
	
	
	return 0;
}








//Called every choice yoou make
bool didMonsterFindPlayer() {
	


	//Check to see if the monster and player have the same number. if basically The game is over.
	if (monstersChoice == playerChoiceIntForm)
	{
		pauseForEffect(2);
		//Player is dead and you get a gameover runs a function.
		GameOver(playerName);
		return 0;
	}
	else if (monstersChoice != playerChoiceIntForm)
	{
		//Mainly build atmosphere
		pauseForEffect(3);
		progressStory++;
	}
	return 0;
}


//Function to call a wait. to break up the text.
int pauseForEffect(int timeForPausing)
{

	//Basically use to convert the time into Seconds of waiting instead of miliseconds
	timeForPausing = timeForPausing * 1000;
	//Sets the time to wait for.
	Sleep(timeForPausing);
	return 0;
}
//Makes the monster Choose A number at random
int MonsterNumberChoice(){
	srand(time(0));

	// The monster has a 25% chance to get you.
	monstersChoice = rand() % 4;
	cout << monstersChoice << endl;


	return 0;
}

//Checks to see if the input was valid
int ChoicePlayerMade(char playerChoiceChecker)
{
	//Use to make sure players choice is valid
	bool isPlayerChoiceValid = false;




	//A loop to make sure the player enters A or B. nothing else is accepted
	while (!isPlayerChoiceValid)
	{
		playerChoiceChecker = toupper(playerChoiceChecker);
		if (playerChoiceChecker == 'A')
		{

			isPlayerChoiceValid = true;
			//Changes your choice to a number and will be use to check against monster RNG
			playerChoiceIntForm = 0;
		}
		else if (playerChoiceChecker == 'B')
		{

			isPlayerChoiceValid = true;
			playerChoiceIntForm = 1;
		}
		else {
			cout << "Not a valid response!" << endl;
			cin >> playerChoiceChecker;
		}
	}

	return 0;
}


//This is called to end game
string GameOver(string playerDeadName) {

	cout << " The monster found you, it took your name and your life. or should I say " + playerDeadName + " Killed you!" << endl;

	return playerDeadName;
}