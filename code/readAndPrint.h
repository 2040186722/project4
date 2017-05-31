#pragma once
#include "course.h"
#include "user.h"
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <windows.h>

struct Mail 
{
	std::string id;
	std::string name;
	std::string subject;
	std::string body;
};

bool readPhrase(char*& line, std::string& s);

/*id，密码，名字*/
void readUser(char* line, User* user);
void readAdminAccount(User* admin, const std::string path = "Data/adminAccount.csv");
void readTeachersAccount(std::map<std::string, Teacher*>& teachers, const std::string path = "Data/teachersAccount.csv");
void readStudentsAccount(std::map<std::string, Student*>& students, const std::string path = "Data/studentsAccount.csv");
/*id，课程（名称，星期，第几节开始/结束，第几周开始/结束，课堂成员上限，地点）。。。*/
void readTeachersAndCourses(std::map<std::string, Teacher*>& teachers, std::vector<Course*>& courses, const std::string path = "Data/teachers&courses.csv");
/*id，课程。。。*/
void readStudentsAndCourses(std::map<std::string, Student*>& students, const std::vector<Course*>& courses, const std::string path = "Data/students&courses.csv");
void readMails(std::vector<Mail>& mails, const std::string path = "Data/mail.csv");
void readFlag(bool& isBeginChooseCourse, const std::string path = "Data/isBeginChooseCourse.txt");
void readAllData(std::map<std::string, Teacher*>& teachers, std::map<std::string, Student*>& students, std::vector<Course*>& courses, User* admin, bool& isBeginChooseCourse);
void readCourseFromScreen(Course* course);
void readPasswordFromScreen(std::string& password);

void loginIn(std::string& id, std::string& password, const std::string title, const std::string hint1, const std::string hint2, const std::string errorMessage = "");
void changePassword(User* user, std::string title);

void printTeachersAccount(const std::map<std::string, Teacher*>& teachers, const std::string path = "Data/teachersAccount.csv");
void printStudentsAccount(const std::map<std::string, Student*>& students, const std::string path = "Data/studentsAccount.csv");
void printAdminAccount(const User* admin, const std::string path = "Data/admin.csv");
void printTeachersAndCourses(const std::map<std::string, Teacher*>& teachers, const std::string path = "Data/teachers&courses.csv");
void printStudentsAndCourses(const std::map<std::string, Student*>& students, const std::string path = "Data/students&courses.csv");
void printMail(Mail mail, const std::string path = "Data/mail.csv");
void printFlag(bool flag, const std::string path = "Data/isBeginChooseCourse.txt");
void printNotice(std::string flag, const std::string path = "Page/notice.txt");

void refreshPage(std::string pageName, std::string name = "");
void listCourses(const std::vector<Course*>& courses, std::string title);
void listStudents(const std::map<std::string, Student*>& students);
void listTeachers(const std::map<std::string, Teacher*>& teachers);
void printCourseTimetable(const std::vector<Course*>& courses, std::string name);

void moveCursor(const short dx, const short dy);