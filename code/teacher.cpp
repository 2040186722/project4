#include "teacher.h"
#include "course.h"

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