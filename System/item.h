/**
 * @file item.h
 * @author 赵熙缘
 * @date 2024/06/03
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief 定义结构体item
 * @param id 商品编号
 * @param name 商品名称
 * @param chandi 商品产地
 * @param price 商品价格
 * @param num 商品数量
 */
typedef struct {
    int id;
    char name[20];
    char chandi[20];
    float price;
    int num;
} item;

static void add_item();

static int repeat(int ID);

void main_interface();

static void save(item a);

static void search();

static void search_infor(int ID, char name[20], char chandi[20], float price);

static void revise();

static void delete();

static void delete_In_Separately();

static void delete_dandu();

static void delete_in_bulk();

static void tongji();

static void paixu();

static int stats();

static void chengben();

static void chaxun_total();
