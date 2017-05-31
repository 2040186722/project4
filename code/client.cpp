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
			string title = "ѡ��ϵͳ >> ";
			title = title + student->getName() + "(ѧ��) >> �鿴ȫ���γ�";
			listCourses(courses, title);
			cout << "�����������..." << endl;
			_getch();
			break;
		}
		case '3':
		{
			string title = "ѡ��ϵͳ >> ";
			title = title + student->getName() + "(ѧ��) >> �鿴�ҵĿγ�";
			listCourses(student->getCourse(), title);
			cout << "�����������..." << endl;
			_getch();
			break;
		}
		case '4':
		{
			string title = "ѡ��ϵͳ >> ";
			title = title + student->getName() + "(ѧ��) >> ѡ��γ�";
			if (!isBeginChooseCourse)
			{
				system("cls");
				cout << title << "\n\nѡ����δ���ţ��������Ա��ϵ�������������...";
			}
			else
			{
				listCourses(courses, title);
				cout << "��������Ҫѡ��Ŀγ���ţ�";
				cin >> command2;
				if (command2 > courses.size() || command2 <= 0)
					cout << "���ʧ�ܣ��Ҳ������ſγ̣������������...";
				else
				{
					flag = student->addCourse(courses[command2 - 1]);
					printStudentsAndCourses(students);
					switch (flag)
					{
					case 0:
						cout << "��ӳɹ��������������...";
						break;
					case 1:
						cout << "����ѡ�����ſΣ������������...";
						break;
					case 2:
						cout << "���ʧ�ܣ������пγ�ʱ���ͻ�������������...";
						break;
					case 3:
						cout << "���ʧ�ܣ��ÿγ�ѧ�����������������������...";
						break;
					}
				}
			}
			_getch();
			break;
		}
		case '5':
		{
			string title = "ѡ��ϵͳ >> ";
			title = title + student->getName() + "(ѧ��) >> ��ѡ�γ�";
			if (!isBeginChooseCourse)
			{
				system("cls");
				cout << title << "\n\nѡ����δ���ţ��������Ա��ϵ�������������...";
			}
			else
			{
				listCourses(student->getCourse(), title);
				cout << "��������Ҫ��ѡ�Ŀγ���ţ�";
				cin >> command2;
				if (command2 > student->getCourse().size() || command2 <= 0)
					cout << "�˿�ʧ�ܣ��Ҳ������ſγ̣������������...";
				else
				{
					student->decCourse(student->getCourse()[command2 - 1]);
					printStudentsAndCourses(students);
					cout << "�˿γɹ��������������...";
				}
			}
			_getch();
			break;
		}
		case '6':
			printCourseTimetable(student->getCourse(), student->getName());
			cout << "\n�����������...";
			_getch();
			break;
		case '7':
			title = "ѡ��ϵͳ >> ";
			title = title + student->getName() + "(ѧ��) >> �޸�����";
			changePassword(student, title);
			printStudentsAccount(students);
			break;
		case '8':
			Mail mail;
			system("cls");
			mail.id = student->getAccountId();
			mail.name = student->getName();
			cout << "ѡ��ϵͳ >> " << student->getName() << "(ѧ��) >> �������\n\n���⣺";
			cin >> s;
			mail.subject = s;
			cout << "���ݣ�";
			cin >> s;
			mail.body = s;
			printMail(mail);
			cout << "���ͳɹ�����ȴ�����Ա���������������..." << endl;
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
			string title = "ѡ��ϵͳ >> ";
			title = title + teacher->getName() + "(��ʦ) >> �鿴ȫ���γ�";
			listCourses(courses, title);
			cout << "�����������..." << endl;
			_getch();
			break;
		}
		case '2':
		{
			string title = "ѡ��ϵͳ >> ";
			title = title + teacher->getName() + "(��ʦ) >> �鿴�ҵĿγ�";
			listCourses(teacher->getCourse(), title);
			cout << "��������Ҫ�鿴�Ŀγ���ţ���0���أ�";
			cin >> command2;
			while (command2 != 0)
			{
				if (command2 <= teacher->getCourse().size() && command2 > 0)
				{
					vector<Course*> course1;
					course1.push_back(teacher->getCourse()[command2 - 1]);
					listCourses(course1, title);
					cout << "ѧ��" << endl;
					for (auto i = teacher->getCourse()[command2 - 1]->getStudent().begin(); i != teacher->getCourse()[command2 - 1]->getStudent().end(); ++i)
						cout << (*i)->getAccountId() << ", " << (*i)->getName() << endl;
					cout << "\n\n�����������...";
					_getch();
				}
				listCourses(teacher->getCourse(), title);
				cout << "��������Ҫ�鿴�Ŀγ���ţ���0���أ�";
				cin >> command2;
			}
			break;
		}
		case '3':
		{
			system("cls");
			string title = "ѡ��ϵͳ >> ";
			title = title + teacher->getName() + "(��ʦ) >> �޸��ҵĿγ�";
			listCourses(teacher->getCourse(), title);
			cout << "��������Ҫ�޸ĵĿγ���ţ�";
			cin >> command2;
			command2--;
			if (command2 > teacher->getCourse().size() - 1 || command2 < 0)
				cout << "�޸�ʧ�ܣ��Ҳ������ſγ̣������������...";
			else
			{
				system("cls");
				cout << "ѡ��ϵͳ >> " << teacher->getName() + "(��ʦ) >> �޸��ҵĿγ�\n\n";
				cout << "�������¿γ����ƣ�";
				cin >> s;
				teacher->getCourse()[command2]->setCourseName(s);
				readCourseFromScreen(teacher->getCourse()[command2]);
				printTeachersAndCourses(teachers);
				printStudentsAndCourses(students);
				cout << "�޸ĳɹ��������������...";
			}
			_getch();
			break;
		}
		case '4':
		{
			system("cls");
			cout << "ѡ��ϵͳ >> " << teacher->getName() << "(��ʦ) >> �����γ�\n\n";
			cout << "������γ����ƣ�";
			cin >> s;
			Course* newCourse = new Course(s, teacher);
			readCourseFromScreen(newCourse);
			teacher->addCourse(newCourse);
			courses.push_back(newCourse);
			printTeachersAndCourses(teachers);
			cout << "��ӳɹ��������������..." << endl;
			_getch();
			break;
		}
		case '5':
		{
			system("cls");
			string title = "ѡ��ϵͳ >> ";
			title = title + teacher->getName() + "(��ʦ) >> ɾ���γ�";
			listCourses(teacher->getCourse(), title);
			cout << "��������Ҫɾ���Ŀγ���ţ�";
			cin >> command2;
			if (command2 > teacher->getCourse().size() || command2 <= 0)
				cout << "ɾ��ʧ�ܣ��Ҳ������ſγ̣������������...";
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
				cout << "ɾ���ɹ��������������...";
			}
			_getch();
			break;
		}
		case '6':
			system("cls");
			cout << "ѡ��ϵͳ >> " << teacher->getName() << "(��ʦ) >> ��������\n\n���ݣ�";
			cin >> s;
			printNotice(s);
			cout << "�����ɹ��������������..." << endl;
			_getch();
			break;
		case '7':
			title = "ѡ��ϵͳ >> ";
			title = title + teacher->getName() + "(��ʦ) >> �޸�����";
			changePassword(teacher, title);
			printTeachersAccount(teachers);
			break;
		case '8':
			Mail mail;
			system("cls");
			mail.id = teacher->getAccountId();
			mail.name = teacher->getName();
			cout << "ѡ��ϵͳ >> " << teacher->getName() << "(��ʦ) >> �������\n\n���⣺";
			cin >> s;
			mail.subject = s;
			cout << "���ݣ�";
			cin >> s;
			mail.body = s;
			printMail(mail);
			cout << "���ͳɹ�����ȴ�����Ա���������������..." << endl;
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
					cout << "ѡ��ϵͳ >> ����Ա >> ����ѡ��״̬\n\n�޸ĳɹ��������������...";
					_getch();
					break;
				case '2':
					isBeginChooseCourse = false;
					system("cls");
					printFlag(isBeginChooseCourse);
					cout << "ѡ��ϵͳ >> ����Ա >> ����ѡ��״̬\n\n�޸ĳɹ��������������...";
					_getch();
					break;
				}
				refreshPage("adminCourseOption");
			}
			break;
		case '2':
			listCourses(courses, "ѡ��ϵͳ >> ����Ա >> �鿴�γ��б�");
			cout << "�����������..." << endl;
			_getch();
			break;
		case '3':
			listStudents(students);
			cout << "�����������..." << endl;
			_getch();
			break;
		case '4':
			listTeachers(teachers);
			cout << "�����������..." << endl;
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
					cout << "ѡ��ϵͳ >> ����Ա >> �γ̹��� >> �����γ�\n\n" << endl;
					cout << "������γ����ƣ�";
					cin >> s;
					cout << "�������ʦ���ţ�";
					cin >> s1;
					if (teachers.count(s1) == 0)
						cout << "�ù��Ų����ڣ������������..." << endl;
					else
					{
						Course* newCourse = new Course(s, teachers[s1]);
						readCourseFromScreen(newCourse);
						teachers[s1]->addCourse(newCourse);
						courses.push_back(newCourse);
						printTeachersAndCourses(teachers);
						cout << "��ӳɹ��������������..." << endl;
					}
					_getch();
					break;
				}
				case '2':
					system("cls");
					flag1 = false;
					cout << "ѡ��ϵͳ >> ����Ա >> �γ̹��� >> �޸Ŀγ�\n\n" << endl;
					cout << "������ԭ�γ����ƣ�";
					cin >> s;
					for (auto i = courses.begin(); i != courses.end(); ++i)
						if ((*i)->getName() == s)
						{
							cout << "�������¿γ����ƣ�";
							cin >> s;
							cout << "�������ʦ���ţ�";
							cin >> s1;
							if (teachers.count(s1) == 0)
								cout << "�ù��Ų����ڣ������������..." << endl;
							else
							{
								(*i)->setCourseName(s);
								(*i)->setTeacher(teachers[s1]);
								readCourseFromScreen(*i);
								printTeachersAndCourses(teachers);
								printStudentsAndCourses(students);
								cout << "�޸ĳɹ��������������..." << endl;
							}
							flag1 = true;
							break;
						}
					if (!flag1)
						cout << "�޸�ʧ�ܣ��޷��ҵ��ÿγ̣������������..." << endl;
					_getch();
					break;
				case '3':
					system("cls");
					flag1 = false;
					cout << "ѡ��ϵͳ >> ����Ա >> �γ̹��� >> ɾ���γ�\n\n" << endl;
					cout << "������γ����ƣ�";
					cin >> s;
					for (auto i = courses.begin(); i != courses.end(); ++i)
						if ((*i)->getName() == s)
						{
							delete (*i);
							courses.erase(i);
							flag1 = true;
							printTeachersAndCourses(teachers);
							printStudentsAndCourses(students);
							cout << "ɾ���ɹ��������������..." << endl;
							break;
						}
					if (!flag1)
						cout << "ɾ��ʧ�ܣ��޷��ҵ��ÿγ̣������������..." << endl;
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
					cout << "ѡ��ϵͳ >> ����Ա >> �û����� >> ����ѧ���˻�\n\n\n";
					Student* newStudent = new Student;
					cout << "������ѧ��ѧ�ţ�";
					cin >> s;
					if (students.count(s) == 0)
					{
						students[s] = newStudent;
						newStudent->setAccountId(s);
						cout << "������ѧ��������";
						cin >> s;
						newStudent->setName(s);
						cout << "�������˻����룺";
						cin >> s;
						newStudent->setPassword(s);
						printStudentsAccount(students);
						cout << "��ӳɹ����������������..." << endl;
					}
					else
						cout << "��ѧ���ѱ�ע�ᣬ�����������..." << endl;
					_getch();
					break;
				}
				case '2':
					system("cls");
					cout << "ѡ��ϵͳ >> ����Ա >> �û����� >> �޸�ѧ���˻�\n\n\n";
					cout << "������ѧ��ѧ�ţ�";
					cin >> s;
					if (students.count(s) == 1)
					{
						Student* student = students[s];
						cout << "������ѧ��������";
						cin >> s;
						student->setName(s);
						cout << "������ѧ���˻����룺";
						cin >> s;
						student->setPassword(s);
						printStudentsAccount(students);
						cout << "�޸ĳɹ����������������..." << endl;
					}
					else
						cout << "��ѧ���˻������ڣ������������..." << endl;
					_getch();
					break;
				case '3':
					system("cls");
					cout << "ѡ��ϵͳ >> ����Ա >> �û����� >> ɾ��ѧ���˻�\n\n\n";
					cout << "������ѧ��ѧ�ţ�";
					cin >> s;
					if (students.count(s) == 1)
					{
						delete students[s];
						students.erase(s);
						printStudentsAccount(students);
						cout << "ɾ���ɹ��������������..." << endl;
					}
					else
						cout << "��ѧ���˻������ڣ������������..." << endl;
					_getch();
					break;
				case '4':
				{
					system("cls");
					cout << "ѡ��ϵͳ >> ����Ա >> �û����� >> ������ʦ�˻�\n\n\n";
					Teacher* newTeacher = new Teacher;
					cout << "�������ʦ���ţ�";
					cin >> s;
					if (teachers.count(s) == 0)
					{
						teachers[s] = newTeacher;
						newTeacher->setAccountId(s);
						cout << "�������ʦ������";
						cin >> s;
						newTeacher->setName(s);
						cout << "�������ʦ���룺";
						cin >> s;
						newTeacher->setPassword(s);
						printTeachersAccount(teachers);
						cout << "��ӳɹ����������������..." << endl;
					}
					else
						cout << "�ù����ѱ�ע�ᣬ�����������..." << endl;
					_getch();
					break;
				}
				case '5':
					system("cls");
					cout << "ѡ��ϵͳ >> ����Ա >> �û����� >> �޸Ľ�ʦ�˻�\n\n\n";
					cout << "�������ʦ���ţ�";
					cin >> s;
					if (teachers.count(s) == 1)
					{
						Teacher* teacher = teachers[s];
						cout << "�������ʦ������";
						cin >> s;
						teacher->setName(s);
						cout << "�������ʦ�˻����룺";
						cin >> s;
						teacher->setPassword(s);
						printTeachersAccount(teachers);
						cout << "�޸ĳɹ����������������..." << endl;
					}
					else
						cout << "�ý�ʦ�˻������ڣ������������..." << endl;
					_getch();
					break;
				case '6':system("cls");
					cout << "ѡ��ϵͳ >> ����Ա >> �û����� >> ɾ����ʦ�˻�\n\n\n";
					cout << "�������ʦ���ţ�";
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
						cout << "ɾ���ɹ��������������..." << endl;
					}
					else
						cout << "�ý�ʦ�˻������ڣ������������..." << endl;
					_getch();
					break;
				}
				refreshPage("adminReviseAccount");
			}
			break;
		case '7':
			system("cls");
			cout << "ѡ��ϵͳ >> ����Ա >> ��������\n\n���ݣ�";
			cin >> s;
			printNotice(s);
			cout << "�����ɹ��������������..." << endl;
			_getch();
			break;
		case '8':
			title = "ѡ��ϵͳ >> ����Ա >> �޸�����";
			changePassword(admin, title);
			printAdminAccount(admin);
			break;
		case '9':
			system("cls");
			cout << "ѡ��ϵͳ >> ����Ա >> �ռ���\n\nѡ��һ��������鿴�ʼ�" << endl;
			for (auto i = mails.rbegin(); i != mails.rend() && i - mails.rbegin() + 1 <= 9; ++i)
				cout << i - mails.rbegin() + 1 << "." << i->subject << "    <from " << i->id << ", " << i->name << ">" << endl;
			cout << "0.����" << endl;
			while ((command2 = _getch()) != '0')
			{
				if (command2 >= '1'&&command2 <= '9' && command2 - '0' <= mails.size())
				{
					system("cls");
					command2 = command2 - '0';
					cout << "ѡ��ϵͳ >> ����Ա >> �ռ���\n\n�����ˣ�" << mails[mails.size() - command2].name \
						<< ", " << mails[mails.size() - command2].id << "\n���⣺" << mails[mails.size() - command2].subject \
						<< "\n���ģ�" << mails[mails.size() - command2].body << "\n\n�����������..." << endl;
					_getch();
				}
				system("cls");
				cout << "ѡ��ϵͳ >> ����Ա >> �ռ���\n\nѡ��һ��������鿴�ʼ�" << endl;
				for (auto i = mails.rbegin(); i != mails.rend() && i - mails.rbegin() + 1 <= 9; ++i)
					cout << i - mails.rbegin() + 1 << "." << i->subject << "    <from " << i->id << ", " << i->name << ">" << endl;
				cout << "0.����" << endl;
			}
			break;
		}
		refreshPage("adminMain");
	}
}