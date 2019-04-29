#include "user.h"

User::User(char *name, fingerIdType fingerprint)
{
	this->Name = name;
	this->UserId = User::nextId++;
	this->Fingerprint = fingerprint;
	this->Trusted = false;
}

char *User::getName(void) const
{
	return this->Name;
}

userIdType User::getUserId(void) const
{
	return this->UserId;
}

fingerIdType User::getFingerprint(void) const
{
	return this->Fingerprint;
}

bool User::isTrusted(void) const
{
	return this->Trusted;
}

bool User::elevateTrust(User *admin)
{
	if (admin->isTrusted())
	this->Trusted = true;

	return this->Trusted;
}
