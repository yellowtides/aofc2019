#include <stdio.h>
#include <string.h>

#define ll long long
#define MAXVAL 2000000

ll input[MAXVAL];
int mode[10];
int relBase;

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
				scanf("%lld", &val);
				base = relBase*mode[0]/2;
				input[input[i+1]+base] = val;
				i++;
				break;
			case 4:
				printf("%lld ", fetch(input[i+1], mode[0]));
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
	return 0;
}