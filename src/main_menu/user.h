#ifndef USER_H
#define USER_H

#include "medication.h"

using namespace std;

typedef int fingerIdType;
typedef int userIdType;

class User
{
  public:
	static int nextId;
	char *Name;
	userIdType UserId;
	fingerIdType Fingerprint;
	Medication *Prescriptions;
	int prescriptionCount;
	bool Trusted;

	User(char *name, fingerIdType print);
	bool elevateTrust(User *admin);
};

#endif
