#include "course.h"

const std::string Course::dayName[Course::totalDaysInWeek] = { "周一","周二","周三","周四","周五","周六","周日" };

Course::Course(const std::string newName, Teacher* newTeacher)
{
	name = newName;
	teacher = newTeacher;
}

Course::~Course()
{
	teacher->popClass(this);
	for (auto i = student.begin(); i != student.end();)
	{
		(*i)->decCourse(this);
		i = student.begin();
	}
}

void Course::setCourseName(const std::string &courseName)
{
	name = courseName;
}

void Course::setTeacher(Teacher* newTeacher)
{
	teacher = newTeacher;
}

bool Course::setDay(const int newDay)
{
	if (newDay < 0 || newDay > 6)
		return false;
	day = newDay;
	return true;
}

bool Course::setBeginClass(const int newBeginClass)
{
	if (newBeginClass < 1 || newBeginClass > 15)
		return false;
	beginClass = newBeginClass;
	return true;
}

bool Course::setEndClass(const int newEndClass)
{
	if (newEndClass < beginClass || newEndClass > 15)
		return false;
	endClass = newEndClass;
	return true;
}

bool Course::setBeginWeek(const int newBeginWeek)
{
	if (newBeginWeek < 1)
		return false;
	beginWeek = newBeginWeek;
	return true;
}

bool Course::setEndWeek(const int newEndWeek)
{
	if (newEndWeek < beginWeek)
		return false;
	endWeek = newEndWeek;
	return true;
}

bool Course::setMaxStudents(const int max)
{
	if (max < 0)
		return false;
	maxStudents = max;
	return true;
}

void Course::setPlace(const std::string newPlace) 
{
	place = newPlace;
}

std::string Course::getName() const
{
	return name;
}

int Course::getDay() const
{
	return day;
}

int Course::getBeginClass() const
{
	return beginClass;
}

int Course::getEndClass() const
{
	return endClass;
}

int Course::getBeginWeek() const
{
	return beginWeek;
}

int Course::getEndWeek() const
{
	return endWeek;
}

int Course::getMaxStudents() const
{
	return maxStudents;
}

std::string Course::getPlace() const 
{
	return place;
}

Teacher* Course::getTeacher() const
{
	return teacher;
}

std::vector<Student*>& Course::getStudent()
{
	return student;
}

bool Course::isInClass(const int week1, const int day1, const int class1) const
{
	if (week1 >= beginWeek && week1 <= endWeek && day1 == day && class1 >= beginClass && class1 <= endClass)
		return true;
	return false;
}

int Course::addStudent(Student* newStudent)
{
	if (student.size() == maxStudents)
		return 1;
	for (auto i = student.begin(); i != student.end(); ++i)
		if (*i == newStudent)
			return 2;
	student.push_back(newStudent);
	newStudent->addCourse(this);
	return 0;
}

bool Course::decStudent(Student* student1) 
{
	for (auto i = student.begin(); i != student.end(); ++i)
		if (*i == student1) 
		{
			student.erase(i);
			student1->decCourse(this);
			return true;
		}
	return false;
}

std::string Course::timeToString()
{
	std::ostringstream ostr;
	ostr << dayName[day] << beginClass << "-" << endClass << "节, 第" << beginWeek << "周到第" << endWeek << "周";
	return ostr.str();
}