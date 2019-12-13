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
				scanf("%d", &val);
				input[input[i+1]] = val;
				i++;
				break;
			case 4:
				printf("%d ", fetch(input[i+1], mode[0]));
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
	return 0;
}