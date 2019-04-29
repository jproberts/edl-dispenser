#ifndef MEDS_H
#define MEDS_H

class Medication
{
  private:
	char const *Name;
	int Frequency;
	int TimeOfDay;
	char const *DoctorContactInfo;
	int Supply;
	// enum Notifications;
	int UniqueId;
	// User* Recipients // Hoping we don't need this.
	int ContainerNum;

  public:
	Medication() : Name("Vitamins"), Frequency(1000), TimeOfDay(5000), Supply(15), ContainerNum(0) {}
	Medication(char const *name, int frequency, int timeofday) : Name(name), Frequency(frequency), TimeOfDay(timeofday) {}
	char const *getName(void) const;
	int getFrequency(void) const;
	int getTimeOfDay(void) const;
	int getSupply(void) const;
	int getUID(void) const;
	int getContainerNum(void) const;
};

#endif