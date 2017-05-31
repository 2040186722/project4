#include "client.h"
using namespace std;

void studentClient(Student* student, std::map<std::string, Student*>& students, vector<Course*>& courses, const bool isBeginChooseCourse)
{
	int command2, flag;
	char command1;
	string s, title;
	refreshPage("studentMain", student->getName());
	command1 = _getch();
	while (command1 != '0')
	{
		switch (command1)
		{
		case '1':
			refreshPage("notice", student->getName());
			_getch();
			break;
		case '2':
		{
			string title = "选课系统 >> ";
			title = title + student->getName() + "(学生) >> 查看全部课程";
			listCourses(courses, title);
			cout << "按任意键返回..." << endl;
			_getch();
			break;
		}
		case '3':
		{
			string title = "选课系统 >> ";
			title = title + student->getName() + "(学生) >> 查看我的课程";
			listCourses(student->getCourse(), title);
			cout << "按任意键返回..." << endl;
			_getch();
			break;
		}
		case '4':
		{
			string title = "选课系统 >> ";
			title = title + student->getName() + "(学生) >> 选择课程";
			if (!isBeginChooseCourse)
			{
				system("cls");
				cout << title << "\n\n选课尚未开放，请与管理员联系，按任意键返回...";
			}
			else
			{
				listCourses(courses, title);
				cout << "请输入你要选择的课程序号：";
				cin >> command2;
				if (command2 > courses.size() || command2 <= 0)
					cout << "添加失败，找不到这门课程，按任意键返回...";
				else
				{
					flag = student->addCourse(courses[command2 - 1]);
					printStudentsAndCourses(students);
					switch (flag)
					{
					case 0:
						cout << "添加成功，按任意键返回...";
						break;
					case 1:
						cout << "你已选过这门课，按任意键返回...";
						break;
					case 2:
						cout << "添加失败，与现有课程时间冲突，按任意键返回...";
						break;
					case 3:
						cout << "添加失败，该课程学生人数已满，按任意键返回...";
						break;
					}
				}
			}
			_getch();
			break;
		}
		case '5':
		{
			string title = "选课系统 >> ";
			title = title + student->getName() + "(学生) >> 退选课程";
			if (!isBeginChooseCourse)
			{
				system("cls");
				cout << title << "\n\n选课尚未开放，请与管理员联系，按任意键返回...";
			}
			else
			{
				listCourses(student->getCourse(), title);
				cout << "请输入你要退选的课程序号：";
				cin >> command2;
				if (command2 > student->getCourse().size() || command2 <= 0)
					cout << "退课失败，找不到这门课程，按任意键返回...";
				else
				{
					student->decCourse(student->getCourse()[command2 - 1]);
					printStudentsAndCourses(students);
					cout << "退课成功，按任意键返回...";
				}
			}
			_getch();
			break;
		}
		case '6':
			printCourseTimetable(student->getCourse(), student->getName());
			cout << "\n按任意键返回...";
			_getch();
			break;
		case '7':
			title = "选课系统 >> ";
			title = title + student->getName() + "(学生) >> 修改密码";
			changePassword(student, title);
			printStudentsAccount(students);
			break;
		case '8':
			Mail mail;
			system("cls");
			mail.id = student->getAccountId();
			mail.name = student->getName();
			cout << "选课系统 >> " << student->getName() << "(学生) >> 意见反馈\n\n主题：";
			cin >> s;
			mail.subject = s;
			cout << "内容：";
			cin >> s;
			mail.body = s;
			printMail(mail);
			cout << "发送成功，请等待管理员处理，按任意键返回..." << endl;
			_getch();
			break;
		}
		refreshPage("studentMain", student->getName());
		command1 = _getch();
	}
}

void teacherClient(Teacher* teacher, std::map<std::string, Teacher*>& teachers, std::map<std::string, Student*>& students, vector<Course*>& courses)
{
	int command2, x;
	char command1;
	string s, title;
	refreshPage("teacherMain", teacher->getName());
	command1 = _getch();
	while (command1 != '0')
	{
		switch (command1)
		{
		case '1':
		{
			string title = "选课系统 >> ";
			title = title + teacher->getName() + "(教师) >> 查看全部课程";
			listCourses(courses, title);
			cout << "按任意键返回..." << endl;
			_getch();
			break;
		}
		case '2':
		{
			string title = "选课系统 >> ";
			title = title + teacher->getName() + "(教师) >> 查看我的课程";
			listCourses(teacher->getCourse(), title);
			cout << "请输入你要查看的课程序号，按0返回：";
			cin >> command2;
			while (command2 != 0)
			{
				if (command2 <= teacher->getCourse().size() && command2 > 0)
				{
					vector<Course*> course1;
					course1.push_back(teacher->getCourse()[command2 - 1]);
					listCourses(course1, title);
					cout << "学生" << endl;
					for (auto i = teacher->getCourse()[command2 - 1]->getStudent().begin(); i != teacher->getCourse()[command2 - 1]->getStudent().end(); ++i)
						cout << (*i)->getAccountId() << ", " << (*i)->getName() << endl;
					cout << "\n\n按任意键返回...";
					_getch();
				}
				listCourses(teacher->getCourse(), title);
				cout << "请输入你要查看的课程序号，按0返回：";
				cin >> command2;
			}
			break;
		}
		case '3':
		{
			system("cls");
			string title = "选课系统 >> ";
			title = title + teacher->getName() + "(教师) >> 修改我的课程";
			listCourses(teacher->getCourse(), title);
			cout << "请输入你要修改的课程序号：";
			cin >> command2;
			command2--;
			if (command2 > teacher->getCourse().size() - 1 || command2 < 0)
				cout << "修改失败，找不到这门课程，按任意键返回...";
			else
			{
				system("cls");
				cout << "选课系统 >> " << teacher->getName() + "(教师) >> 修改我的课程\n\n";
				cout << "请输入新课程名称：";
				cin >> s;
				teacher->getCourse()[command2]->setCourseName(s);
				readCourseFromScreen(teacher->getCourse()[command2]);
				printTeachersAndCourses(teachers);
				printStudentsAndCourses(students);
				cout << "修改成功，按任意键返回...";
			}
			_getch();
			break;
		}
		case '4':
		{
			system("cls");
			cout << "选课系统 >> " << teacher->getName() << "(教师) >> 新增课程\n\n";
			cout << "请输入课程名称：";
			cin >> s;
			Course* newCourse = new Course(s, teacher);
			readCourseFromScreen(newCourse);
			teacher->addCourse(newCourse);
			courses.push_back(newCourse);
			printTeachersAndCourses(teachers);
			cout << "添加成功，按任意键返回..." << endl;
			_getch();
			break;
		}
		case '5':
		{
			system("cls");
			string title = "选课系统 >> ";
			title = title + teacher->getName() + "(教师) >> 删除课程";
			listCourses(teacher->getCourse(), title);
			cout << "请输入你要删除的课程序号：";
			cin >> command2;
			if (command2 > teacher->getCourse().size() || command2 <= 0)
				cout << "删除失败，找不到这门课程，按任意键返回...";
			else
			{
				for (auto i = courses.begin(); i != courses.end(); ++i)
					if ((*i) == teacher->getCourse()[command2 - 1])
					{
						courses.erase(i);
						break;
					}
				teacher->decCourse(teacher->getCourse()[command2 - 1]);
				printTeachersAndCourses(teachers);
				printStudentsAndCourses(students);
				cout << "删除成功，按任意键返回...";
			}
			_getch();
			break;
		}
		case '6':
			system("cls");
			cout << "选课系统 >> " << teacher->getName() << "(教师) >> 发布公告\n\n内容：";
			cin >> s;
			printNotice(s);
			cout << "发布成功，按任意键返回..." << endl;
			_getch();
			break;
		case '7':
			title = "选课系统 >> ";
			title = title + teacher->getName() + "(教师) >> 修改密码";
			changePassword(teacher, title);
			printTeachersAccount(teachers);
			break;
		case '8':
			Mail mail;
			system("cls");
			mail.id = teacher->getAccountId();
			mail.name = teacher->getName();
			cout << "选课系统 >> " << teacher->getName() << "(教师) >> 意见反馈\n\n主题：";
			cin >> s;
			mail.subject = s;
			cout << "内容：";
			cin >> s;
			mail.body = s;
			printMail(mail);
			cout << "发送成功，请等待管理员处理，按任意键返回..." << endl;
			_getch();
			break;
		}
		refreshPage("teacherMain", teacher->getName());
		command1 = _getch();
	}
}

void administratorClient(map<std::string, Teacher*>& teachers, map<std::string, Student*>& students, vector<Course*>& courses, User* admin, bool& isBeginChooseCourse)
{
	int x;
	bool flag1;
	char command1, command2;
	string s, s1, title;
	vector<Mail> mails;
	readMails(mails);
	refreshPage("adminMain");
	while ((command1 = _getch()) != '0')
	{
		switch (command1)
		{
		case '1':
			refreshPage("adminCourseOption");
			while ((command2 = _getch()) != '0')
			{
				switch (command2)
				{
				case '1':
					isBeginChooseCourse = true;
					system("cls");
					printFlag(isBeginChooseCourse);
					cout << "选课系统 >> 管理员 >> 更改选课状态\n\n修改成功，按任意键返回...";
					_getch();
					break;
				case '2':
					isBeginChooseCourse = false;
					system("cls");
					printFlag(isBeginChooseCourse);
					cout << "选课系统 >> 管理员 >> 更改选课状态\n\n修改成功，按任意键返回...";
					_getch();
					break;
				}
				refreshPage("adminCourseOption");
			}
			break;
		case '2':
			listCourses(courses, "选课系统 >> 管理员 >> 查看课程列表");
			cout << "按任意键返回..." << endl;
			_getch();
			break;
		case '3':
			listStudents(students);
			cout << "按任意键返回..." << endl;
			_getch();
			break;
		case '4':
			listTeachers(teachers);
			cout << "按任意键返回..." << endl;
			_getch();
			break;
		case '5':
			refreshPage("adminReviseCourse");
			while ((command2 = _getch()) != '0')
			{
				switch (command2)
				{
				case '1':
				{
					system("cls");
					cout << "选课系统 >> 管理员 >> 课程管理 >> 新增课程\n\n" << endl;
					cout << "请输入课程名称：";
					cin >> s;
					cout << "请输入教师工号：";
					cin >> s1;
					if (teachers.count(s1) == 0)
						cout << "该工号不存在，按任意键返回..." << endl;
					else
					{
						Course* newCourse = new Course(s, teachers[s1]);
						readCourseFromScreen(newCourse);
						teachers[s1]->addCourse(newCourse);
						courses.push_back(newCourse);
						printTeachersAndCourses(teachers);
						cout << "添加成功，按任意键返回..." << endl;
					}
					_getch();
					break;
				}
				case '2':
					system("cls");
					flag1 = false;
					cout << "选课系统 >> 管理员 >> 课程管理 >> 修改课程\n\n" << endl;
					cout << "请输入原课程名称：";
					cin >> s;
					for (auto i = courses.begin(); i != courses.end(); ++i)
						if ((*i)->getName() == s)
						{
							cout << "请输入新课程名称：";
							cin >> s;
							cout << "请输入教师工号：";
							cin >> s1;
							if (teachers.count(s1) == 0)
								cout << "该工号不存在，按任意键返回..." << endl;
							else
							{
								(*i)->setCourseName(s);
								(*i)->setTeacher(teachers[s1]);
								readCourseFromScreen(*i);
								printTeachersAndCourses(teachers);
								printStudentsAndCourses(students);
								cout << "修改成功，按任意键返回..." << endl;
							}
							flag1 = true;
							break;
						}
					if (!flag1)
						cout << "修改失败，无法找到该课程，按任意键返回..." << endl;
					_getch();
					break;
				case '3':
					system("cls");
					flag1 = false;
					cout << "选课系统 >> 管理员 >> 课程管理 >> 删除课程\n\n" << endl;
					cout << "请输入课程名称：";
					cin >> s;
					for (auto i = courses.begin(); i != courses.end(); ++i)
						if ((*i)->getName() == s)
						{
							delete (*i);
							courses.erase(i);
							flag1 = true;
							printTeachersAndCourses(teachers);
							printStudentsAndCourses(students);
							cout << "删除成功，按任意键返回..." << endl;
							break;
						}
					if (!flag1)
						cout << "删除失败，无法找到该课程，按任意键返回..." << endl;
					_getch();
					break;
				}
				refreshPage("adminReviseCourse");
			}
			break;
		case '6':
			refreshPage("adminReviseAccount");
			while ((command2 = _getch()) != '0')
			{
				switch (command2)
				{
				case '1':
				{
					system("cls");
					cout << "选课系统 >> 管理员 >> 用户管理 >> 新增学生账户\n\n\n";
					Student* newStudent = new Student;
					cout << "请输入学生学号：";
					cin >> s;
					if (students.count(s) == 0)
					{
						students[s] = newStudent;
						newStudent->setAccountId(s);
						cout << "请输入学生姓名：";
						cin >> s;
						newStudent->setName(s);
						cout << "请输入账户密码：";
						cin >> s;
						newStudent->setPassword(s);
						printStudentsAccount(students);
						cout << "添加成功！，按任意键返回..." << endl;
					}
					else
						cout << "该学号已被注册，按任意键返回..." << endl;
					_getch();
					break;
				}
				case '2':
					system("cls");
					cout << "选课系统 >> 管理员 >> 用户管理 >> 修改学生账户\n\n\n";
					cout << "请输入学生学号：";
					cin >> s;
					if (students.count(s) == 1)
					{
						Student* student = students[s];
						cout << "请输入学生姓名：";
						cin >> s;
						student->setName(s);
						cout << "请输入学生账户密码：";
						cin >> s;
						student->setPassword(s);
						printStudentsAccount(students);
						cout << "修改成功！，按任意键返回..." << endl;
					}
					else
						cout << "该学生账户不存在，按任意键返回..." << endl;
					_getch();
					break;
				case '3':
					system("cls");
					cout << "选课系统 >> 管理员 >> 用户管理 >> 删除学生账户\n\n\n";
					cout << "请输入学生学号：";
					cin >> s;
					if (students.count(s) == 1)
					{
						delete students[s];
						students.erase(s);
						printStudentsAccount(students);
						cout << "删除成功！按任意键返回..." << endl;
					}
					else
						cout << "该学生账户不存在，按任意键返回..." << endl;
					_getch();
					break;
				case '4':
				{
					system("cls");
					cout << "选课系统 >> 管理员 >> 用户管理 >> 新增教师账户\n\n\n";
					Teacher* newTeacher = new Teacher;
					cout << "请输入教师工号：";
					cin >> s;
					if (teachers.count(s) == 0)
					{
						teachers[s] = newTeacher;
						newTeacher->setAccountId(s);
						cout << "请输入教师姓名：";
						cin >> s;
						newTeacher->setName(s);
						cout << "请输入教师密码：";
						cin >> s;
						newTeacher->setPassword(s);
						printTeachersAccount(teachers);
						cout << "添加成功！，按任意键返回..." << endl;
					}
					else
						cout << "该工号已被注册，按任意键返回..." << endl;
					_getch();
					break;
				}
				case '5':
					system("cls");
					cout << "选课系统 >> 管理员 >> 用户管理 >> 修改教师账户\n\n\n";
					cout << "请输入教师工号：";
					cin >> s;
					if (teachers.count(s) == 1)
					{
						Teacher* teacher = teachers[s];
						cout << "请输入教师姓名：";
						cin >> s;
						teacher->setName(s);
						cout << "请输入教师账户密码：";
						cin >> s;
						teacher->setPassword(s);
						printTeachersAccount(teachers);
						cout << "修改成功！，按任意键返回..." << endl;
					}
					else
						cout << "该教师账户不存在，按任意键返回..." << endl;
					_getch();
					break;
				case '6':system("cls");
					cout << "选课系统 >> 管理员 >> 用户管理 >> 删除教师账户\n\n\n";
					cout << "请输入教师工号：";
					cin >> s;
					if (teachers.count(s) == 1)
					{
						for (auto i = teachers[s]->getCourse().begin(); i != teachers[s]->getCourse().end(); ++i)
							for (auto j = courses.begin(); j != courses.end();)
								if ((*i) == (*j))
								{
									courses.erase(j);
									j = courses.begin();
								}
								else
									++j;
						delete teachers[s];
						teachers.erase(s);
						printTeachersAccount(teachers);
						printTeachersAndCourses(teachers);
						printStudentsAndCourses(students);
						cout << "删除成功！按任意键返回..." << endl;
					}
					else
						cout << "该教师账户不存在，按任意键返回..." << endl;
					_getch();
					break;
				}
				refreshPage("adminReviseAccount");
			}
			break;
		case '7':
			system("cls");
			cout << "选课系统 >> 管理员 >> 发布公告\n\n内容：";
			cin >> s;
			printNotice(s);
			cout << "发布成功，按任意键返回..." << endl;
			_getch();
			break;
		case '8':
			title = "选课系统 >> 管理员 >> 修改密码";
			changePassword(admin, title);
			printAdminAccount(admin);
			break;
		case '9':
			system("cls");
			cout << "选课系统 >> 管理员 >> 收件箱\n\n选择一个序号来查看邮件" << endl;
			for (auto i = mails.rbegin(); i != mails.rend() && i - mails.rbegin() + 1 <= 9; ++i)
				cout << i - mails.rbegin() + 1 << "." << i->subject << "    <from " << i->id << ", " << i->name << ">" << endl;
			cout << "0.返回" << endl;
			while ((command2 = _getch()) != '0')
			{
				if (command2 >= '1'&&command2 <= '9' && command2 - '0' <= mails.size())
				{
					system("cls");
					command2 = command2 - '0';
					cout << "选课系统 >> 管理员 >> 收件箱\n\n发件人：" << mails[mails.size() - command2].name \
						<< ", " << mails[mails.size() - command2].id << "\n主题：" << mails[mails.size() - command2].subject \
						<< "\n正文：" << mails[mails.size() - command2].body << "\n\n按任意键返回..." << endl;
					_getch();
				}
				system("cls");
				cout << "选课系统 >> 管理员 >> 收件箱\n\n选择一个序号来查看邮件" << endl;
				for (auto i = mails.rbegin(); i != mails.rend() && i - mails.rbegin() + 1 <= 9; ++i)
					cout << i - mails.rbegin() + 1 << "." << i->subject << "    <from " << i->id << ", " << i->name << ">" << endl;
				cout << "0.返回" << endl;
			}
			break;
		}
		refreshPage("adminMain");
	}
}