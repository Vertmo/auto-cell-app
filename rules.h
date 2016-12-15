#ifndef _RULES_H_
#define _RULES_H_

typedef struct {
	int nbStates;
	float **colors;
} Rule;

Rule *allocate_rule(Rule *rule, int nbStates);

void free_rule(Rule *rule);

void free_world(int **world, int SIZE_X, int SIZE_Y);

int **conway(int **world, int SIZE_X, int SIZE_Y);

#endif
