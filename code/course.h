#pragma once
#include "student.h"
#include "teacher.h"
#include <string>
#include <vector>
#include <sstream>

class Course
{
	public:
		static const int totalDaysInWeek = 7;
		Course(const std::string newName, Teacher* newTeacher);
		~Course();
		void setCourseName(const std::string &courseName);
		void setTeacher(Teacher* newTeacher);
		bool setDay(const int newDay);
		bool setBeginClass(const int newBeginClass);
		bool setEndClass(const int newEndClass);
		bool setBeginWeek(const int newBeginWeek);
		bool setEndWeek(const int newEndWeek);
		bool setMaxStudents(const int max);
		void setPlace(const std::string newPlace);
		std::string getName() const;
		int getDay() const;
		int getBeginClass() const;
		int getEndClass() const;
		int getBeginWeek() const;
		int getEndWeek() const;
		int getMaxStudents() const;
		std::string getPlace() const;
		Teacher* Course::getTeacher() const;
		std::vector<Student*>& getStudent();
		bool isInClass(const int week1, const int day1, const int class1) const;
		int addStudent(Student* newStudent);
		bool decStudent(Student* student1);
		std::string timeToString();
	private:
		static const std::string dayName[totalDaysInWeek];
		std::string name;
		Teacher* teacher;
		std::vector<Student*> student;
		int day;
		int beginClass;
		int endClass;
		int beginWeek;
		int endWeek;
		int maxStudents;
		std::string place;
};