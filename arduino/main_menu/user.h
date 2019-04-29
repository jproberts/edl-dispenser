#ifndef USER_H
#define USER_H

#include "medication.h"

using namespace std;

typedef int fingerIdType;
typedef int userIdType;

class User
{
	private:
	static int nextId;
	char *Name;
	userIdType UserId;
	fingerIdType Fingerprint;
	Medication *Prescriptions;
	int prescriptionCount;
	bool Trusted;

	public:
	User(char *name, fingerIdType print);
	char *getName(void) const;
	userIdType getUserId(void) const;
	fingerIdType getFingerprint(void) const;
	bool isTrusted(void) const;
	bool elevateTrust(User *admin);
};

#endif