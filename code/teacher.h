#pragma once
#include "user.h"
#include <string>
#include <vector>

class Course;

class Teacher:public User
{
	public:
		Teacher();
		~Teacher();
		std::vector<Course*>& getCourse();
		bool addCourse(const Course* newCourse);
		bool decCourse(const Course* course1);
		void popClass(const Course* course1);
	private:
		std::vector<Course*> course;
};