#pragma once
#include "course.h"
#include "student.h"
#include "teacher.h"
#include "readAndPrint.h"
#include <conio.h>
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>

void studentClient(Student* student, std::map<std::string, Student*>& students, std::vector<Course*>& courses, bool isBeginChooseCourse);
void teacherClient(Teacher* teacher, std::map<std::string, Teacher*>& teachers, std::map<std::string, Student*>& students, std::vector<Course*>& courses);
void administratorClient(std::map<std::string, Teacher*>& teachers, std::map<std::string, Student*>& students, \
	std::vector<Course*>& courses, User* admin, bool& isBeginChooseCourse);

