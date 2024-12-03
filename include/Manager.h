//
// Created by kikib on 24-12-3.
//

#pragma once
#include "woker.h"
//继承Worker类,声明Manager类,并重写Worker类的纯虚函数,实现多态
class Manager:public Worker{
public:
    //声明构造函数,初始化编号,姓名,部门,并调用父类构造函数
    Manager(int id, std::string name, int department);
    //声明方法,显示个人信息,重写父类纯虚函数,实现多态
    virtual void ShowInfo();
    //声明方法,获取岗位名称,重写父类纯虚函数,实现多态
    virtual string GetDepartment();
};



