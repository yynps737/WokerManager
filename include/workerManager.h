//
// Created by kikib on 24-12-2.
//
#pragma once
#include <iostream>
#include <fstream>
#include "../include/woker.h"
#include "../include/employees.h"
#include "../include/Manager.h"
#include "../include/Boss.h"
#define FILENAME "empFile.txt"
using namespace std;

//声明WorkerManager类
class WorkerManager {
public:
    //声明构造函数
    WorkerManager();



	//声明保存数据函数
	void save();

    //声明静态函数菜单
    void Show_Menu();

    //声明退出系统函数
    void ExitSystem();

    //声明增加职工函数
    void Add_Emp();

    //初始化职工
    void init_Emp();

    //统计职工人数
    int get_EmpNum();

	//声明显示职工函数
	void Show_Emp();

	//判断职工是否存在,若存在返回职工在数组中的位置,不存在返回-1
	int IsExist(int id);
    
	//声明删除职工函数
	void Del_Emp();

	//修改职工
	void Mod_Emp();

    //查找职工信息
	void Find_Emp();

	//按照编号排序
	void Sort_Emp();

	//清空所有文档
	void Clean_File();


    //声明析构函数
    ~WorkerManager();
    





    //声明记录职工人数,并初始化为0
    int m_EmpNum;
    //职工数组指针,指向职工数组的指针,用于存放职工对象,用于管理职工
    Worker **m_EmpArray;
    //判断文件是否为空
    bool m_FileIsEmpty;

};



