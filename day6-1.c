#include <stdio.h>
#include <string.h>

#define MAXVAL 1000000

int father[MAXVAL];
int nodes[MAXVAL];

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

	int ans = 0;

	for (int i = 0; i < nNodes; i++) {
		ans += ascend(nodes[i]);
	}

	printf("%d", ans);
	return 0;
}