#include <stdio.h>
#include <string.h>


void logIn();

int main(){
	logIn();
	return 0;
}

/*int main() {
	char account[20];
	char code[20];
	int count = 0;
	while (1) {
		if (count == 3) {
			return 0;
		}
		printf("请输入账号:");
		scanf("%s", account);
		printf("请输入密码:");
		scanf("%s", code);
		if (!strcmp(account, "liyufeng") && !strcmp(code, "lyufeng")) {
			// 进入职工管理系统
			printf("您是合法用户\n");
			printf("即将进入职工管理系统........\n\n");
			staff();
			return 0;
		} else if (!strcmp(account, "XYcsd") && !strcmp(code, "zxy")) {
			// 进入物品管理系统
			printf("您是合法用户\n");
			printf("即将进入物品管理系统........\n\n");
			main_interface();
			return 0;
		} else {
			printf("\033[31m账号密码错误,还剩%d次机会\033[0m\n", 2 - count);
			count++;
		}
	}
}*/

//测试登陆状态
/*int main(){
	int choose;
	str:
	printf("1.职工管理系统\n2.物品管理系统\n");
	scanf("%d",&choose);
	if(choose == 1){
		staff();
	} else if(choose == 2){
		main_interface();
	} else{
		goto str;
	}
}*/
