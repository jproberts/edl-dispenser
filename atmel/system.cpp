#include "system.h"
#include <ctime>

User *System::getUserFromId(userIdType userId)
{
	for (int i = 0; i < numUsers; i++)
	{
		User *user = UserList + i;
		if (user->getUserId() == userId)
		return user;
	}
	return nullptr;
}

User *System::getUserFromPrint(fingerIdType fingerprint)
{
	for (int i = 0; i < numUsers; i++)
	{
		User *user = UserList + i;
		if (user->getFingerprint() == fingerprint)
		return user;
	}
	return nullptr;
}

userIdType System::addUser(char *name, fingerIdType fingerprint)
{
	User newUser = User(name, fingerprint);
	UserList[numUsers] = (newUser);
	return newUser.getUserId();
}

bool System::removeUser(int userId, fingerIdType fingerprint)
{
	User *admin = getUserFromPrint(fingerprint);
	if (admin == nullptr || !admin->isTrusted())
	return false;
	else
	{
		bool swap = false;
		for (int i = 0; i < numUsers; i++)
		{
			User *user = UserList + i;
			if (user->getFingerprint() == fingerprint)
			{
				swap = true;
			}
			if (swap)
			{
				UserList[i] = UserList[i + 1];
			}
		}
		if (swap)
		{
			numUsers--;
		}
		return swap;
	}
}

bool System::elevateUser(int userId, fingerIdType fingerprint)
{
	User *admin = getUserFromPrint(fingerprint);
	User *user = getUserFromId(userId);

	if (admin == nullptr || user == nullptr)
	return false;
	else
	return user->elevateTrust(admin);
}

bool System::addPrescription(User *user, Medication *meds)
{
	time_t current_time = time(nullptr);

	int delay = meds->getTimeOfDay() - current_time;
	int interval = meds->getFrequency();

	SimpleTimer t = SimpleTimer();
	// cout << "Starting timeout" << endl;
	// cout << "Found interval: " << interval << endl;
	auto repeat = [](SimpleTimer t, int interval, Medication *meds) {
		t.setInterval(System::alertUser,
		interval, meds);
	};

	t.setTimeout(repeat, delay, t, interval, meds);

	return true;
}

void System::alertUser(Medication *meds)
{
	std::cout << "Time for medication: " << meds->getName() << std::endl;
}