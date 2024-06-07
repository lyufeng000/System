/**
 * @file item.c
 * @brief 物品管理系统的实现
 * @details 该文件包含了物品管理系统的所有功能的实现
 * @date 2024/06/03
 */
#include "item.h"

/**
 * @brief 管理系统的主界面
 * @details 该函数为管理系统的主界面，用户可以通过该界面选择所需的功能
 */
void main_interface() {
	int flag = 1;
	int i;
	while (flag == 1) {
		printf("\033[0m");
		printf("\033[01m");
		printf("*****************************\n");
		printf("*        物品管理系统         *\n");
		printf("*****************************\033[0m\n");
		printf("\033[34m1.添加物品信息\t2.查询物品信息\n3.浏览物品信息\t"
		       "4.修改物品信息\n5.删除物品信息\t6.统计物品信息\n0.退出\033[0m\n");
		printf("请选择您的操作:");
		scanf("%d", &i);
		fflush(stdin);
		switch (i) {
			case 1:
				add_item();
				break;
			case 2:
				search();
				break;
			case 3:
				chaxun_total();
				break;
			case 4:
				revise();
				break;
			case 5:
				delete();
				break;
			case 6:
				tongji();
				break;
			case 0:
				flag = 0;
				break;
			default:
				printf("\033[01;31m错误的指令，请重新输入\033[0m\n");
				break;
		}
	}
}

/**
 * @brief 添加物品信息
 * @details 该函数用于添加物品信息
 */
void add_item() {
	int count;
	printf("请输入添加的数量:");
	scanf("%d", &count);
	item *a = malloc(count * sizeof(item));
	for (int i = 0; i < count; i++) {
		//结构体a[i]接受数据
		printf("请输入物品ID:");
		scanf("%d", &a[i].id);
		while (repeat(a[i].id)) {
			//repeat会在检查到重复的时候返回1(true)
			printf("\033[01;31mID重复，请重新输入:\033[0m");
			scanf("%d", &a[i].id);//重新输入ID后再次判断
		}
		printf("请输入物品名称:");
		scanf("%s", a[i].name);
		printf("请输入物品产地:");
		scanf("%s", a[i].chandi);
		printf("请输入物品价格:");
		scanf("%f", &a[i].price);
		printf("请输入物品数量:");
		scanf("%d", &a[i].num);
		getchar();
		save(a[i]);
	}
	free(a);
}

/**
 * @brief 检查ID是否重复
 * @details 该函数用于检查ID是否重复
 * @param ID 物品ID，用于检查是否重复
 * @return
 */
int repeat(int ID) {
	item a;
	FILE *fp = fopen("item.txt", "r");
	if (!fp || fgetc(fp) == EOF) {
		fclose(fp);
		return 0;
	}
	rewind(fp);
	while (fread(&a, sizeof(item), 1, fp)) {
		if (a.id == ID) {
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}

/**
 * @brief 保存物品信息
 * @details 该函数用于保存物品信息
 * @param a 物品信息
 */
void save(item a) {
	FILE *fp;
	fp = fopen("item.txt", "a");
	fwrite(&a, sizeof(item), 1, fp);
	printf("已保存\n");
	fclose(fp);
}

/**
 * @brief 查询物品信息
 * @details 该函数用于查询物品信息
 * @param ID 物品ID
 * @param name 物品名称
 * @param chandi 物品产地
 * @param price 物品价格
 * @return
 */
void search() {
	int flag = 1;
	int input;
	int ID, price;
	char name[20];
	char chandi[20];
	while (flag == 1) {
		printf("\033[32m1.按ID查询\t2.按名称查询\n3.按产地查询\t4.按价格查询\n0.退出\033[0m\n");
		scanf("%d", &input);
		switch (input) {
			case 1:
				printf("请输入要查询的ID:");
				scanf("%d", &ID);
				search_infor(ID, "NULL", "NULL", (int) NULL);
				break;
			case 2:
				printf("请输入要查询的名称：");
				scanf("%s", name);
				search_infor((int) NULL, name, "NULL", (int) NULL);
				break;
			case 3:
				printf("请输入要查询的产地");
				scanf("%s", chandi);
				search_infor((int) NULL, "NULL", chandi, (int) NULL);
				break;
			case 4:
				printf("请输入要查询的价格");
				scanf("%d", &price);
				search_infor((int) NULL, "NULL", "NULL", price);
				break;
			case 0:
				flag = 0;
				break;
			default:
				printf("请重新输入");
				break;
		}
	}
}

/**
 * @brief 查询所有物品信息
 * @details 该函数用于查询所有物品信息
 * @param ID 物品ID
 * @param yes 是否存在目标信息
 * @return
 */
void chaxun_total() {
	item a;
	int yes = 0;
	FILE *fp = fopen("item.txt", "r");
	if (!fp) {
		printf("\033[01;31m文件不存在\033[0m\n");
		return;
	}
	while (fread(&a, sizeof(item), 1, fp)) {
		yes = 1;
		printf("\033[01;34m");
		printf("ID:%d\n", a.id);
		printf("名称:%s\n", a.name);
		printf("价格:%f\n", a.price);
		printf("产地:%s\n", a.chandi);
		printf("数量:%d\n\n", a.num);
		printf("\033[0m");
	}
	if (yes == 0) {
		printf("\033[01;31m无目标信息\033[0m\n");
	}
	fclose(fp);
}

/**
 * @brief 查询物品信息
 * @details 该函数用于查询物品信息，用参数和文件内的信息进行比较
 * @param ID 物品的ID号
 * @param name 物品的名称
 * @param chandi 物品的产地
 * @param price 物品的价格
 */
void search_infor(int ID, char name[20], char chandi[20], float price) {
	int flag = 1;
	int i = 0;
	item a[50];
	FILE *fp;
	fp = fopen("item.txt", "r");
	while (!feof(fp)) {
		fread(&a[i], sizeof(item), 1, fp);
		i++;
	}
	for (int j = 0; j < i - 1; ++j) {
		if (ID == a[j].id || !strcmp(name, a[j].name) || !strcmp(chandi, a[j].chandi) || price == a[j].price) {
			printf("\033[01;34m");
			printf("ID:%d\n", a[j].id);
			printf("名称:%s\n", a[j].name);
			printf("产地:%s\n", a[j].chandi);
			printf("单价:%f\n", a[j].price);
			printf("数量:%d\n\n", a[j].num);
			printf("\033[0m");
			flag = 0;
		}
	}
	if (flag == 1) {
		printf("\033[01;31m查无此物\033[0m\n");
		fclose(fp);
		return;
	}
	fclose(fp);
}

/**
 * @brief 修改物品信息
 * @details 该函数用于修改物品信息
 * @details 通过用户不同的选择，对物品信息进行修改
 * @details 用户可以选择修改物品的ID、名称、产地、价格、数量
 * @details 用户可以选择保存修改后的信息
 * @param position 物品指针的位置
 * @param end 控制循环
 * @param choose 用户选择
 * @param flag 判断是否找到物品
 */
void revise() {
	int position = 0;
	int end = 1;
	int choose;
	int flag = 0;
	FILE *fp = fopen("item.txt", "r+");
	item a;
	char input[20];
	printf("\033[32m请输入要修改的id或名称:\033[0m");
	scanf("%s", input);
	while (fread(&a, sizeof(item), 1, fp)) {
		position++;
		if (!strcmp(a.name, input) || atoi(input) == a.id) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) {
		printf("\033[01;34m");
		printf("ID:%d\n", a.id);
		printf("名称:%s\n", a.name);
		printf("产地:%s\n", a.chandi);
		printf("单价:%f\n", a.price);
		printf("数量:%d\n\n", a.num);
		printf("\033[0m");
		while (end == 1) {
			printf("\033[32m");
			printf("1.修改物品ID  \t2.修改物品名称\n3.修改物品产地\t"
			       "4.修改物品价格\n5.修改物品数量\n0.保存\n");
			printf("\033[0m");
			printf("请选择您的操作:");
			scanf("%d", &choose);
			switch (choose) {
				case 1:
					printf("请输入修改后的ID:");
					scanf("%d", &a.id);
					printf("修改成功\n");
					break;
				case 2:
					printf("请输入修改后的名称：");
					scanf("%s", a.name);
					printf("修改成功\n");
					break;
				case 3:
					printf("请输入修改后的产地：");
					scanf("%s", a.chandi);
					printf("修改成功\n");
					break;
				case 4:
					printf("请输入修改后的价格:");
					scanf("%f", &a.price);
					printf("修改成功\n");
					break;
				case 5:
					printf("请输入修改后的数量:");
					scanf("%d", &a.num);
					printf("修改成功\n");
					break;
				case 0:
					end = 0;
					break;
				default:
					printf("\033[01;31m错误的表达方式\n\033[0m");
					break;
			}
		}
	} else {
		printf("\033[01;31m查无此物\033[0m\n");
		return;
	}
	fseek(fp, (position - 1) * sizeof(item), SEEK_SET);
	fwrite(&a, sizeof(item), 1, fp);
	fclose(fp);
}

/**
 * @brief 删除物品信息向导
 * @details 该函数用于指向不同的删除方式的函数
 * @details 用户可以选择单独删除或批量删除
 * @return
 */
void delete() {
	int choose;
	int flag = 1;
	while (flag == 1) {
		printf("\033[32m");
		printf("1.单独删除\n2.批量删除\n0.退出\n\033[0m");
		printf("请选择您要删除的方式:");
		scanf("%d", &choose);
		switch (choose) {
			case 1:
				delete_In_Separately();
				break;
			case 2:
				delete_in_bulk();
				break;
			case 0:
				flag = 0;
				break;
			default:
				printf("\033[01;31m错误的输入，请重新输入\033[0m");
				break;
		}
	}
}

/**
 * @brief 单独删除物品信息
 * @details 该函数用于单独删除物品信息
 * @details 输入要删除的物品的ID或名称
 * @details 然后删除该物品的信息
 * @param q 用户选择，是否删除
 * @param input 输入的ID或名称
 * @param yes 判断是否找到物品
 *
 */
void delete_In_Separately() {
	int q;
	item a;
	int yes = 0;
	char input[20];
	FILE *fp = fopen("item.txt", "r");
	FILE *XY = fopen("temp.txt", "w");
	if (!fp || !XY) {
		printf("\033[01;31m文件打开失败\033[0m\n");
		return;
	}
	printf("请输入要删除的物品信息:");
	scanf("%s", input);
	while (fread(&a, sizeof(item), 1, fp)) {
		if (a.id == atoi(input) || !strcmp(a.name, input)) {
			yes = 1;
			printf("\033[34mID:%d\n名称:%s\n产地:%s\n价格:%f"
			       "\n数量:%d\n\033[0m", a.id, a.name, a.chandi, a.price, a.num);
			continue;
		}
		fwrite(&a, sizeof(item), 1, XY);
	}
	if (yes == 0) {
		printf("\033[01;31m没有信息为\"%s\"的物品\033[0m\n", input);
		fclose(fp);
		fclose(XY);
		return;
	}
	fclose(fp);
	fclose(XY);
	printf("是否删除该产品\n");
	printf("1.确认\t2.退出\n");
	scanf("%d", &q);
	if (q == 1) {
		delete_dandu();
		printf("删除成功\n");
	} else {
		fclose(fp);
		fclose(XY);
		return;
	}
	
}

/**
 * @brief 将中间文件的内容写回原文件
 */
void delete_dandu() {
	item a;
	FILE *XY = fopen("temp.txt", "r");
	FILE *fp = fopen("item.txt", "w");
	while (fread(&a, sizeof(item), 1, XY)) {
		fwrite(&a, sizeof(item), 1, fp);
	}
	fclose(fp);
	fclose(XY);
}

/**
 * @brief 批量删除物品信息
 * @details 该函数用于批量删除物品信息
 * @details 输入要删除的物品的产地
 * @details 然后删除该产地的所有物品信息
 * @param c 输入的产地
 * @param yes 判断是否找到物品
 * @param k 用户选择，是否删除
 *
 */
void delete_in_bulk() {
	int k;
	item a;
	char c[20];
	int yes = 0;
	//初始状态下,认为文件中不包含目标信息
	printf("请输入物品产地:");
	scanf("%s", c);
	FILE *fp = fopen("item.txt", "r");
	FILE *file = fopen("temp.txt", "w");
	while (fread(&a, sizeof(item), 1, fp)) {
		if (!strcmp(a.chandi, c)) {
			//如果文件内包含目标信息
			yes = 1;
			printf("\033[34mID:%d\n", a.id);
			printf("名称:%s\n", a.name);
			printf("价格:%f\n", a.price);
			printf("产地:%s\n", a.chandi);
			printf("数量:%d\n\n\033[0m", a.num);
			continue;
		}
		fwrite(&a, sizeof(item), 1, file);
	}
	fclose(fp);
	fclose(file);
	if (yes == 0) {
		printf("\033[01;31m没有产地在\"%s\"的物品\n\033[0m", c);
		return;
	}
	printf("是否删除该产品\n");
	printf("1.确认\t2.退出\n");
	scanf("%d", &k);
	if (k == 1) {
		delete_dandu();
		printf("删除成功\n");
	} else {
		fclose(fp);
		fclose(file);
		return;
	}
	fclose(fp);
	fclose(file);
}

/**
 * @brief 统计物品信息
 * @details 该函数用于统计物品信息，用户可以选择不同的统计方式
 * @details 用户可以选择按价格从高到低排序或者出库成本最大的商品
 * @param e 用户选择
 * @param flag 控制循环
 */
void tongji() {
	int e;
	int flag = 1;
	while (flag == 1) {
		printf("1.价格从高到低排序\t2.出库成本最大商品\n0.返回\n");
		printf("请选择您要统计的类型:");
		scanf("%d", &e);
		switch (e) {
			case 1:
				paixu();
				break;
			case 2:
				chengben();
				break;
			case 0:
				flag = 0;
				break;
			default:
				printf(" 选择错误\n");
				break;
		}
	}
}

/**
 * @brief 价格从高到低排序
 * @details 该函数用于将物品按价格从高到低排序
 * @details 读取文件中的物品信息，然后按价格从高到低排序
 * @details 最后输出排序后的物品信息
 * @param count 文件中的物品数量
 * @param temp 用于交换位置的临时变量
 * @param a 动态结构体数组
 * @param i 冒泡排序的第一个循环变量
 * @param j 冒泡排序的第二个循环变量
 *
 */
void paixu() {
	int count = stats();//count就是文件里的物品数
	FILE *fp = fopen("item.txt", "r");
	item temp;
	//进行动态结构体初始化
	item *a = malloc(count * sizeof(item));
	for (int i = 0; i < count; ++i) {
		fread(&a[i], sizeof(item), 1, fp);
	}
	//冒泡排序
	for (int i = 0; i < count; ++i) {
		for (int j = 0; j < count - 1; ++j) {
			if (a[j].price < a[j + 1].price) {
				//调换位置啊
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < count; ++i) {
		printf("ID:%d\n", a[i].id);
		printf("名称:%s\n", a[i].name);
		printf("价格:%f\n", a[i].price);
		printf("产地:%s\n", a[i].chandi);
		printf("数量:%d\n\n", a[i].num);
	}
	fclose(fp);
	free(a);
}

/**
 * @brief 统计物品数量
 * @details 该函数用于统计物品数量
 * @details 读取文件中的物品信息，然后统计物品数量
 * @param a 用于接收文件中的物品信息
 * @param number 物品数量
 * @param fp 文件指针
 * @return 物品数量
 */
int stats() {
	item a;
	int number = 0;//number用于记录物品数量
	FILE *fp = fopen("item.txt", "r");
	while (fread(&a, sizeof(item), 1, fp)) {
		number++;//每读出来一个,number+1
	}
	return number;
}

/**
 * @brief 出库成本最大的商品
 * @details 该函数用于找出出库成本最大的商品
 * @details 读取文件中的物品信息，然后找出出库成本最大的商品
 * @details 最后输出出库成本最大的商品信息
 * @param price 出库成本最大的商品的价格
 * @param temp 用于比较的临时变量
 * @param count 文件中的物品数量
 * @param a 动态结构体数组
 * @param i 循环变量
 * @param fp 文件指针
 */
void chengben() {
	float price, temp;
	int count = stats();
	item *a = malloc(count * sizeof(item));
	FILE *fp = fopen("item.txt", "r");
	for (int i = 0; i < count; ++i) {
		fread(&a[i], sizeof(item), 1, fp);
		if (i == 0) {
			price = a[i].num * a[i].price;
		} else {
			temp = a[i].price * a[i].num;
			if (temp > price) {
				price = temp;
			}
		}
	}
	for (int i = 0; i < count; ++i) {
		if (a[i].price * a[i].num == price) {
			printf("库存成本最大的商品是:%f\n", price);
			printf("ID:%d\n", a[i].id);
			printf("名称:%s\n", a[i].name);
			printf("价格:%f\n", a[i].price);
			printf("产地:%s\n", a[i].chandi);
			printf("数量:%d\n\n", a[i].num);
		}
	}
	fclose(fp);
	free(a);
}
