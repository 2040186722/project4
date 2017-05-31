#pragma once
#include "user.h"
#include <string>
#include <vector>

class Course;

class Student:public User
{
public:
	Student();
	~Student();
	std::vector<Course*>& getCourse();
	int addCourse(Course* newCourse);
	bool decCourse(Course* course1);
private:
	std::vector<Course*> course;
};