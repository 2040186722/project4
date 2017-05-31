#include "student.h"
#include "course.h"

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