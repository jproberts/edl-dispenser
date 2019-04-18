#include "medication.h"
#include "SimpleTimer.h"
#include "user.h"

namespace System
{
	int numUsers;
	int numMeds;
	User *UserList;
	Medication *MedicationList;

	userIdType addUser(char *name, fingerIdType fingerprint);
	bool removeUser(int userId, fingerIdType fingerprint);
	bool elevateUser(int userId, fingerIdType fingerprint);
	User *getUserFromId(userIdType userId);
	User *getUserFromPrint(fingerIdType fingerprint);
	bool addPrescription(User *user, Medication *meds);
	bool removePrescription(User *user, Medication *meds);
	void alertUser(Medication *meds);
}; // namespace System