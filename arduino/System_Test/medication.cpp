#include "medication.h"

char const *Medication::getName(void) const
{
    return this->Name;
}
int Medication::getFrequency(void) const
{
    return this->Frequency;
}
int Medication::getTimeOfDay(void) const
{
    return this->TimeOfDay;
}
int Medication::getSupply(void) const
{
    return this->Supply;
}
int Medication::getUID(void) const
{
    return this->UniqueId;
}
int Medication::getContainerNum(void) const
{
    return this->ContainerNum;
}