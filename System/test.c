#include <stdio.h>
#include <string.h>

// a < b ,strcmp(a,b) 返回-1
// a > b ,strcmp(a,b) 返回 1

int main() {
	char a[] = "aaa";
	char b[] = "bbb";
	if(strcmp(a,b)){
		printf("1");
	} else{
		printf("-1");
	}
	return 0;
}