#include <stdlib.h>
#include "rules.h"

Rule *allocate_rule(Rule *rule, int nbStates) {
	rule = (Rule *) malloc(sizeof(Rule));
	rule->nbStates = nbStates;
	rule->colors = (float **) malloc(nbStates*sizeof(float *));
	int i;
	for(i=0;i<nbStates;i++) rule->colors[i] = (float *) malloc(3*sizeof(float));
	return rule;
}

void free_rule(Rule *rule) {
	if(rule == NULL) return;
	int i;
	for(i=0;i<rule->nbStates;i++) free(rule->colors[i]);
	free(rule->colors);
	free(rule);
}
