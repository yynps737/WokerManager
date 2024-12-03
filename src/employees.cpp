//
// Created by kikib on 24-12-3.
//
#include "../include/employees.h"

//定义构造函数,初始化编号,姓名,部门,并调用父类构造函数
Employees::Employees(int id, std::string name, int department) {
    this->m_Id = id; //this指针指向当前对象,避免与形参重名,用this指针访问成员变量
    this->m_Name = name;//this指针指向当前对象,避免与形参重名,用this指针访问成员变量
    this->m_Department = department;//this指针指向当前对象,避免与形参重名,用this指针访问成员变量
}
//定义方法,显示个人信息
void Employees::ShowInfo() {
    std::cout<<"职工编号:"<<this->m_Id<<"\t"<<"职工姓名:"<<this->m_Name<<"\t"<<"岗位名称:"<<this->GetDepartment()<<std::endl;
}
//定义方法,获取岗位名称
string Employees::GetDepartment() {
    return string("员工");
}
