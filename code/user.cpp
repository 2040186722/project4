#include "user.h"

User::User()
{
}


User::~User()
{
}

bool User::setName(const std::string &name1)
{
	name = name1;
	return true;
}

bool User::setAccountId(const std::string &accountId1)
{
	accountId = accountId1;
	return true;
}

bool User::setPassword(const std::string &password1)
{
	password = password1;
	return true;
}

std::string User::getName() const
{
	return name;
}

std::string User::getAccountId() const
{
	return accountId;
}

std::string User::getPassword() const
{
	return password;
}

bool User::login(const std::string &password1) const
{
	if (password == password1)
		return true;
	return false;
}