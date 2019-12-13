#include <stdio.h>
#include <string.h>

#define ll long long
#define MAXVAL 200000

int main() {
	char input[MAXVAL];
	int ones = 0, twos = 0, zeroes = 0;
	int minZeroes = (int) 2e9;

	scanf("%s", input);
	int inpSize = strlen(input);

	int area = 25*6;
	int ans = 0;

	for (int i = 0; i <= inpSize; i++) {
		if (i > 0 && i%area == 0) {
			if (zeroes < minZeroes) {
				minZeroes = zeroes;
				ans = ones*twos;
			}
			ones = 0;
			twos = 0;
			zeroes = 0;
		}
		switch (input[i]) {
			case '1':
				ones++;
				break;
			case '2':
				twos++;
				break;
			case '0':
				zeroes++;
				break;
			default:
				break;
		}
	}
	printf("%d\n", ans);
	return 0;
}