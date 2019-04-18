#ifndef MEDS_H
#define MEDS_H

class Medication
{
	private:
	char* Name;
	int Frequency;
	int TimeOfDay;
	char* DoctorContactInfo;
	int Supply;
	// enum Notifications;
	int UniqueId;
	// User* Recipients // Hoping we don't need this.
	int ContainerNum;

	public:
	char* getName(void) const;
	int getFrequency(void) const;
	int getTimeOfDay(void) const;
	int getSupply(void) const;
	int getUID(void) const;
	int getContainerNum(void) const;
};

#endif