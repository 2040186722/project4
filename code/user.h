#pragma once
#include <string>
#include <vector>

class Course;

class User
{
	public:
		User();
		~User();
		bool setName(const std::string &name1);
		bool setAccountId(const std::string &accountId1);
		bool setPassword(const std::string &password1);
		std::string getName() const;
		std::string getAccountId() const;
		std::string getPassword() const;
		bool login(const std::string &password1) const;
	private:
		std::string name;
		std::string accountId;
		std::string password;
};

class Student :public User
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

class Teacher :public User
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