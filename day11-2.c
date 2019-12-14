#include <stdio.h>
#include <string.h>

#define ll long long
#define MAXVAL 2000000
#define MAXVAL2 100

ll input[MAXVAL];
int mode[10];
int relBase;

struct pair {
	int x;
	int y;
	int color;
} visited[MAXVAL];
int visitedSize;

int currX = 50, currY = 50;
int indexInVisited;
int dir;

char map[MAXVAL2][MAXVAL2];

int firstOutp = 1;

ll fetch(ll val, int mode) {
	if (mode == 1) {
		return val;
	}
	if (mode == 2) {
		return input[relBase+val];
	}
	return input[val];
}

int main() {

	for (int i = 0; i < MAXVAL2; i++) 
		for (int j = 0; j < MAXVAL2; j++) {
			map[i][j] = '.';
		}

	char encInp[MAXVAL];
	scanf("%s", encInp);
	int inpSize = strlen(encInp);
	encInp[inpSize] = ',';
	encInp[++inpSize] = '\0';

	ll currVal = 0;
	int n = 0;
	ll sign = 1;

	for (int i = 0; i < inpSize; i++) {
		if (encInp[i] == ',') {
			input[n++] = currVal*sign;
			currVal = 0;
			sign = 1;
			continue;
		}
		if (encInp[i] == '-') {
			sign = -1;
			continue;
		}
		currVal = currVal*10 + encInp[i] - '0';
	}
	
	for (int i = 0; i < n; i++) {

		for (int modeInd = 0; modeInd <= 9; modeInd++) {
			mode[modeInd] = 0;
		}

		int modeNumber = 0;
		int modeString = input[i]/100;
		
		while (modeString) {
			mode[modeNumber++] = modeString%10;
			modeString /= 10;
		}

		ll val;
		ll base = 0;
		int isVisited = 0;

		switch (input[i]%100) {
			case 99:
				i = n;
				break;
			case 1:
				base = relBase*mode[2]/2;
				input[input[i+3]+base] = fetch(input[i+2], mode[1]) + fetch(input[i+1], mode[0]);
				i += 3;
				break;
			case 2:
				base = relBase*mode[2]/2; 
				input[input[i+3]+base] = fetch(input[i+2], mode[1]) * fetch(input[i+1], mode[0]);
				i += 3;
				break;
			case 3:

				for (int v = 0; v < visitedSize; v++) {
					if (visited[v].x == currX && visited[v].y == currY) {
						indexInVisited = v;
						val = visited[v].color;

						isVisited = 1;
						break;
					}
				}
				if (!isVisited) {
					indexInVisited = visitedSize;
					visited[visitedSize].x = currX;
					visited[visitedSize++].y = currY;
					val = 0;
					if (visitedSize == 1) {
						val = 1;
					}
				}

				base = relBase*mode[0]/2;
				input[input[i+1]+base] = val;
				i++;
				break;
			case 4:

				if (firstOutp) {
					visited[indexInVisited].color = fetch(input[i+1], mode[0]);
					map[visited[indexInVisited].x][visited[indexInVisited].y] = (char) ('0'+fetch(input[i+1], mode[0]));
					firstOutp = 0;
				}
				else {
					if (fetch(input[i+1], mode[0])) {
						dir = (dir+1)%4;
					}
					else {
						dir = (dir-1)%4;
						if (dir < 0) dir += 4;
					}
					switch (dir) {
						case 0: 
							currY++;
							break;
						case 1: 
							currX++;
							break;
						case 2: 
							currY--;
							break;
						case 3: 
							currX--;
							break;
						default:
							break;
					}
					firstOutp = 1;
				}
				i++;
				break;
			case 5:
				if (fetch(input[i+1], mode[0])) {
					i = fetch(input[i+2], mode[1])-1;
				}
				else {
					i += 2;
				}
				break;
			case 6:
				if (!fetch(input[i+1], mode[0])) {
					i = fetch(input[i+2], mode[1])-1;
				}
				else {
					i += 2;
				}
				break;
			case 7:
				base = relBase*mode[2]/2;
				if (fetch(input[i+1], mode[0]) < fetch(input[i+2], mode[1])) {
					input[input[i+3]+base] = 1;
				}
				else {
					input[input[i+3]+base] = 0;
				}
				i += 3;
				break;
			case 8:
				base = relBase*mode[2]/2;
				if (fetch(input[i+1], mode[0]) == fetch(input[i+2], mode[1])) {
					input[input[i+3]+base] = 1;
				}
				else {
					input[input[i+3]+base] = 0;
				}
				i += 3;
				break;
			case 9:
				relBase += fetch(input[i+1], mode[0]);
				i++;
				break;
			default:
				break;
		}
	}

	for (int i = MAXVAL2-1; i >= 0; i--) {
		for (int j = 0; j < MAXVAL2; j++) {
			if (map[j][i] == '1') printf("%c", '#');
			else printf("%s", " ");
		}
		printf("\n");
	}
	return 0;
}