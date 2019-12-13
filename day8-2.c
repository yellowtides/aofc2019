#include <stdio.h>
#include <string.h>

#define ll long long
#define MAXVAL 200000

char ans[301];

int main() {

	freopen("day8input.txt", "r", stdin);

	char input[MAXVAL];
	fgets(input, MAXVAL, stdin);

	int inpSize = strlen(input);

	int area = 25*6;

	for (int i = 0; i < inpSize; i++) {
		if (input[i] != '2' && !ans[i%area]) {
			ans[i%area] = input[i];
		}
	}
	for (int i = 0; i < area; i++) {
		if (!ans[i]) {
			ans[i] = '2';
		}
		if (i%25 == 0) {
			printf("\n");
		}
		switch (ans[i]) {
			case '1':
				printf("%c", '0');
				break;
			default:
				printf(" ");
				break;
		}
	}

	return 0;
}