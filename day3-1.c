#include <stdio.h>
#include <string.h>
#include <math.h>

#define ll long long
#define MAXVAL 200000


struct pair {
	int src;
	int dest;
	int index;
} hLines[20001], vLines[20001];


int min(int x, int y) {
	return (x < y)? x : y;
}

int abs(int x) {
	return (x > 0)? x : -x;
}

int main() {

	// FIRST LINE

	char encInp[MAXVAL];
	scanf("%s", encInp);
	int inpSize = strlen(encInp);
	encInp[inpSize] = ',';
	encInp[++inpSize] = '\0';

	char dir;
	int hLinesSize = 0;
	int vLinesSize = 0;
	int currX = 0;
	int currY = 0;
	int currVal = 0;

	for (int i = 0; i < inpSize; i++) {
		if (encInp[i] == ',') {
			// process dir and currVal
			switch (dir) {
				case 'L':
					currX -= currVal;
					hLines[hLinesSize].index = currY;
					hLines[hLinesSize].src = currX;
					hLines[hLinesSize++].dest = currX+currVal;
					break;
				case 'R':
					currX += currVal;
					hLines[hLinesSize].index = currY;
					hLines[hLinesSize].src = currX-currVal;
					hLines[hLinesSize++].dest = currX;
					break;
				case 'U':
					currY += currVal;
					vLines[vLinesSize].index = currX;
					vLines[vLinesSize].src = currY-currVal;
					vLines[vLinesSize++].dest = currY;
					break;
				case 'D':
					currY -= currVal;
					vLines[vLinesSize].index = currX;
					vLines[vLinesSize].src = currY;
					vLines[vLinesSize++].dest = currY+currVal;
					break;
				default:
					break;
			}
			currVal = 0;
			continue;
		}
		if (encInp[i] >= 'A' && encInp[i] <= 'Z') {
			dir = encInp[i];
			continue;
		}
		currVal = currVal*10 + encInp[i] - '0';
	}

	// SECOND LINE

	scanf("%s", encInp);
	inpSize = strlen(encInp);
	encInp[inpSize] = ',';
	encInp[++inpSize] = '\0';

	currX = 0;
	currY = 0;

	int minDist = (int)2e9;

	for (int i = 0; i < inpSize; i++) {
		if (encInp[i] == ',') {
			// process dir and currVal
			switch (dir) {
				case 'L':
					currX -= currVal;
					for (int x = currX; x <= currX+currVal; x++) {
						for (int line = 0; line < vLinesSize; line++) {
							
							if (x != vLines[line].index) continue;
							
							if (currY >= vLines[line].src && currY <= vLines[line].dest) {
								minDist = min(minDist, abs(x)+abs(currY));
								printf("(%d, %d)\n", x, currY);
							}
						}
					}

					break;
				case 'R':
					currX += currVal;
					for (int x = currX-currVal; x <= currX; x++) {
						for (int line = 0; line < vLinesSize; line++) {
							
							if (x != vLines[line].index) continue;
							
							if (currY >= vLines[line].src && currY <= vLines[line].dest) {
								minDist = min(minDist, abs(x)+abs(currY));
								printf("(%d, %d)\n", x, currY);
							}
						}
					}

					break;
				case 'U':
					currY += currVal;
					for (int y = currY-currVal; y <= currY; y++) {
						for (int line = 0; line < hLinesSize; line++) {
							
							if (y != hLines[line].index) continue;
							
							if (currX >= hLines[line].src && currX <= hLines[line].dest) {
								
								if (y == 0 && currX == 0) continue;

								minDist = min(minDist, abs(y)+abs(currX));
								printf("(%d, %d)\n", currX, y);
							}
						}
					}

					break;
				case 'D':
					currY -= currVal;
					for (int y = currY; y <= currY+currVal; y++) {
						for (int line = 0; line < hLinesSize; line++) {
							
							if (y != hLines[line].index) continue;
							
							if (currX >= hLines[line].src && currX <= hLines[line].dest) {
								minDist = min(minDist, abs(y)+abs(currX));
								printf("(%d, %d)\n", currX, y);
							}
						}
					}

					break;
				default:
					break;
			}

			currVal = 0;
			continue;
		}
		if (encInp[i] >= 'A' && encInp[i] <= 'Z') {
			dir = encInp[i];
			continue;
		}
		currVal = currVal*10 + encInp[i] - '0';
	}

	printf("\nmindist: %d\n", minDist);

	return 0;
}