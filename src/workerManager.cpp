//
// Created by kikib on 24-12-
#include "../include/workerManager.h"


//定义构造函数
WorkerManager::WorkerManager()
{
	//1.文件不存在时初始化
    ifstream ifs;
	ifs.open(FILENAME, ios::in); //输入流对象打开文件
    if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		//初始化属性
		//初始化职工人数
		this->m_EmpNum = 0;
		//初始化职工数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		//关闭文件
		ifs.close();
		return;
    }
	//2.文件存在,数据为空
	char ch;
    ifs >> ch;
    if (ifs.eof()) {
		cout << "文件为空" << endl;
		//初始化属性
		//初始化职工人数
		this->m_EmpNum = 0;
		//初始化职工数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		//关闭文件
		ifs.close();
		return;

    }
	//3.文件存在且记录数据
	int num = this->get_EmpNum();
	cout << "职工人数为:" << num << endl;
	//初始化文件属性
	this->m_FileIsEmpty = false;
	this->m_EmpNum = num;
	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据存到数组中
	this->init_Emp();

	//测试代码
    /*for(int i = 0; i < this->m_EmpNum; i++)
    {
        cout << "职工编号:" << this->m_EmpArray[i]->m_Id
            << "姓名:" << this->m_EmpArray[i]->m_Name
            << "岗位:" << this->m_EmpArray[i]->m_Department << endl;
    }*/
}

//定义显示职工函数
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->ShowInfo();
		}
	}
}

//判断职工是否存在,若存在返回职工在数组中的位置,不存在返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//定义删除职工函数
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入想要删除的职工编号:" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)
		{
			//找到职工
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			//同步更新到文件中
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败,未找到该职工" << endl;
		}
	}
}

//定义修改职工函数
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号:" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int department = 0;
			cout << "查到:" << id << "号职工,请输入新职工编号:" << endl;
			cin >> newId;
			cout << "请输入新职工姓名:" << endl;
			cin >> newName;
			cout << "请输入新职工岗位:" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> department;
			Worker* worker = NULL;
			switch (department)
			{
			case 1:
				worker = new Employees(newId, newName, department);
				break;
			case 2:
				worker = new Manager(newId, newName, department);
				break;
			case 3:
				worker = new Boss(newId, newName, department);
				break;
			default:
				break;
			}
			this->m_EmpArray[ret] = worker;
			cout << "修改成功" << endl;
			this->save();
		}
		else
		{
			cout << "修改失败,未找到该职工" << endl;
		}
	}
}

//定义查找职工函数
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式:" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "请输入查找的职工编号:" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功,该职工信息如下:" << endl;
				this->m_EmpArray[ret]->ShowInfo();
			}
			else
			{
				cout << "查找失败,未找到该职工" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入查找的职工姓名:" << endl;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功,职工编号为:" << this->m_EmpArray[i]->m_Id << "的职工信息如下:" << endl;
					this->m_EmpArray[i]->ShowInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查找失败,未找到该职工" << endl;
			}
		}
		else
		{
			cout << "输入有误" << endl;
		}
	}
}

//定义按照编号排序函数
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请选择排序方式:" << endl;
		cout << "1.升序" << endl;
		cout << "2.降序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else if (select == 2)
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功,排序后的结果如下:" << endl;
		this->save();
		this->Show_Emp();
	}
}

//定义清空所有文档函数
void WorkerManager::Clean_File()
{
	cout << "确认清空所有文档吗?" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = NULL;
				}
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功" << endl;
	}
}


//定义静态函数菜单
void WorkerManager::Show_Menu()
{
    cout << "*******欢迎使用职工管理系统*******" << endl;
    cout << "******** 0.退出管理程序 ********" << endl;
    cout << "******** 1.增加职工信息 ********" << endl;
    cout << "******** 2.显示职工信息 ********" << endl;
    cout << "******** 3.删除离职职工 ********" << endl;
    cout << "******** 4.修改职工信息 ********" << endl;
    cout << "******** 5.查找职工信息 ********" << endl;
    cout << "******** 6.按照编号排序 ********" << endl;
    cout << "******** 7.清空所有文档 ********" << endl;
    cout << "******************************" << endl;
    cout<<endl;
}
//定义退出系统函数
void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}
//统计职工人数
int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME,ios::in);
    int id;
	string name;
	int department;
	int num = 0;
    while (ifs >> id && ifs >> name&&  ifs >> department)
    {
        num++;
    }
    return num;
}
//初始化职工
void WorkerManager::init_Emp(){
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int department;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> department)
    {
        Worker* worker = NULL;
        if (department == 1) {
            worker = new Employees(id, name, department);
        }
        else if (department == 2) {
            worker = new Manager(id, name, department);
        }
        else if (department == 3) {
            worker = new Boss(id, name, department);
        }
        else {
			cerr << "文件数据有误" << endl;
			return;
        }
        this->m_EmpArray[index] = worker;
        index++;
    }
    ifs.close();
}
//保存函数
void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//用输出的方式打开文件,相当于清空文件
	//将每个人数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_Department << endl;
	}
	cout << "保存成功" << endl;
	ofs.close();//关闭文件
}

//定义增加职工函数
void WorkerManager::Add_Emp() {
    cout << "请输入要添加的职工人数(必须为大于0的整数):" << endl;
    int addNum = 0;
    cin >> addNum;

    if (addNum > 0) {
        //计算新空间大小
        int newSize = m_EmpNum + addNum;
        //开辟新空间
        Worker** newSpace = new Worker * [newSize];

        //将原来空间下数据存放到新空间下
        if (this->m_EmpArray != NULL) {
            for (int i = 0;i<this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

     

        // 添加新数据
        for (int i = 0; i < addNum; i++) {
            int id;
            string name;
            int department;

            cout << "请输入第" << i + 1 << "个职工编号:" << endl;
            if (!(cin >> id)) {
                cerr << "输入职工编号错误！" << endl;
                delete[] m_EmpArray; // 释放内存
                return;
            }

            cout << "请输入第" << i + 1 << "个职工姓名:" << endl;
            if (!(cin >> name)) {
                cerr << "输入职工姓名错误！" << endl;
                delete[] m_EmpArray; // 释放内存
                return;
            }

            cout << "请选择该职工岗位:" << endl;
            cout << "1.普通职工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            if (!(cin >> department)) {
                cerr << "输入职工岗位错误！" << endl;
                delete[] m_EmpArray; // 释放内存
                return;
            }

            //根据用户选择创建不同对象
            Worker* worker = NULL;
            switch (department) {
            case 1:
                worker = new Employees(id, name, department);
                break;
            case 2:
                worker = new Manager(id, name, department);
                break;
            case 3:
                worker = new Boss(id, name, department);
                break;
            default:
                cerr << "输入的岗位选择无效！" << endl;
                delete[] m_EmpArray; // 释放内存
                return;
            }

            //存储到数组中
            newSpace[this->m_EmpNum + i] = worker;
        }
		//释放原有空间
		delete[]this->m_EmpArray;
		//更新空间指向
		this->m_EmpArray = newSpace;
		//更新新的职工人数
		this->m_EmpNum = newSize;
		//更新职工不为空标志
		this->m_FileIsEmpty = false;
        cout << "成功添加" <<addNum<< "名职工" << endl;
        this->save();
    }
    else {
        cout << "输入有误,请重新输入" << endl;
        // 释放内存
        return;
    }
    system("cls");//清屏
	cout << "添加操作已经完成,自动为你清屏" << endl;
    return;
}
//定义析构函数
WorkerManager::~WorkerManager()
{
	//释放职工数组
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
