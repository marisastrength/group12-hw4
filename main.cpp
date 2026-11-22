#include <iostream>
#include "bowling_frame.h"
#include <random>


using namespace std;

std::random_device dev_main;
std::mt19937 rng_main(dev_main());

int current_game_total(Bowling_Frame * first_frame)
{
	Bowling_Frame * temp = first_frame;
	int game_total = 0;
	int temp_total = 0;
	while(temp)
	{
		game_total += temp->frame_score();
		temp = temp->next_frame();
	}
	return game_total;	
}
// argc counts command line arguments
// argv stors the arguments
int main(int argc, char * argv[])
{
	// checks if the user entered the number of players
	if (argc < 2)
	{
		cout<< "Usage: " << argv[0] << " <num_players>" << endl;
		return 1;
	}
	// converts command line argument into a number
	int num_players = stod(argv[1]);

	// checks if number of players is greater than zero
	if (num_players <= 0)
	{
		cout << "Error: Number of players must be greater than 0." << endl;
		return 1;
	}
	//make frames

	// hold each players first name
	Bowling_Frame ** players = new Bowling_Frame * [num_players];
	// initializes each pointer
	for (int i = 0; i < num_players; i++)
	{
		players[i] = nullptr;
	}

	// go through each player and create 10 bolwing farmes
	for(int i = 0; i< num_players; i++)
	{
		// create first bowling frame
		Bowling_Frame * first_frame = new Bowling_Frame(1);

		// store first frame in array position
		players[i] = first_frame;

		Bowling_Frame * previous = first_frame;

		// frames 2 through 10
		for (int j = 2; j <= 10; j++)
		{
			Bowling_Frame * current = new Bowling_Frame(j);
			previous -> next_frame(current);
			current -> prev_frame(previous);
			previous = current;
		}
	
	}

	// go through each player and make their bowling scores
	for (int i =0; i < num_players; i++)
	{
		// moves through the linked frames as rolls are completed
		for (int j =0; j< 20; j++)
		{
			players[i]->update_scores();
		}
	}

	for(int i = 0; i< num_players; i++)
	{
		cout << "Player " << i + 1 << ":" << endl;
		Bowling_Frame * traverse = players[i];

		// goe through all frames in the list
		while(traverse) 
		{
			cout << "Frame " << traverse ->frame_num() << ":" << endl;
			cout << " Score 1: " << traverse->score1() << endl;
			cout << " Score 2: " << traverse->score2()<<endl;

			traverse = traverse ->next_frame();
		}
		// calculates final score
		cout<< "Game Total: " << current_game_total(players[i]) <<endl;
		cout << endl;
	}

}
