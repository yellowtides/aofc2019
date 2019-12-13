#include <stdio.h>
#include <string.h>

#define ll long long
#define MAXVAL 200000

int input[MAXVAL];
int mode[10];
	
int fetch(int val, int mode) {
	if (mode) {
		return val;
	}
	return input[val];
}
int max(int x, int y) {
	return (x > y)? x : y;
}

int main() {
	char encInp[MAXVAL];
	scanf("%s", encInp);
	int inpSize = strlen(encInp);
	encInp[inpSize] = ',';
	encInp[++inpSize] = '\0';

	int currVal = 0;
	int n = 0;
	int sign = 1;

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

	int amp[5];
	int results[5];

	int ans = -1;

	for (amp[0] = 0; amp[0] < 5; amp[0]++)
	for (amp[1] = 0; amp[1] < 5; amp[1]++)
	for (amp[2] = 0; amp[2] < 5; amp[2]++)
	for (amp[3] = 0; amp[3] < 5; amp[3]++)
	for (amp[4] = 0; amp[4] < 5; amp[4]++) {
	
		if (amp[0] == amp[1] || amp[0] == amp[2] || amp[0] == amp[3] || amp[0] == amp[4]) continue;
		if (amp[1] == amp[2] || amp[1] == amp[3] || amp[1] == amp[4]) continue;
		if (amp[2] == amp[3] || amp[2] == amp[4]) continue;
		if (amp[3] == amp[4]) continue;

		for (int currAmp = 0; currAmp < 5; currAmp++) {

			int first = 1;

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

				int val;

				switch (input[i]%100) {
					case 99:
						i = n;
						break;
					case 1:
						input[input[i+3]] = fetch(input[i+2], mode[1]) + fetch(input[i+1], mode[0]);
						i += 3;
						break;
					case 2:
						input[input[i+3]] = fetch(input[i+2], mode[1]) * fetch(input[i+1], mode[0]);
						i += 3;
						break;
					case 3:
						if (!first) {
							if (currAmp > 0) {
								input[input[i+1]] = results[currAmp-1];
							}
							else {
								input[input[i+1]] = 0;
							}
						}
						else {
							first = 0;
							input[input[i+1]] = amp[currAmp]; 
						}
						i++;
						break;
					case 4:
						results[currAmp] = fetch(input[i+1], mode[0]);
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
						if (fetch(input[i+1], mode[0]) < fetch(input[i+2], mode[1])) {
							input[input[i+3]] = 1;
						}
						else {
							input[input[i+3]] = 0;
						}
						break;
					case 8:
						if (fetch(input[i+1], mode[0]) == fetch(input[i+2], mode[1])) {
							input[input[i+3]] = 1;
						}
						else {
							input[input[i+3]] = 0;
						}
						break;
					default:
						break;
				}
			}
		}
		ans = max(ans, results[4]);
	}
	printf("%d", ans);
	return 0;
}