#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>

/* add elements into the queue */
void enqueue(struct queue *q, struct game_state state) {
	size_t numToAdd = (size_t)serialize(state);
	insert_at_head(&q->data, numToAdd);
}

struct game_state dequeue(struct queue *q) { 
	size_t numToRemove = remove_from_tail(&q->data);
	struct game_state valToCheck = deserialize((uint64_t)numToRemove);
	return valToCheck;
}	

void advance_state(struct game_state *state, struct linked_list *visitedNode, struct queue *q){
	size_t check = (size_t)serialize(*state);
	struct list_node *currNode = visitedNode->head;
	
	// check that the current node is valid
	while(currNode){
		if(currNode->value == check){
			return;
		}
		currNode = currNode->next;	// update the current node
	}
	// add to head
	insert_at_head(visitedNode, check);
	enqueue(q, *state);
}
bool checkState(struct game_state state){
	size_t expected = 1;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(i == 3 && j == 3){
				if(state.tiles[3][3] != 0){
					return false;
				}
			}else{
				if (state.tiles[i][j] != expected++){
					return false;
				}
			}
		}
	}
	return true;
}

bool finalSolve(struct game_state currMove, struct game_state nextMove, struct linked_list *visitedNode, struct queue *q){
        if(nextMove.empty_row != currMove.empty_row || nextMove.empty_col != currMove.empty_col){
                if(checkState(nextMove)){
                        free_list(*visitedNode);
                        free_list(q->data);
                        return true;
                }
        }
        return false;
}

int number_of_moves(struct game_state start) {
	// check initial conditions
	if (checkState(start)){return 0;}
	
	// create the queue
	struct queue q = {.data = {.head = NULL}};
	enqueue(&q, start);

	// start inserting
	struct linked_list visitedNode = {.head = NULL};
	size_t startPoint = (size_t)serialize(start);
	insert_at_head(&visitedNode, startPoint); 

	// while the queue is valid
	while(q.data.head != NULL){
	        // initialize current and next moves
	        struct game_state currMove = dequeue(&q);	// the node we are visiting
	        struct game_state nextMove = currMove;	// the next node we need to 'look at'

		// move up
		move_up(&nextMove);	// update next move
		if(finalSolve(currMove, nextMove, &visitedNode, &q)){return nextMove.num_steps;}
		advance_state(&nextMove, &visitedNode, &q);
		//enqueue(&q, nextMove);

		// move down
		nextMove = currMove;	// update next move
		move_down(&nextMove);
		if(finalSolve(currMove, nextMove, &visitedNode, &q)){return nextMove.num_steps;}
		advance_state(&nextMove, &visitedNode, &q);
		//enqueue(&q, nextMove);
		
		// move left
                nextMove = currMove;	// update next move
                move_left(&nextMove);
                if(finalSolve(currMove, nextMove, &visitedNode, &q)){return nextMove.num_steps;}
                advance_state(&nextMove, &visitedNode, &q);
                //enqueue(&q, nextMove);

		// move right
		nextMove = currMove;	// update next move
		move_right(&nextMove);
		if(finalSolve(currMove, nextMove, &visitedNode, &q)){return nextMove.num_steps;}
		advance_state(&nextMove, &visitedNode, &q);
		//enqueue(&q, nextMove);
	}

	// free if no path is valid
	free_list(visitedNode);
	free_list(q.data);
	return EXIT_FAILURE;
}

