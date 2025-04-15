#include "queue.h"
#include "tile_game.h"
#include <stdio.h>

int checkEqual(struct game_state state, uint8_t goal [4][4])
{
	for(int row = 0; row < 4; row++)
	{
		for(int col = 0; col < 4; col++)
		{
			if(goal[row][col] != state.tiles[row][col])
			{
				return 0;
			}
		}
	}
	return 1;
}
int checkEnd(struct game_state state)
{
	uint8_t goal [4][4] = {{1, 2, 3, 4}, { 5, 6, 7, 8}, {9, 10, 11, 12}, { 13, 14, 15, 0}};
	return checkEqual(state, goal);
}
void printGame(struct game_state state)
{
	printf("=-=-=-=-\n");
	for(int row = 0; row < 4; row++)
	{
		for(int col = 0; col < 4; col++)
		{
			printf("%d ",state.tiles[row][col]);
		}
		printf("\n");
	}
}
void queueChildren(struct queue *q, struct game_state game)
{
	struct game_state temp = game;
	move_up(&temp);
	if(!(game.empty_row == temp.empty_row && game.empty_col == temp.empty_col)){
		enqueue(q, temp);
	}

	temp = game;
	move_down(&temp);
	if(!(game.empty_row == temp.empty_row && game.empty_col == temp.empty_col)){
		enqueue(q, temp);
	}

	temp = game;
	move_left(&temp);
	if(!(game.empty_row == temp.empty_row && game.empty_col == temp.empty_col)){
		enqueue(q, temp);
	}

	temp = game;
	move_right(&temp);
	if(!(game.empty_row == temp.empty_row && game.empty_col == temp.empty_col)){
		enqueue(q, temp);
	}

}

void enqueue(struct queue *q, struct game_state state) {
	insert_at_tail(&(q->data), serialize(state));
}

struct game_state dequeue(struct queue *q) { 
	struct game_state game = deserialize(q->data.head->value);
	//printGame(game);
	remove_from_head(&(q->data));

	return game;      
}

int number_of_moves(struct game_state start) { 
	struct queue q = {.data.head = NULL};
	struct game_state current;
	enqueue(&q, start);
	int numMoves;

	while(q.data.head)
	{
		current = dequeue(&q);
		if(current.empty_row == 3 && current.empty_col == 3 && checkEnd(current)) //check end
		{
			numMoves = current.num_steps;
			free_list(q.data);
			return numMoves;
		} else {
			queueChildren(&q, current);
		}
	}
	return 0; 
}
