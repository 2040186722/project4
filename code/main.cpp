#include "course.h"
#include "user.h"
#include "student.h"
#include "teacher.h"
#include "readAndPrint.h"
#include "client.h"
#include <conio.h>
#include <map>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
using namespace std;

void HideCursor();

int main() 
{
	char command;
	bool isBeginChooseCourse;
	string id, password;
	vector<Course*> courses;
	map<std::string, Teacher*> teachers;
	map<std::string, Student*> students;
	User* administrator = new User;
	HideCursor();
	readAllData(teachers, students, courses, administrator, isBeginChooseCourse);
	refreshPage("main");
	command = _getch();
	while(command != '0')
	{
		switch (command)
		{
			case '1':
				loginIn(id, password, "选课系统 >> 账户登录 >> 学生账户登录", "请输入学号：", "请输入密码：");
				while(students.count(id)==0 || !students[id]->login(password))
					loginIn(id, password, "选课系统 >> 账户登录 >> 学生账户登录", "请输入学号：", "请输入密码：", "学号或密码错误，请重新输入");
				studentClient(students[id], students, courses, isBeginChooseCourse);
				break;
			case '2':
				loginIn(id, password, "选课系统 >> 账户登录 >> 教师账户登录", "请输入工号：", "请输入密码：");
				while (teachers.count(id) == 0 || !teachers[id]->login(password))
					loginIn(id, password, "选课系统 >> 账户登录 >> 教师账户登录", "请输入工号：", "请输入密码：", "工号或密码错误，请重新输入");
				teacherClient(teachers[id], teachers, students, courses);
				break;
			case '3':
				loginIn(id, password, "选课系统 >> 账户登录 >> 管理员账户登录", "请输入账号(默认账号为admin)：", "请输入密码(默认密码为0000)：");
				while (administrator->getAccountId() != id || !administrator->login(password))
					loginIn(id, password, "选课系统 >> 账户登录 >> 管理员账户登录", "请输入账号(默认账号为admin)：", "请输入密码(默认密码为0000)：", "账号或密码错误，请重新输入");
				administratorClient(teachers, students, courses, administrator, isBeginChooseCourse);
				break;
		}
		refreshPage("main");
		command = _getch();
	}
	for (auto i = courses.begin(); i != courses.end(); i++)
		delete (*i);
	for (auto i = students.begin(); i != students.end(); i++)
		delete i->second; 
	for (auto i = teachers.begin(); i != teachers.end(); i++)
		delete i->second;
	delete administrator;
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}