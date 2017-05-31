#include "user.h"
#include "course.h"

User::User()
{
}

User::~User()
{
}

bool User::setName(const std::string &name1)
{
	name = name1;
	return true;
}

bool User::setAccountId(const std::string &accountId1)
{
	accountId = accountId1;
	return true;
}

bool User::setPassword(const std::string &password1)
{
	password = password1;
	return true;
}

std::string User::getName() const
{
	return name;
}

std::string User::getAccountId() const
{
	return accountId;
}

std::string User::getPassword() const
{
	return password;
}

bool User::login(const std::string &password1) const
{
	if (password == password1)
		return true;
	return false;
}


Student::Student()
{
}

Student::~Student()
{
	for (auto i = course.begin(); i != course.end();)
	{
		this->decCourse(*i);
		i = course.begin();
	}
}

std::vector<Course*>& Student::getCourse()
{
	return course;
}

int Student::addCourse(Course* newCourse)
{
	for (auto i = course.begin(); i != course.end(); ++i)
		if ((*i) == newCourse)
			return 1;
	for (auto i = course.begin(); i != course.end(); ++i)
		for (int j = newCourse->getBeginWeek(); j <= newCourse->getEndWeek(); j++)
			for (int k = newCourse->getBeginClass(); k <= newCourse->getEndClass(); k++)
				if ((*i)->isInClass(j, newCourse->getDay(), k))
					return 2;
	if (newCourse->getMaxStudents() - newCourse->getStudent().size() == 0)
		return 3;
	course.push_back(newCourse);
	newCourse->addStudent(this);
	return 0;
}

bool Student::decCourse(Course* course1)
{
	for (auto i = course.begin(); i != course.end(); ++i)
		if (*i == course1)
		{
			course.erase(i);
			course1->decStudent(this);
			return true;
		}
	return false;
}

Teacher::Teacher()
{
}

Teacher::~Teacher()
{
	for (auto i = course.begin(); i != course.end();)
	{
		delete (*i);
		i = course.begin();
	}
}

std::vector<Course*>& Teacher::getCourse()
{
	return course;
}

bool Teacher::addCourse(const Course* newCourse)
{
	for (auto i = course.begin(); i != course.end(); ++i)
		for (int j = newCourse->getBeginWeek(); j <= newCourse->getEndWeek(); j++)
			for (int k = newCourse->getBeginClass(); k <= newCourse->getEndClass(); k++)
				if ((*i)->isInClass(j, newCourse->getDay(), k))
					return false;
	course.push_back((Course*)newCourse);
	return true;
}

bool Teacher::decCourse(const Course* course1)
{
	for (auto i = course.begin(); i != course.end(); ++i)
		if (*i == course1)
		{
			delete course1;
			return true;
		}
	return false;
}

void Teacher::popClass(const Course* course1) {
	for (auto i = course.begin(); i != course.end(); ++i)
		if (*i == course1) {
			course.erase(i);
			break;
		}
}