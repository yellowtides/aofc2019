#include <stdio.h>
#include <string.h>

#define ll long long
#define MAXVAL 200
#define INF 2e12
#define EPS 1e-5

struct coords {
	int x;
	int y;
} astLoc[40000];

char map[MAXVAL][MAXVAL];
struct segm {
	int pos;
	double slope;
} slopes[40000];

int max(int x, int y) {
	return (x > y)? x : y;
}

double abso(double x) {
	return (x > 0)? x : -x;
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

	int maxAst = -1;
	int mFocus = -1;

	for (int focus = 0; focus < noAst; focus++) {

		int currVisible = 0;

		for (int other = 0; other < noAst; other++) {

			int isChecked = 0;
			int currPos;
			if (astLoc[focus].y > astLoc[other].y) {
				currPos = 1;
			}
			else if (astLoc[focus].y < astLoc[other].y) {
				currPos = 0;
			}
			else {
				if (astLoc[focus].x > astLoc[other].x) {
					currPos = 1;
				}
				else {
					currPos = 0;
				}
			}

			if (focus == other) {
				continue;
			}

			double currSlope;
			if (astLoc[other].x == astLoc[focus].x) {
				currSlope = INF;
			}
			else {
				currSlope = (astLoc[other].y-astLoc[focus].y+0.0)/(astLoc[other].x-astLoc[focus].x+0.0);
			}

			for (int i = 0; i < other; i++) {

				if (i == focus) {
					continue;
				}

				if ((abso(slopes[i].slope-currSlope) < EPS) && slopes[i].pos == currPos) {
					isChecked = 1;
				}
			}

			slopes[other].slope = currSlope;
			slopes[other].pos = currPos;

			if (!isChecked) currVisible++;
		}

		if (maxAst < currVisible) {
			maxAst = currVisible;
			mFocus = focus;
		}
	}

	printf("%d", mFocus);
	return 0;
}