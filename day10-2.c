#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ll long long
#define MAXVAL 200
#define MAXVAL2 40000
#define INF 2e11
#define EPS 1e-5

struct coords {
	int x;
	int y;
} astLoc[MAXVAL2];

char map[MAXVAL][MAXVAL];
struct segm {
	int pos;
	double slope;
} slopes[MAXVAL2];

int max(int x, int y) {
	return (x > y)? x : y;
}

double abso(double x) {
	return (x > 0)? x : -x;
}

int cmpDesc(const void* a, const void* b) {
  return (*(double*)a > *(double*)b)? -1 : ((*(double*)a < *(double*)b)? 1 : 0);
}
int cmpAsc(const void* a, const void* b) {
  return (*(double*)a > *(double*)b)? 1 : ((*(double*)a < *(double*)b)? -1 : 0);
}

int main() {
	int noAst = 0;
	int mapSize = 0;
	do {
		scanf("%s", map[mapSize]);
		
		int rowSize = strlen(map[mapSize]);
		if (rowSize <= 1) {
			break;
		}
		
		for (int i = 0; i < rowSize; i++) {
			if (map[mapSize][i] == '#') {
				astLoc[noAst].x = i;
				astLoc[noAst++].y = mapSize;
			}
		}

		mapSize++;
	
	} while (1);

	int focus = 311; // monitoring point

	for (int i = 0; i < noAst; i++) {
		astLoc[i].y = mapSize - astLoc[i].y - 1;
	}

	// int focus = 205;

	double firstQuad[MAXVAL2];
	double secondQuad[MAXVAL2];
	double thirdQuad[MAXVAL2];
	double fourthQuad[MAXVAL2];
	int fiQS = 0, sQS = 0, tQS = 0, foQS = 0;


	for (int other = 0; other < noAst; other++) {

		if (other == focus) {
			continue;
		}

		int currPos;
		if (astLoc[focus].y < astLoc[other].y) {
			currPos = 1;
		}
		else if (astLoc[focus].y > astLoc[other].y) {
			currPos = 0;
		}
		else {
			if (astLoc[focus].x < astLoc[other].x) {
				currPos = 1;
			}
			else {
				currPos = 0;
			}
		}

		double currSlope;
		if (astLoc[other].x == astLoc[focus].x) {
			currSlope = INF;
		}
		else {
			currSlope = (astLoc[other].y-astLoc[focus].y+0.0)/(astLoc[other].x-astLoc[focus].x+0.0);
			if (abso(currSlope) < EPS) currSlope = 0;
		}

		if ((currSlope >= 0) && currPos == 1) {
			firstQuad[fiQS++] = currSlope;
		}
		if ((currSlope < 0) && currPos == 0) {
			secondQuad[sQS++] = currSlope;
		}
		if ((currSlope >= 0) && currPos == 0) {
			thirdQuad[tQS++] = currSlope;
		}
		if ((currSlope < 0) && currPos == 1) {
			fourthQuad[foQS++] = currSlope;
		}


	}

	qsort(firstQuad, fiQS, sizeof(double), cmpDesc);
	qsort(secondQuad, sQS, sizeof(double), cmpDesc);
	qsort(thirdQuad, tQS, sizeof(double), cmpDesc);
	qsort(fourthQuad, foQS, sizeof(double), cmpDesc);

	double combined[MAXVAL2];
	int cSize = 0;

	for (int i = 0; i < fiQS; i++) {
		combined[cSize++] = firstQuad[i];
	}
	for (int i = 0; i < sQS; i++) {
		combined[cSize++] = secondQuad[i];
	}
	for (int i = 0; i < tQS; i++) {
		combined[cSize++] = thirdQuad[i];
	}
	for (int i = 0; i < foQS; i++) {
		combined[cSize++] = fourthQuad[i];
	}

	int destroyed = 0;
	double magicSlope = 0;
	for (int i = 0; i < cSize; i = (i+1)%cSize) {
		while (i < cSize-1 && abso(combined[i]-combined[i+1]) < EPS) {
			i++;
		}
		if (abso(combined[i]-2*INF) < EPS) {
			continue;
		}
		destroyed++;
		if (destroyed == 200) {
			magicSlope = combined[i];
			break;
		}
		combined[i] = 2*INF;
	}

	for (int other = 0; other < noAst; other++) {

		if (other == focus) continue;

		double currSlope;
		if (astLoc[other].x == astLoc[focus].x) {
			currSlope = INF;
		}
		else {
			currSlope = (astLoc[other].y-astLoc[focus].y+0.0)/(astLoc[other].x-astLoc[focus].x+0.0);
		}

		if (abso(currSlope-magicSlope) < EPS) {
			printf("\n(%d, %d)", astLoc[other].x, mapSize-1-astLoc[other].y);
		}
	}

	printf("\n");
	
	return 0;
}