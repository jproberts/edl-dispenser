#include "user.h"

User::User(char *name, fingerIdType fingerprint)
{
	this->Name = name;
	this->UserId = User::nextId++;
	this->Fingerprint = fingerprint;
	this->Trusted = false;
}

bool User::elevateTrust(User *admin)
{
	if (admin->Trusted)
		this->Trusted = true;

	return this->Trusted;
}
