#include <stdio.h>

#define ll long long

int main() {
	int val;
	ll ans = 0;
	do {
		scanf("%d", &val);
		if (val == -1) {
			break;
		}

		// solution
		ans -= val;

		while (val >= 0) {
			ans += val;
			val = val/3-2;
		}

	} while (1);

	printf("%lld", ans);

	return 0;
}