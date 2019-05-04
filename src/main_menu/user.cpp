#include "user.h"

User::User(char *name, int enrollId)
{
	this->Name = name;
	this->UserId = enrollId;
	this->Trusted = false;
}

void User::elevateTrust()
{
	this->Trusted = true;
}
