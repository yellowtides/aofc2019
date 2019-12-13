#include <stdio.h>
#include <string.h>

#define ll long long
#define MAXVAL 200000

int main() {
	char encInp[MAXVAL];
	scanf("%s", encInp);
	int inpSize = strlen(encInp);
	encInp[inpSize] = ',';
	encInp[++inpSize] = '\0';

	ll input[MAXVAL];
	ll currVal = 0;
	int n = 0;

	for (int i = 0; i < inpSize; i++) {
		if (encInp[i] == ',') {
			input[n++] = currVal;
			currVal = 0;
			continue;
		}
		currVal = currVal*10 + encInp[i] - '0';
	}

	ll aux[MAXVAL];
	for (int i = 0; i < n; i++) {
		aux[i] = input[i];
	}

	for (int noun = 0; noun < 100; noun++)
		for (int verb = 0; verb < 100; verb++) {
		
			for (int i = 0; i < n; i++) {
				input[i] = aux[i];
			}
			
			input[1] = noun;
			input[2] = verb;
			for (int i = 0; i < n; i += 4) {
				switch (input[i]) {
					case 99:
						i = n;
						break;
					case 1:
						input[input[i+3]] = input[input[i+1]] + input[input[i+2]];
						break;
					case 2:
						input[input[i+3]] = input[input[i+1]] * input[input[i+2]];
						break;
					default:
						break;
				}
			}
			if (input[0] == 19690720) {
				printf("%d", 100*noun+verb);
				return 0;
			}
		}

	return 0;
}