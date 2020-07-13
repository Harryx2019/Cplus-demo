#include <iostream>
#include <cstdlib>

using namespace std;
enum class GameStatus { WIN, LOSE, PLAYING };

int rollDice()
{
	int die1 = 1 + rand() % 6;
	int die2 = 1 + rand() % 6;
	int sum = die1 + die2;
	cout << "player rolled " << die1 << "+" << die2 << "=" << sum << endl;
	return sum;
}

void playDice()
{
	int sum, myPoint;
	GameStatus status;

	unsigned seed;
	cout << "Please enter an unsigned integer:";
	cin >> seed;
	srand(seed);

	sum = rollDice();
	switch (sum)
	{
	case 7:
	case 11:
		status = GameStatus::WIN;
		break;
	case 2:
	case 3:
	case 12:
		status = GameStatus::LOSE;
		break;
	default:
		status = GameStatus::PLAYING;
		myPoint = sum;
		cout << "point is " << myPoint << endl;
		break;
	}

	while (status == GameStatus::PLAYING)
	{
		sum = rollDice();
		if (sum == myPoint)
			status = GameStatus::WIN;
		else if (sum == 7)
			status = GameStatus::LOSE;
	}

	if (status == GameStatus::WIN)
		cout << "player wins" << endl;
	else
		cout << "player loses" << endl;
}