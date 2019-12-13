#include <stdio.h>
#include <string.h>

#define MAXVAL 1000000

int father[MAXVAL];
int nodes[MAXVAL];

struct pair {
	int nodeVal;
	int distFromYou;
} encountered[1001];

int ascend(int val) {
	if (!father[val]) return 0;
	return 1 + ascend(father[val]);
}

int main() {

	char s[10];
	int sSize;
	do  {
	
		scanf("%s", s);
		sSize = strlen(s);
		if (sSize <= 1) break;

		int i = 0;
		int x = 0, y = 0;
		while (s[i] != ')') {
			x = x*100+s[i++];
		}

		i++;
		while (i < sSize) {
			y = y*100+s[i++];
		} 
		
		father[y] = x;
	
	} while (sSize > 1);

	int nNodes = 0;
	
	for (int i = 0; i < MAXVAL; i++) {
		if (father[i]) {
			nodes[nNodes++] = i;
		}
	}

	int start = 897985; // YOU
	int end = 836578; // SAN

	int encounters = 0;
	while (start) {
		encountered[encounters].nodeVal = start;
		if (encounters) {
			encountered[encounters].distFromYou = encountered[encounters-1].distFromYou + 1;
		}
		start = father[start];
		encounters++;
	}

	int ans = 0;
	while (end) {
		for (int i = 0; i < encounters; i++) {
			if (encountered[i].nodeVal == end) {
				ans += encountered[i].distFromYou;
				printf("%d", ans-2);
				return 0;
			}
		}
		end = father[end];
		ans++;
	}

	printf("%d", ans);
	return 0;
}