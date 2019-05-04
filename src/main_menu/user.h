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
	int enrollId;
	Medication *Prescriptions;
	int prescriptionCount;
	bool Trusted;

	User(char *name, int enrollId);
	void elevateTrust();
};

#endif
