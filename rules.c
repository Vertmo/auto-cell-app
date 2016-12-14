#include <stdlib.h>
#include <stdio.h>
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

int **copyWorld(int **world, int SIZE_X, int SIZE_Y) {
	int i; int j;
	int **newWorld = (int **) malloc(SIZE_Y*sizeof(int *));
	for(i=0;i<SIZE_Y;i++) {
		newWorld[i] = (int *) malloc(SIZE_X*sizeof(int));
		for(j=0;j<SIZE_X;j++) {
			newWorld[i][j] = world[i][j];
		}
	}
	return newWorld;
}

void freeWorld(int **world, int SIZE_X, int SIZE_Y) {
	if(world == NULL) return;
	int i;
	for(i=0;i<SIZE_Y;i++) free(world[i]);
	free(world);
}

int **conway(int **world, int SIZE_X, int SIZE_Y) {
	int **newWorld = copyWorld(world, SIZE_X, SIZE_Y);
	int i; int j; int left; int right; int top; int bottom; int sum;
	for(i=0;i<SIZE_Y;i++) {
		for(j=0;j<SIZE_X;j++) {
			if(j>0) left = j-1; else left = SIZE_X-1;
			if(j<SIZE_X-1) right = j+1; else right = 0;
			if(i>0) top = i-1; else top = SIZE_Y-1;
			if(i<SIZE_Y-1) bottom = i+1; else bottom = 0;
			sum = world[top][left] + world[top][j] + world[top][right] + world[i][left] + world[i][right] + world[bottom][left] + world[bottom][j] + world[bottom][right];
			if(world[i][j] == 1) {
				if(sum == 2 || sum == 3) newWorld[i][j] = 1;
				else newWorld[i][j] = 0;
			} else {
				if(sum==3) newWorld[i][j] = 1;
				else newWorld[i][j] = 0;
			}
		}
	}
	freeWorld(world, SIZE_X, SIZE_Y);
	return newWorld;
}
