#ifndef SUPERMARKETMANAGEMENTSYSTEM_LOGIN_H
#define SUPERMARKETMANAGEMENTSYSTEM_LOGIN_H

#include <iostream>

using namespace std;

bool link_to_admin();
void registe();
bool link_to_user();
void show_all_account();
void set_permissions();
void delete_account();
void permissions();
void color(int c);
int caculate();


extern "C" void logIn();

//#ifdef __cplusplus

class user {
private:
	string this_account;
	string this_code;
	int this_status; // 权限：0.职工管理，1.物品管理
public:
	void set_account(string &account) {
		this_account = account;
	}
	
	void set_code(string &code) {
		this_code = code;
	}
	
	void set_status(int status) {
		this_status = status;
	}
	
	string get_account() {
		return this_account;
	}
	
	string get_code() {
		return this_code;
	}
	
	int get_status() {
		return this_status;
	}
};

//#endif

#endif //SUPERMARKETMANAGEMENTSYSTEM_LOGIN_H
