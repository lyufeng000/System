/**
 * @file function.c
 * @brief 这是职工管理系统
 * @author 李雨峰
 * @date 2024/06/03
 */
#include "function.h"

/**
 * @brief 主页面，负责调用其他函数
 * @details 接收用户输入的操作，与指定好的数字进行比对，进入对应的函数，每次进入函数后都会返回到这个函数
 * @param input 用户输入的操作
 */
void staff(){
	fflush(stdin);
	int inPut;
	while (1) {
		printf("\033[0m");
		printf("*****************************\n");
		printf("*        职工管理系统        *\n");
		printf("*****************************\n");
		printf("\033[34m1.添加职工信息\t2.查询职工信息\n3.浏览职工信息\t4.修改职工信息\n"
		       "5.删除职工信息\t6.执行统计\n0.退出\033[0m\n");
		printf("请选择您的操作:");
		scanf("%d", &inPut);
		fflush(stdin);
		switch (inPut) {
			case 1:
				add_staff();
				break;
			case 2:
				search_one();
				break;
			case 3:
				find_all();
				break;
			case 4:
				revise();
				break;
			case 5:
				delete();
				break;
			case 6:
				stats();
				break;
			case 0:
				exit(0);
			default:
				printf("\033[31m错误的命令请重新输入:\033[0m\n");
		}
	}
}

/**
 * @brief 添加职工信息
 * @details 先输入录入的人数，然后依次输入职工信息，保存到文件中
 * @details 信息包括ID，姓名，年龄，性别，工龄，级别，工资，婚姻状况，在职情况
 * @details 询问是否保存，若不保存返回开头，且不占人数
 * @param count 记录用户要添加的人数，用于控制循环
 * @param sure 记录是否保存，与'y'和'n'比较
 * @param A 结构体，用于存储职工信息
 */
void add_staff(){
	int count;
	char sure;
	printf("请输入添加人数:");
	scanf("%d", &count);
	staf A;
	for (int i = 0; i < count;) {
		restart:
		A.ID = ID_add();
		//————————————————————————————————————
		printf("请输入姓名:");
		scanf("%s", A.name);
		//————————————————————————————————————
		sex:
		printf("请输入性别:");
		scanf("%s", A.sex);
		if (strcmp(A.sex, "男") != 0 && strcmp(A.sex, "女")) {
			printf("\033[31m性别错误\033[0m\n");
			goto sex;
		}
		//————————————————————————————————————
		printf("请输入年龄:");
		scanf("%d", &A.age);
		//————————————————————————————————————
		work:
		printf("请输入工龄:");
		scanf("%d", &A.workTime);
		if (A.workTime > A.age) {
			printf("\033[31m工龄不得大于年龄\033[0m\n");
			goto work;
		}
		//————————————————————————————————————
		marri:
		printf("请输入婚姻状况:");
		scanf("%s", A.marrige);
		if (strcmp(A.marrige, "已婚") && strcmp(A.marrige, "未婚")) {
			printf("\033[31m婚姻状态错误\033[0m\n");
			goto marri;
		}
		//————————————————————————————————————
		lev:
		printf("请输入员工级别:");
		scanf("%d", &A.grade);
		if (A.grade > 5 || A.grade < 1) {
			printf("\033[31m级别错误\033[0m\n");
			goto lev;
		}
		//————————————————————————————————————
		printf("请输入员工工资:");
		scanf("%d", &A.wage);
		//————————————————————————————————————
		tir:
		printf("请输入员工在职状况:");
		scanf("%s", A.tired);
		fflush(stdin);
		if (strcmp(A.tired, "在职") && strcmp(A.tired, "休假")) {
			printf("\033[31m工作状态错误\033[0m\n");
			goto tir;
		}
		//————————————————————————————————————
		sav:
		printf("要保存吗?(Y/N)\n");
		scanf("%c", &sure);
		fflush(stdin);
		if (sure == 'Y' || sure == 'y') {
			save(A);
		} else if (sure == 'N' || sure == 'n') {
			goto restart;
		} else {
			printf("\033[31m错误的表达方式,请重新输入\033[0m\n");
			goto sav;
		}
		i++;
	}
}

/**
 * @brief ID自动编号
 * @details 打开文件，将指针直接指向文件最后一位，读取最后一位的ID，然后加1
 * @param a 结构体，用于存储职工信息
 * @return 返回ID+1作为新的ID
 */
int ID_add(){
	staf a;
	FILE *fp = fopen("staff.txt", "r");
	fseek(fp, -1 * sizeof(staf), SEEK_END);
	fread(&a, sizeof(staf), 1, fp);
	fclose(fp);
	return (a.ID + 1);
}

/**
 * @brief 将添加的职工信息保存下来
 * @param A 作为参数，被传递过来然后保存
 */
void save(staf A){
	FILE *fp;
	fp = fopen("staff.txt", "a");
	fwrite(&A, sizeof(staf), 1, fp);
	fclose(fp);
}

/**
 * @brief 查看全部员工信息
 * @details 先打开文件，若文件为空或不存在则打印保存信息并返回
 * @details 若存在，则使用fread控制while的循环，循环读出文件内容并打印
 */
void find_all(){
	FILE *fp = fopen("staff.txt", "r");
	staf a;
	if (!fp) {
		printf("\033[31m无法打开文件\033[31m\n");
		return;
	}
	if (fgetc(fp) == EOF) {
		printf("\033[31m查无此人\033[0m\n");
		return;
	}
	rewind(fp);
	while (fread(&a, sizeof(staf), 1, fp)) {
		printf("\033[34mID:%d\n", a.ID);
		printf("姓名:%s\n", a.name);
		printf("年龄:%d\n", a.age);
		printf("性别:%s\n", a.sex);
		printf("工龄:%d\n", a.workTime);
		printf("级别:%d\n", a.grade);
		printf("工资:%d\n", a.wage);
		printf("婚姻状况:%s\n", a.marrige);
		printf("在职情况:%s\033[0m\n\n", a.tired);
	}
	return;
}

/**
 * @brief 可以选择查询员工的方法，进入不同的函数
 * @details 先选择查询方式（ID or 姓名）
 * @details 通过不同的选择进入不同的函数
 * @param choice 是用户的选择
 * @param input 是接收用户输入的字符串（名字）
 * @param ID 接收用户输入的ID
 */
void revise(){
	int flag = 1;
	int ID;
	int choice;
	char input[20];
	while (flag == 1) {
		printf("\033[32m1.ID查询\n2.姓名查询\n0.退出\033[0m\n");
		printf("请输入您的操作:");
		scanf("%d", &choice);
		fflush(stdin);
		switch (choice) {
			case 1:
				printf("请输入ID:");
				scanf("%d", &ID);
				revise_id(ID);
				break;
			case 2:
				printf("请输入姓名:");
				scanf("%s", input);
				revise_name(input);
				break;
			case 0:
				flag = 0;
				break;
			default:
				printf("\033[31m错误的表达方式,请重新输入:\033[0m\n");
				break;
		}
	}
}

/**
 * @brief 通过id查找修改员工的信息
 * @details 先打开文件，判断文件是否打开失败
 * @details 使用fread控制循环，将信息读到结构体中，判断结构体中信息的ID是否和传入的相同
 * @details 找到员工后，选择修改的数据类型，把修改后的数据暂时放入结构体，确定保存后写入文件
 * @details 如果没有查找到，那么输出查无此人
 * @param id 员工的ID，通过这个ID特定检索员工信息
 * @param yes 默认值为0，代表员工不存在，当查找到员工信息将其归1
 * @param flag 默认值是1，保证循环持续进行，选择保存后归0，退出循环
 * @param position 记录员工的位置，在写入之前用该变量控制指针的位置
 */
void revise_id(int id){
	staf a;
	int yes = 0;
	int choose;
	int flag = 1;
	int position = 0;
	FILE *fp = fopen("staff.txt", "r+");
	if (!fp) {
		printf("\033[31m文件打开失败\033[0m\n");
		fclose(fp);
		return;
	}
	while (fread(&a, sizeof(staf), 1, fp)) {
		position++;
		if (a.ID == id) {
			yes = 1;
			break;
		}
	}
	if (yes == 0) {
		printf("\033[31m查无此人\033[0m\n");
		return;
	}
	printf("\033[34mID:%d\n", a.ID);
	printf("姓名:%s\n", a.name);
	printf("年龄:%d\n", a.age);
	printf("性别:%s\n", a.sex);
	printf("工龄:%d\n", a.workTime);
	printf("级别:%d\n", a.grade);
	printf("工资:%d\n", a.wage);
	printf("婚姻状况:%s\n", a.marrige);
	printf("在职情况:%s\033[0m\n", a.tired);
	while (flag == 1) {
		printf("\033[33m1.修改姓名\t2.修改年龄\n3.修改性别\t4.修改工龄\n5.修改级别\t6."
		       "修改工资\n7.修改婚况\t8.修改在职情况\n0.保存\033[0m\n");
		printf("请输入要修改的数据类型:");
		scanf("%d", &choose);
		switch (choose) {
			case 1:
				printf("\033[34m请输入修改后的姓名:");
				scanf("%s\033[0m", a.name);
				break;
			case 2:
				printf("\033[34m请输入修改后的年龄:");
				scanf("%d\033[0m", &a.age);
				break;
			case 3:
				printf("\033[34m请输入修改后的性别:");
				scanf("%s\033[0m", a.sex);
				break;
			case 4:
				printf("\033[34m请输入修改后的工龄:");
				scanf("%d\033[0m", &a.workTime);
				break;
			case 5:
				printf("\033[34m请输入修改后的级别:");
				scanf("%d\033[0m", &a.grade);
				break;
			case 6:
				printf("\033[34m请输入修改后的工资:");
				scanf("%d\033[0m", &a.wage);
				break;
			case 7:
				printf("\033[34m请输入修改后的婚姻状况:");
				scanf("%s\033[0m", a.marrige);
				break;
			case 8:
				printf("\033[34m请输入修改后的在职情况:");
				scanf("%s\033[0m", a.tired);
				break;
			case 0:
				flag = 0;
				break;
			default:
				printf("\033[31m错误的表达方式,请重新输入\033[0m\n");
				break;
		}
	}
	fseek(fp, (position - 1) * sizeof(staf), SEEK_SET);
	fwrite(&a, sizeof(staf), 1, fp);
	fclose(fp);
}

/**@brief 通过姓名查找修改员工的信息
 * @details 先打开文件，判断文件是否打开失败
 * @details 使用fread控制循环，将信息读到结构体中，判断结构体中信息的ID是否和传入的相同
 * @details 找到员工后，选择修改的数据类型，把修改后的数据暂时放入结构体，确定保存后写入文件
 * @details 如果没有查找到，那么输出查无此人
 * @param name 员工的姓名，通过这个名字特定检索员工信息
 * @param yes 默认值为0，代表员工不存在，当查找到员工信息将其归1
 * @param flag 默认值是1，保证循环持续进行，选择保存后归0，退出循环
 * @param position 记录员工的位置，在写入之前用该变量控制指针的位置
 *
 */
void revise_name(char name[20]){
	staf a;
	int choose;
	int yes = 0;
	int flag = 1;
	int position = 0;
	FILE *fp = fopen("staff.txt", "r+");
	if (!fp) {
		printf("\033[31m文件打开失败\033[0m\n");
		fclose(fp);
		return;
	}
	while (fread(&a, sizeof(staf), 1, fp)) {
		position++;
		if (!strcmp(name, a.name)) {
			yes = 1;
			break;
		}
	}
	if (yes == 0) {
		printf("\033[31m查无此人\033[0m\n");
		return;
	}
	printf("\033[34mID:%d\n", a.ID);
	printf("姓名:%s\n", a.name);
	printf("年龄:%d\n", a.age);
	printf("性别:%s\n", a.sex);
	printf("工龄:%d\n", a.workTime);
	printf("级别:%d\n", a.grade);
	printf("工资:%d\n", a.wage);
	printf("婚姻状况:%s\n", a.marrige);
	printf("在职情况:%s\033[0m\n", a.tired);
	while (flag == 1) {
		printf("\033[33m1.修改姓名\t2.修改年龄\n3.修改性别\t4.修改工龄\n5.修改级别\t6."
		       "修改工资\n7.修改婚况\t8.修改在职情况\n0.保存\033[0m\n");
		printf("请输入要修改的数据类型:");
		scanf("%d", &choose);
		switch (choose) {
			case 1:
				printf("\033[34m请输入修改后的姓名:");
				scanf("%s\033[0m", a.name);
				break;
			case 2:
				printf("\033[34m请输入修改后的年龄:");
				scanf("%d\033[0m", &a.age);
				break;
			case 3:
				printf("\033[34m请输入修改后的性别:");
				scanf("%s\033[0m", a.sex);
				break;
			case 4:
				printf("\033[34m请输入修改后的工龄:");
				scanf("%d\033[0m", &a.workTime);
				break;
			case 5:
				printf("\033[34m请输入修改后的级别:");
				scanf("%d\033[0m", &a.grade);
				break;
			case 6:
				printf("\033[34m请输入修改后的工资:");
				scanf("%d\033[0m", &a.wage);
				break;
			case 7:
				printf("\033[34m请输入修改后的婚姻状况:");
				scanf("%s\033[0m", a.marrige);
				break;
			case 8:
				printf("\033[34m请输入修改后的在职情况:");
				scanf("%s\033[0m", a.tired);
				break;
			case 0:
				flag = 0;// 保存
				break;
			default:
				printf("\033[31m错误的表达方式,请重新输入\033[0m\n");
				break;
		}
	}
	fseek(fp, (position - 1) * sizeof(staf), SEEK_SET);
	fwrite(&a, sizeof(staf), 1, fp);
	fclose(fp);
}

/**
 * @brief 可以查询有特定信息的员工
 * @param yes 默认0代表员工不存在，存在则归1
 * @param sure 保存用户输入的是否继续查询的选择
 * @param information 保存用户输入的信息
 * @param a 结构体，用于存储职工信息
 * @param fp 打开文件
 * @return 返回1，继续查询，返回0，退出查询
 */
int search_one(){
	fflush(stdin);
	staf a;
	int yes;
	FILE *fp;
	char sure;
	char information[20];
	start:
	yes = 0;
	fp = fopen("staff.txt", "r");
	if (!fp) {
		printf("\033[31m文件打开失败\033[0m\n");
		fclose(fp);
		return 0;
	}
	printf("请输入要查询的信息(ID，姓名，性别，婚姻状态)\n");
	scanf("%s", information);
	while (fread(&a, sizeof(staf), 1, fp)) {
		if (a.ID == atoi(information) || !strcmp(a.name, information) || !strcmp(a.sex, information) ||
		    !strcmp(a.marrige, information)) {
			yes = 1;
			printf("\033[34mID:%d\n", a.ID);
			printf("姓名:%s\n", a.name);
			printf("年龄:%d\n", a.age);
			printf("性别:%s\n", a.sex);
			printf("工龄:%d\n", a.workTime);
			printf("级别:%d\n", a.grade);
			printf("工资:%d\n", a.wage);
			printf("婚姻状况:%s\n", a.marrige);
			printf("在职情况:%s\033[0m\n\n", a.tired);
		}
	}
	if (yes == 0) {
		fflush(stdin);
		printf("\033[01;31m没有信息为%s的人\033[0m\n", information);
	}
	fclose(fp);
	fflush(stdin);
	printf("要继续查询吗?(Y/N)\n");
	sure = getchar();
	fflush(stdin);
	if (sure == 'Y' || sure == 'y') {
		goto start;
	}
	return 1;
}

/**
 * @brief 删除向导，指向不同的删除方法
 * @details 选择删除的方法，单独删除，级别删除，全部删除
 * @param choose 用户输入的选择
 * @param fp 打开文件
 */
void delete(){
	FILE *fp = fopen("staff.txt", "r");
	if (!fp) {
		printf("\033[31m文件打开失败\033[0m\n");
		fclose(fp);
		return;
	}
	fclose(fp);
	char choose;
	str:
	printf("\033[32m1.单独删除\t2.级别删除\n3.全部删除\n0.返回\033[0m\n");
	printf("请输入删除的方法:");
	scanf("%c", &choose);
	fflush(stdin);
	switch (choose) {
		case '1':
			Delete_Individually();
			break;
		case '2':
			Delete_In_Bulk();
			break;
		case '3':
			remove("staff.txt");
			break;
		case '0':
			return;
		default:
			printf("\033[31m错误的指令,请重新输入\033[0m\n");
			goto str;
	}
}

/**
 * @brief 单独删除
 * @details 先打开文件，判断文件是否打开失败
 * @details 使用fread控制循环，将信息读到结构体中，判断结构体中信息的ID是否和传入的相同
 * @details 除了找到的员工，其他员工信息写入中间文件
 * @details 确认删除后，将中间文件内容写入原文件
 * @param a 结构体，用于存储职工信息
 * @param sure 保存用户输入的是否删除的选择
 * @param yes 默认0代表员工不存在，存在则归1
 * @param flag 默认值是1，保证循环持续进行，如果输入错误就将继续循环
 * @param infor 保存用户输入的信息
 * @param fp 打开文件
 * @param file 打开中间文件
 */
void Delete_Individually(){
	staf a;
	char sure;
	int yes = 0;
	int flag = 1;
	char infor[20];
	FILE *fp = fopen("staff.txt", "r");
	FILE *file = fopen("temp.txt", "w");
	//在假设情况下,姓名和ID是唯一标识,不存在重名状态
	//后期优化可添加重名可能性
	printf("请输入要删除的姓名或ID:");
	fflush(stdin);
	scanf("%s", infor);
	while (fread(&a, sizeof(staf), 1, fp)) {
		if (!strcmp(a.name, infor) || a.ID == atoi(infor)) {
			//查找到了即将删除的信息
			yes = 1;//表示找到了要删除的人
			printf("\033[31mID:%d\n", a.ID);
			printf("姓名:%s\n", a.name);
			printf("年龄:%d\n", a.age);
			printf("性别:%s\n", a.sex);
			printf("工龄:%d\n", a.workTime);
			printf("级别:%d\n", a.grade);
			printf("工资:%d\n", a.wage);
			printf("婚姻状况:%s\n", a.marrige);
			printf("在职情况:%s\033[0m\n", a.tired);
		} else {
			//没有找到即将删除的信息,将无关信息写入中间文件temp
			fwrite(&a, sizeof(staf), 1, file);
		}
	}
	if (yes == 0) {
		printf("\033[01;31m没有目标信息为\"%s\"的人\033[0m\n", infor);
		return;
	}
	fclose(fp);
	fclose(file);
	while (flag == 1) {
		getchar();
		printf("确定要删除吗?(Y/N)\n");
		sure = getchar();
		if (sure == 'Y' || sure == 'y') {
			flag = 0;//用于跳出while
			resave();
		} else if (sure == 'N' || sure == 'n') {
			return;//不删除,返回上一级
		} else {
			printf("\033[31m错误的指令,请重新输入\033[0m\n");
		}
	}
}

/**
 * @brief 批量删除
 * @details 先打开文件，判断文件是否打开失败
 * @details 使用fread控制循环，将信息读到结构体中，判断结构体中信息的级别是否和输入的相同
 * @details 除了找到的员工，其他员工信息写入中间文件
 * @details 每找出一个员工，就询问是否删除，若删除则跳过，不删除则写入中间文件
 * @details 确认删除后，将中间文件内容写入原文件
 * @param a 结构体，用于存储职工信息
 * @param level 保存用户输入的级别
 * @param sure 保存用户输入的是否删除的选择
 * @param fp 打开文件
 * @param file 打开中间文件
 */
void Delete_In_Bulk(){
	staf a;
	int level;
	char sure;
	FILE *fp = fopen("staff.txt", "r");
	FILE *file = fopen("temp.txt", "w");
	printf("请输入要删除的级别:");
	scanf("%d", &level);
	while (fread(&a, sizeof(staf), 1, fp)) {
		if (a.grade == level) {
			printf("\033[34mID:%d\n", a.ID);
			printf("姓名:%s\n", a.name);
			printf("年龄:%d\n", a.age);
			printf("性别:%s\n", a.sex);
			printf("工龄:%d\n", a.workTime);
			printf("级别:%d\n", a.grade);
			printf("工资:%d\n", a.wage);
			printf("婚姻状况:%s\n", a.marrige);
			printf("在职情况:%s\n", a.tired);
			printf("\033[01;31m确定要删除这个人吗?(Y/N)\033[0m");
			getchar();
			scanf("%c", &sure);
			if (sure == 'Y' || sure == 'y') {
				continue;
			}
		}
		fwrite(&a, sizeof(staf), 1, file);
	}
	fclose(fp);
	fclose(file);
	resave();
}

/**
 * @brief 重新导向，将中间文件的内容写入原文件
 * @details 打开文件，判断文件是否打开失败
 * @details 使用fread控制循环，将信息读到结构体中，然后写入文件
 * @details 关闭文件
 */
void resave(){
	staf a;
	FILE *fp = fopen("temp.txt", "r");
	FILE *file = fopen("staff.txt", "w");
	if (!fp || !file) {
		printf("\033[01;31m文件打开失败\033[0m\n");
		return;
	}
	while (fread(&a, sizeof(staf), 1, fp)) {
		fwrite(&a, sizeof(staf), 1, file);
	}
	fclose(fp);
	fclose(file);
	sort();
	return;
}

/**
 * @brief 重新编号
 * @details 打开文件，判断文件是否打开失败
 * @details 计算文件中的记录数量
 * @details 分配内存，然后读取所有记录到内存
 * @details 对信息进行重新排序，补充缺失的ID号
 * @details 将排序后的记录写回到文件
 * @details 清理内存
 * @param record_count 记录文件中的记录数量
 * @param fp 打开文件
 * @param records 结构体，用于存储职工信息
 */
void sort(){
	// 打开文件
	FILE *fp = fopen("staff.txt", "r+");
	if (!fp) {
		printf("无法打开文件\n");
		return;
	}
	
	// 计算文件中的记录数量
	fseek(fp, 0, SEEK_END);
	int record_count = stats_number();
	rewind(fp);
	
	// 分配内存
	staf *records = malloc(record_count * sizeof(staf));
	if (!records) {
		printf("内存分配失败\n");
		fclose(fp);
		return;
	}
	// 读取所有记录到内存
	for (int i = 0; i < record_count; i++) {
		fread(&records[i], sizeof(staf), 1, fp);
		records[i].ID = i + 1;  // 更新ID
	}
	// 将排序后的记录写回到文件
	rewind(fp);
	for (int i = 0; i < record_count; i++) {
		fwrite(&records[i], sizeof(staf), 1, fp);
	}
	// 清理
	free(records);
	fclose(fp);
	return;
}

/**
 * @brief 统计向导，指向不同的统计方法
 * @details 选择统计的方法，按级别排序，按工资排序，成本最小的员工
 * @details 选择其他数字返回
 * @param choose 用户输入的选择
 */
void stats(){
	//1.统计按级别从低到高排序
	//2.统计付出成本最小的职工信息
	int choose;
	printf("\033[32m1.按级别从低到高排序\n2.按工资从低到高排序\n"
	       "3.成本最小员工\n输入其他数字返回\033[0m\n");
	printf("请输入您的操作:");
	scanf("%d", &choose);
	fflush(stdin);
	switch (choose) {
		case 1:
			stats_level();
			break;
		case 2:
			salary();
			break;
		case 3:
			cheapest_staff();
			break;
		default:
			return;
	}
	return;
}

/**
 * @brief 按级别排序
 * @details 先打开文件，判断文件是否打开失败
 * @details 使用fread控制循环，将信息读到结构体中，然后排序
 * @details 打印排序后的信息
 * @param count 记录文件中的记录数量
 * @param fp 打开文件
 * @param temp 用于交换数据
 * @param i,j 用于冒泡排序
 * @param a 动态分配内存
 */
void stats_level(){
	//读出txt文件里所有内容
	//冒泡排序(不保存)
	int count = stats_number();
	FILE *fp = fopen("staff.txt", "r");
	staf *a = (staf *) malloc(count * sizeof(staf));
	staf temp;
	for (int i = 0; i < (stats_number() + 1); ++i) {
		fread(&a[i], sizeof(staf), 1, fp);
		//count = i;
	}
	for (int i = 0; i < count; ++i) {
		for (int j = 0; j < count - 1; ++j) {
			if (a[j].grade > a[j + 1].grade) {
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < count; ++i) {
		printf("\033[34m");
		printf("ID:%d\n", a[i].ID);
		printf("姓名:%s\n", a[i].name);
		printf("性别:%s\n", a[i].sex);
		printf("年龄:%d\n", a[i].age);
		printf("工龄:%d\n", a[i].workTime);
		printf("\033[01;31m级别:%d\033[00;34m\n", a[i].grade);
		printf("工资:%d\n", a[i].wage);
		printf("婚姻状态:%s\n", a[i].marrige);
		printf("工作状态:%s\n\n", a[i].tired);
		printf("\033[0m");
	}
	free(a);
	return;
}

/**
 * @brief 统计员工数量
 * @details 使用fread控制循环，将信息读到结构体中，然后统计数量
 * @details 关闭文件
 * @param number 记录文件中的记录数量
 * @param a 结构体，用于存储职工信息
 * @param fp 打开文件
 * @return 返回记录文件中的记录数量
 */
int stats_number(){
	int number = 0;
	staf a;
	FILE *fp = fopen("staff.txt", "r");
	while (fread(&a, sizeof(staf), 1, fp)) {
		number++;
	}
	fclose(fp);
	return number;
}

/**
 * @brief 成本最小员工
 * @details 使用fread控制循环，将信息读到结构体中，然后计算级别*工资
 * @details 找出最小的级别*工资，然后打印出来
 * @param temp 用于存储级别*工资
 * @param price 用于存储最小的级别*工资
 * @param count 记录文件中的记录数量
 * @param a 动态分配内存
 * @param b 用于存储职工信息
 * @param fp 打开文件
 * @param i,j 用于冒泡排序
 */
void cheapest_staff(){
	//1.动态初始化内存
	//2.打开文件
	//3.遍历所有人数据，算出 级别*薪资
	//4.冒泡排序，找出最小薪资
	int temp;
	int price;
	int count = stats_number();
	staf b;
	staf *a = (staf *) malloc(count * sizeof(staf));
	FILE *fp = fopen("staff.txt", "r");
	for (int i = 0; i < count; ++i) {
		fread(&a[i], sizeof(staf), 1, fp);
		temp = (a[i].grade * a[i].wage);
		if (i == 0) {
			price = temp;
		} else {
			if (temp < price) {
				price = temp;
			}
		}
	}
	rewind(fp);
	while (fread(&b, sizeof(staf), 1, fp)) {
		if ((b.grade * b.wage) == price) {
			printf("\033[01;34m");
			printf("ID:%d\n", b.ID);
			printf("姓名:%s\n", b.name);
			printf("性别:%s\n", b.sex);
			printf("年龄:%d\n", b.age);
			printf("工龄:%d\n", b.workTime);
			printf("级别:%d\n", b.grade);
			printf("工资:%d\n", b.wage);
			printf("婚姻状态:%s\n", b.marrige);
			printf("工作状态:%s\033[0m\n", b.tired);
			printf("该员工是最廉价的\n");
		}
	}
	
	free(a);
	return;
}

/**
 * @brief 按工资排序
 * @details 使用fread控制循环，将信息读到结构体中，然后排序
 * @details 打印排序后的信息
 * @param count 记录文件中的记录数量
 * @param a 动态分配内存
 * @param temp 用于交换数据
 * @param i,j 用于冒泡排序
 * @param fp 打开文件
 */
void salary(){
	int count = stats_number();
	staf temp;
	staf *a = malloc(count * sizeof(staf));
	FILE *fp = fopen("staff.txt", "r");
	for (int i = 0; i < count; ++i) {
		fread(&a[i], sizeof(staf), 1, fp);
	}
	for (int i = 0; i < count; ++i) {
		for (int j = 0; j < count - 1; ++j) {
			if (a[j].wage > a[j + 1].wage) {
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < count; ++i) {
		printf("\033[34m");
		printf("ID:%d\n", a[i].ID);
		printf("姓名:%s\n", a[i].name);
		printf("性别:%s\n", a[i].sex);
		printf("年龄:%d\n", a[i].age);
		printf("工龄:%d\n", a[i].workTime);
		printf("级别:%d\n", a[i].grade);
		printf("\033[01;31m");
		printf("工资:%d\n", a[i].wage);
		printf("\033[00;34m");
		printf("婚姻状态:%s\n", a[i].marrige);
		printf("工作状态:%s\033[0m\n\n", a[i].tired);
	}
	fclose(fp);
	free(a);
}

