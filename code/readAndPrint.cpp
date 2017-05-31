#include "readAndPrint.h"

bool readPhrase(char*& line, std::string& s)
{
	s = "";
	while (*(line) != ',' && *(line) != '\0')
	{
		s = s + *(line);
		line++;
	}
	if (*(line) == '\0')
		return false;
	line++;
	return true;
}

/*id，密码，名字*/
void readUser(char* line, User* user)
{
	std::string s;
	readPhrase(line, s);
	user->setAccountId(s);
	readPhrase(line, s);
	user->setPassword(s);
	readPhrase(line, s);
	user->setName(s);
}

void readAdminAccount(User* admin, const std::string path)
{
	char line[1010];
	std::string s;
	std::ifstream in(path);
	in.getline(line, 1000);
	readUser(line, admin);
}

void readTeachersAccount(std::map<std::string, Teacher*>& teachers, const std::string path)
{
	char line[1010];
	std::string s;
	std::ifstream in(path);
	while (in.getline(line, 1000))
	{
		Teacher* teacher = new Teacher();
		readUser(line, teacher);
		teachers[teacher->getAccountId()] = teacher;
	}
	in.close();
}

void readStudentsAccount(std::map<std::string, Student*>& students, const std::string path)
{
	char line[1010];
	std::string s;
	std::ifstream in(path);
	while (in.getline(line, 1000))
	{
		Student* student = new Student();
		readUser(line, student);
		students[student->getAccountId()] = student;
	}
	in.close();
}

/*id，课程（名称，星期，第几节开始/结束，第几周开始/结束，课堂成员上限，地点）。。。*/
void readTeachersAndCourses(std::map<std::string, Teacher*>& teachers, std::vector<Course*>& courses, const std::string path)
{
	char line[1010];
	std::string s;
	std::ifstream in(path);
	while (in.getline(line,1000)) 
	{
		char* line1 = line;
		readPhrase(line1, s);
		Teacher* teacher = teachers[s];
		while (readPhrase(line1, s))
		{
			Course* course = new Course(s, teacher);
			teacher->addCourse(course);
			courses.push_back(course);
			readPhrase(line1, s);
			course->setDay(std::atoi(s.c_str()));
			readPhrase(line1, s);
			course->setBeginClass(std::atoi(s.c_str()));
			readPhrase(line1, s);
			course->setEndClass(std::atoi(s.c_str()));
			readPhrase(line1, s);
			course->setBeginWeek(std::atoi(s.c_str()));
			readPhrase(line1, s);
			course->setEndWeek(std::atoi(s.c_str()));
			readPhrase(line1, s);
			course->setMaxStudents(std::atoi(s.c_str()));
			readPhrase(line1, s);
			course->setPlace(s);
		}
	}
	in.close();
}

/*id，课程。。。*/
void readStudentsAndCourses(std::map<std::string, Student*>& students, const std::vector<Course*>& courses, const std::string path)
{
	char line[1010];
	std::string s;
	std::ifstream in(path);
	while (in.getline(line, 1000))
	{
		char* line1 = line;
		readPhrase(line1, s);
		Student* student = students[s];
		s = "";
		while (readPhrase(line1, s))
			for (auto i = courses.begin(); i != courses.end(); ++i)
				if (s == (*i)->getName()) 
					(*i)->addStudent(student);
		if(s!="")
			for (auto i = courses.begin(); i != courses.end(); ++i)
				if (s == (*i)->getName())
					(*i)->addStudent(student);
	}
	in.close();
}

void readMails(std::vector<Mail>& mails, const std::string path)
{
	char line[1010];
	Mail mail;
	std::string s;
	std::ifstream in(path);
	mails.clear();
	while (in.getline(line, 1000))
	{
		char* line1 = line;
		readPhrase(line1, s);
		mail.id = s;
		readPhrase(line1, s);
		mail.name = s;
		readPhrase(line1, s);
		mail.subject = s;
		readPhrase(line1, s);
		mail.body = s;
		mails.push_back(mail);
	}
}

void readFlag(bool& isBeginChooseCourse, const std::string path)
{
	int x;
	std::ifstream in(path);
	in >> x;
	if (x)
		isBeginChooseCourse = true;
	else
		isBeginChooseCourse = false;
}

void readAllData(std::map<std::string, Teacher*>& teachers, std::map<std::string, Student*>& students, std::vector<Course*>& courses, User* admin, bool& isBeginChooseCourse)
{
	readTeachersAccount(teachers);
	readStudentsAccount(students);
	readAdminAccount(admin);
	readTeachersAndCourses(teachers, courses);
	readStudentsAndCourses(students, courses);
	readFlag(isBeginChooseCourse);
}

void readCourseFromScreen(Course* course) 
{
	int x;
	std::string s;
	std::cout << "请输入课程时间\n周几(1-7)：";
	std::cin >> x;
	course->setDay(x - 1);
	std::cout << "开始节数(1-15)：";
	std::cin >> x;
	course->setBeginClass(x);
	std::cout << "结束节数(1-15)：";
	std::cin >> x;
	course->setEndClass(x);
	std::cout << "开始周数(1-)：";
	std::cin >> x;
	course->setBeginWeek(x);
	std::cout << "结束周数(1-)：";
	std::cin >> x;
	course->setEndWeek(x);
	std::cout << "上课地点：";
	std::cin >> s;
	course->setPlace(s);
	std::cout << "最大人数：";
	std::cin >> x;
	course->setMaxStudents(x);
}

void readPasswordFromScreen(std::string& password)
{
	char c;
	password = "";
	c = _getch();
	while (c != 13)
	{
		if (c == 8 && password.size() > 0) {
			password.erase(password.end() - 1);
			moveCursor(-1, 0);
			std::cout << " ";
			moveCursor(-1, 0);
		}
		else if (c != 8)
		{
			std::cout << "*";
			password = password + c;
		}
		c = _getch();
	}
	std::cout << std::endl;
}

void loginIn(std::string& id, std::string& password, const std::string title, const std::string hint1, const std::string hint2, const std::string errorMessage) {
	system("cls");
	std::cout << title << "\n\n" << errorMessage << std::endl;
	std::cout << hint1;
	std::cin >> id;
	std::cout << hint2;
	readPasswordFromScreen(password);
}

void changePassword(User* user, std::string title) {
	std::string password, newPassword1, newPassword2;
	system("cls");
	std::cout << title << "\n\n\n请输入旧密码：";
	readPasswordFromScreen(password);
	while (!user->login(password))
	{
		system("cls");
		std::cout << title << "\n\n密码错误，请重新输入\n请输入旧密码：";
		readPasswordFromScreen(password);
	}
	std::cout << "请输入新密码：";
	readPasswordFromScreen(newPassword1);
	std::cout << "请再次输入新密码：";
	readPasswordFromScreen(newPassword2);
	while (newPassword1 != newPassword2)
	{
		system("cls");
		std::cout << title << "\n\n确认密码与新密码不符，请重新输入\n请输入旧密码：";
		for (int i = 0; i < password.size(); i++)
			std::cout << "*";
		std::cout << "\n请输入新密码：";
		readPasswordFromScreen(newPassword1);
		std::cout << "请再次输入新密码：";
		readPasswordFromScreen(newPassword2);
	}
	user->setPassword(newPassword1);
	std::cout << "修改成功，按任意键返回..." << std::endl;
	_getch();
}

void printTeachersAccount(const std::map<std::string, Teacher*>& teachers, const std::string path)
{
	std::ofstream out(path);
	for (auto i = teachers.begin(); i != teachers.end(); ++i)
		out << i->second->getAccountId() << "," << i->second->getPassword() << "," << i->second->getName() << std::endl;
	out.close();
}

void printStudentsAccount(const std::map<std::string, Student*>& students, const std::string path)
{
	std::ofstream out(path);
	for (auto i = students.begin(); i != students.end(); ++i)
		out << i->second->getAccountId() << "," << i->second->getPassword() << "," << i->second->getName() << std::endl;
	out.close();
}

void printAdminAccount(const User* admin, const std::string path)
{
	std::ofstream out(path);
	out << admin->getAccountId() << "," << admin->getPassword() << "," << admin->getName() << std::endl;
	out.close();
}

void printTeachersAndCourses(const std::map<std::string, Teacher*>& teachers, const std::string path)
{
	std::ofstream out(path);
	for (auto i = teachers.begin(); i != teachers.end(); ++i) 
	{
		out << i->second->getAccountId();
		for (auto j = i->second->getCourse().begin(); j != i->second->getCourse().end(); ++j)
			out << "," << (*j)->getName() << "," << (*j)->getDay() << "," << (*j)->getBeginClass() << "," << (*j)->getEndClass()\
				<< "," << (*j)->getBeginWeek() << "," << (*j)->getEndWeek() << "," << (*j)->getMaxStudents() << "," << (*j)->getPlace();
		out << std::endl;
	}
	out.close();
}

void printStudentsAndCourses(const std::map<std::string, Student*>& students, const std::string path)
{
	std::ofstream out(path);
	for (auto i = students.begin(); i != students.end(); ++i)
	{
		out << i->second->getAccountId();
		for (auto j = i->second->getCourse().begin(); j != i->second->getCourse().end(); ++j)
			out << "," << (*j)->getName();
		out << std::endl;
	}
	out.close();
}

void printMail(Mail mail, const std::string path)
{
	std::ofstream out(path, std::ios_base::app);
	out << mail.id << "," << mail.name << "," << mail.subject << "," << mail.body << std::endl;
}

void printFlag(bool flag, const std::string path)
{
	std::ofstream out(path);
	out << flag ? 1 : 0;
}

void printNotice(std::string notice, const std::string path)
{
	std::ofstream out(path);
	out << "选课系统 >> %s(学生) >> 查看公告\n\n内容：" << notice << "\n\n按任意键返回...";
	out.close();
}

void refreshPage(std::string pageName, std::string name)
{
	char line[1010];
	std::string path = "Page/" + pageName + ".txt";
	std::ifstream in(path);
	system("cls");
	if (name != "") 
	{
		in.getline(line, 1000);
		printf(line, name.c_str());
		printf("\n");
	}
	while (in.getline(line, 1000))
		std::cout << line << std::endl;
	in.close();
}

void listCourses(const std::vector<Course*>& courses, std::string title)
{
	system("cls");
	std::cout << title << "\n" << std::endl;
	std::cout.setf(std::ios::left);
	std::cout << std::setw(10) << "序号" << std::setw(20) << "课程" << std::setw(15) << "上课老师" << std::setw(10) << "人数上限" << std::setw(10) << "已选人数" \
		<< std::setw(32) << "上课时间" << "地点" << std::endl;
	for (auto i = courses.begin(); i != courses.end(); ++i)
		std::cout << std::setw(10) << i - courses.begin() + 1 << std::setw(20) << (*i)->getName() << std::setw(15) << (*i)->getTeacher()->getName() << std::setw(10) \
		<< (*i)->getMaxStudents() << std::setw(10) << (*i)->getStudent().size() << std::setw(32) << (*i)->timeToString() << (*i)->getPlace() << std::endl;
	std::cout << "\n" << std::endl;
}

void listTeachers(const std::map<std::string, Teacher*>& teachers)
{
	system("cls");
	std::cout << "选课系统 >> 管理员 >> 查看教师信息\n" << std::endl;
	std::cout.setf(std::ios::left);
	std::cout << std::setw(12) << "工号" << std::setw(12) << "姓名" << std::setw(14) << "密码" << "开设课程" << std::endl;
	for (auto i = teachers.begin(); i != teachers.end(); ++i) {
		std::cout << std::setw(12) << i->second->getAccountId() << std::setw(12) << i->second->getName() << std::setw(14) << i->second->getPassword();
		bool flag = false;
		for (auto j = i->second->getCourse().begin(); j != i->second->getCourse().end(); ++j)
		{
			if (flag)
				std::cout << " & ";
			flag = true;
			std::cout << (*j)->getName();
		}
		if (!flag)
			std::cout << "无";
		std::cout << std::endl;
	}
	std::cout << "\n" << std::endl;
}

void listStudents(const std::map<std::string, Student*>& students)
{
	system("cls");
	std::cout << "选课系统 >> 管理员 >> 查看学生信息\n" << std::endl;
	std::cout.setf(std::ios::left);
	std::cout << std::setw(12) << "学号" << std::setw(12) << "姓名" << std::setw(14) << "密码" << "所报课程" << std::endl;
	for (auto i = students.begin(); i != students.end(); ++i) {
		std::cout << std::setw(12) << i->second->getAccountId() << std::setw(12) << i->second->getName() << std::setw(14) << i->second->getPassword();
		bool flag = false;
		for (auto j = i->second->getCourse().begin(); j != i->second->getCourse().end(); ++j)
		{
			if (flag)
				std::cout << " & ";
			flag = true;
			std::cout << (*j)->getName();
		}
		if (!flag)
			std::cout << "无";
		std::cout << std::endl;
	}
	std::cout << "\n" << std::endl;
}

void printCourseTimetable(const std::vector<Course*>& courses, std::string name)
{
	int week;
	system("cls");
	std::cout << "选课系统 >> " << name << "(学生) >> 查看课表\n\n请输入当前周数：";
	std::cin >> week;
	std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "|            |       周一       |       周二       |       周三       |       周四       |       周五       |       周六       |       周日       |" << std::endl;
	std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	for(int i = 1; i <= 15; i++)
	{
		if (i <= 9)
			std::cout << "|   第0" << i << "节   |";
		else
			std::cout << "|   第" << i << "节   |";
		for (int j = 0; j <= 6; j++)
		{
			std::string courseName = "";
			for (auto k = courses.begin(); k != courses.end(); ++k)
				if ((*k)->isInClass(week, j, i))
					courseName = (*k)->getName();
			if(courseName.size()<=18)
				std::cout << std::setw((18 - courseName.size()) / 2) << "" << courseName << std::setw(18 - (18 - courseName.size()) / 2 - courseName.size()) << "" << "|";
			else
				std::cout << courseName << "|";
		}
		std::cout << std::endl;
		std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	}
}

void moveCursor(const short dx, const short dy)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	COORD coordScreen = { csbi.dwCursorPosition.X + dx, csbi.dwCursorPosition.Y + dy }; //光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordScreen);
}