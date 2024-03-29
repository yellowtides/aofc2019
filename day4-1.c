#include <stdio.h>

int main() {

	int x, y;
	scanf("%d%d", &x, &y);
	
	int ans = 0;

	for (int j = x; j <= y; j++) {
		int isBad = 0;
		int hasDoubles = 0;

		int prevDig = 10;

		int i = j;
		while (i) {
			int dig = i%10;
			if (dig == prevDig) {
				hasDoubles = 1;
			}
			if (dig > prevDig) {
				isBad = 1;
				break;
			}
			prevDig = dig;
			i /= 10;
		}

		if (!isBad && hasDoubles) {
			ans++;
			printf("%d\n", j);
		}
	}

	printf("%d\n", ans);
	return 0;
}