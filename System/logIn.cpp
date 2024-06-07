#include "logIn.h"

using namespace std;

extern "C" void staff();
extern "C" void main_interface();

void logIn() {
	char choose;
	bool flag = true;
	while (flag) {
		cout << "1.登陆管理员账号\n2.登陆普通账号\n" << endl;
		printf("请进行操作:");
		cin >> choose;
		fflush(stdin);
		switch (choose) {
			case '1':
				flag = link_to_admin();
				break;
			case '2':
				flag = link_to_user();
				break;
			default:
				cout << "\033[01;31m输入错误\033[0m" << endl;
				break;
		}
	}
}

bool link_to_admin() {
	int choose;
	string input_account;
	string input_code;
	string account = "admin";
	string code = "permitted";
	for (int i = 0; i < 3; i++) {
		color(33);
		cout << "请输入账号:";
		cin >> input_account;
		cout << "请输入密码:";
		cin >> input_code;
		if (input_account == account && input_code == code) {
			cout << "\033[34m登陆成功\033[0m" << endl;
			i = 100;
			color(34);
			cout << "1.进入管理系统\n2.账号权限管理" << endl;
			cout << "请选择要执行的操作:";
			cin >> choose;
			if (choose == 1) {
				here:
				color(0);
				cout << "\n1.职工管理系统\n2.物品管理系统" << endl;
				cout << "请选择要进入的系统:";
				cin >> choose;
				if (choose == 1) {
					staff();
				} else if (choose == 2) {
					main_interface();
				} else {
					cout << "输入错误" << endl;
					goto here;
				}
			} else if (choose == 2) {
				permissions();
				return true;
			}
		} else {
			cout << "\033[01;31m账号或密码错误，请重新输入\n您还剩" << 2 - i << "次机会\033[0m" << endl;
		}
	}
	return false;
}

void registe() {
	string input;
	user u;
	int a;
	FILE *fp = fopen("user.txt", "a+");
	label:
	cout << "请选择账号权限\n1.职工管理\n2.物品管理\n" << endl;
	cin >> a;
	if (a == 1) {
		u.set_status(0);
	} else if (a == 2) {
		u.set_status(1);
	} else {
		cout << "输入错误" << endl;
		goto label;
	}
	cout << "请输入账号:";
	cin >> input;
	u.set_account(input);
	cout << "请输入密码:";
	cin >> input;
	u.set_code(input);
	cout << "账号:" << u.get_account() << "\n密码:" << u.get_code() << endl;
	if (u.get_status() == 0) {
		cout << "权限：职工管理" << endl;
	} else {
		cout << "权限：物品管理" << endl;
	}
	cout << "注册完成" << endl;
	fwrite(&u, sizeof(user), 1, fp);
	fclose(fp);
	return;
}

bool link_to_user() {
	int status;
	int count = caculate();
	user *u = new user[count * sizeof(user)];
	string input_account;
	string input_code;
	FILE *fp = fopen("user.txt", "r");
	if (!fp) {
		cout << "\033[01;31m请先创建账号\033[0m" << endl;
		return true;
	}
	for (int i = 0; i < count; i++) {
		fread(&u[i], sizeof(user), 1, fp);
	}
	fclose(fp);
	for (int i = 0; i < 3; i++) {
		cout << "请输入账号:";
		cin >> input_account;
		cout << "请输入密码:";
		cin >> input_code;
		if (input_account == u[i].get_account() && input_code == u[i].get_code()) {
			status = u[i].get_status();
			delete[] u;
			if (status == 0) {
				staff();
				break;
			} else{
				main_interface();
				break;
			}
		} else{
			cout << "\033[01;31m账号或密码错误，请重新输入\n您还剩" << 2 - i << "次机会\033[0m" << endl;
		}
		
	}
	return false;
}

void permissions() {
	char choose;
	while (1) {
		color(0);
		cout << "1.显示所有账号\t2.账号权限设置\n3.删除账号\t\t4.添加账号\n5.返回" << endl;
		cin >> choose;
		fflush(stdin);
		switch (choose) {
			case '1':
				show_all_account();
				break;
			case '2':
				set_permissions();
				break;
			case '3':
				delete_account();
				break;
			case '4':
				registe();
				break;
			case '5':
				return;
			default:
				color(31);
				cout << "输入错误" << endl;
				color(0);
				break;
		}
	}
}

void show_all_account() {
	user u;
	FILE *fp = fopen("user.txt", "r");
	cout << "\033[34m";
	while (fread(&u, sizeof(user), 1, fp)) {
		cout << "账号:" << u.get_account() << "\n密码:" << u.get_code() << endl;
		if (u.get_status() == 0) {
			cout << "权限：职工管理\n" << endl;
		} else {
			cout << "权限：物品管理\n" << endl;
		}
	}
	cout << "\033[0m";
	fclose(fp);
}

void set_permissions() {
	user u;
	string input;
	int a;
	FILE *fp = fopen("user.txt", "r+");
	cout << "请输入要设置权限的账号:";
	cin >> input;
	while (fread(&u, sizeof(user), 1, fp)) {
		if (u.get_account() == input) {
			cout << "请选择账号权限\n1.职工管理\n2.物品管理\n" << endl;
			cin >> a;
			if (a == 1) {
				u.set_status(0);
			} else if (a == 2) {
				u.set_status(1);
			} else {
				cout << "输入错误" << endl;
				return;
			}
			fseek(fp, -sizeof(user), SEEK_CUR);
			fwrite(&u, sizeof(user), 1, fp);
			cout << "设置成功" << endl;
			fclose(fp);
			return;
		}
	}
}

void delete_account() {
	string input;
	user u;
	FILE *fp = fopen("user.txt", "r+");
	FILE *fp1 = fopen("temp.txt", "w+");
	cout << "请输入要删除的账号:";
	cin >> input;
	while (fread(&u, sizeof(user), 1, fp)) {
		if (u.get_account() == input) {
			continue;
		}
		fwrite(&u, sizeof(user), 1, fp1);
	}
	fclose(fp);
	fclose(fp1);
	remove("user.txt");
	rename("temp.txt", "user.txt");
	cout << "删除成功" << endl;
}

void color(int c) {
	printf("\033[%dm", c);
}

int caculate() {
	user u;
	int count = 0;
	FILE *fp = fopen("user.txt", "r");
	while (fread(&u, sizeof(user), 1, fp)) {
		count++;
	}
	fclose(fp);
	return count;
}