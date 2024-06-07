/**
 * @file function.h
 * @author 李雨峰
 * @date 2024/06/03
 * @brief 头文件，包含库函数引用，结构体定义和函数声明
 */

#ifndef FENG_FUNCTION_H
#define FENG_FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @param ID 是职工的工号
 * @param name 是职工的名字
 * @param age 是职工的年龄
 * @param workTime 是职工的工龄
 * @param sex 是职工的性别
 * @param marrige 是职工的婚姻状态
 * @param grade 是职工的级别
 * @param wage 是职工的工资
 * @param tired 是职工的在职情况
*/
typedef struct {
    int ID;
    char name[20];
    int age;
    int workTime;
    char sex[4];
    char marrige[20];
    int grade;
    int wage;
    char tired[10];
} staf;

//职工页面
extern void staff();

//添加职工
extern void add_staff();

//ID自动编号
extern int ID_add();

//保存
extern void save(staf);

//查找所有人
extern void find_all();

//修改向导
extern void revise();

//通过ID修改
extern void revise_id(int id);

//通过姓名修改
extern void revise_name(char name[20]);

//查找某人
extern int search_one();

//删除向导
extern void delete();

//单独删除
extern void Delete_Individually();

//批量删除
extern void Delete_In_Bulk();

//重新导向
extern void resave();

//ID重新编号
extern void sort();

//职工统计页面
extern void stats();

//统计级别从低到高
extern void stats_level();

//统计人数
extern int stats_number();

//成本最低的员工
extern void cheapest_staff();

//按工资排序
extern void salary();

#endif //FENG_FUNCTION_H
