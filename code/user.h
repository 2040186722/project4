#pragma once
#include <string>

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