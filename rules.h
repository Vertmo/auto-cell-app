#ifndef _RULES_H_
#define _RULES_H_

typedef struct {
	int nbStates;
	float **colors;
} Rule;

Rule *allocate_rule(Rule *rule, int nbStates);

void free_rule(Rule *rule);

void conway();

#endif
