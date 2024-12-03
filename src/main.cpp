#include <iostream>
#include "../include/woker.h"
#include "../include/employees.h"
#include "../include/Manager.h"
#include "../include/Boss.h"
#include "../include/workerManager.h"
using namespace std;


int main() {
    //实例化WorkerManager对象,并调用菜单函数
    int choice = 0;
    WorkerManager wm;
    //循环显示菜单
    while (true) {
        wm.Show_Menu(); //调用菜单函数
        cout << "请输入您的选择：" << endl; //提示用户输入
        cin >> choice; //接收用户选择
        switch (choice) {
        case 0: //退出系统
            wm.ExitSystem(); //调用退出系统函数
            break;
        case 1: //增加职工信息
            wm.Add_Emp(); //调用增加职工函数
            break;
        case 2: //显示职工信息
			wm.Show_Emp(); //调用显示职工函数
            break;
        case 3: //删除离职职工
			wm.Del_Emp(); //调用删除职工函数
            break;
        case 4: //修改职工信息
			wm.Mod_Emp(); //调用修改职工函数
            break;
        case 5: //查找职工信息
			wm.Find_Emp(); //调用查找职工函数
            break;
        case 6: //按照编号排序
			wm.Sort_Emp(); //调用排序函数
            break;
        case 7: //清空所有文档
			wm.Clean_File(); //调用清空文档函数
            break;
        default:
            break;

        }
		system("pause");
    }
	return 0;
}