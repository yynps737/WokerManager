//
// Created by kikib on 24-12-3.
//
#pragma once
#include <string>
#include <iostream>
using namespace std;

//声明Woker基类
class Worker {
public:
//声明纯虚函数,显示个人信息
    virtual void ShowInfo() = 0;
//声明纯虚函数,获取岗位名称
    virtual string GetDepartment() = 0;
    //声明编号
    int m_Id;
    //声明姓名
    string m_Name;
    //声明部门号
    int m_Department;

};

