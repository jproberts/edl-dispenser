/*
     * SimpleTimerAlarmExample.pde
     *
     * Based on usage example for Time + TimeAlarm libraries
     *
     * A timer is called every 15 seconds
     * Another timer is called once only after 10 seconds
     * A third timer is called 10 times.
     *
     */

#include <SimpleTimer.h>
#include "medication.h"

// There must be one global SimpleTimer object.
// More SimpleTimer objects can be created and run,
// although there is little point in doing so.
SimpleTimer ttimer;

void alertUser(Medication *meds)
{
    Serial.print(meds->getName());
    Serial.println(" is ready.");
}

void createAlert(Medication *meds)
{
    ttimer.setTimer(meds->getFrequency(), alertUser, meds, 10);
}

void setupAlert(Medication *meds)
{
    ttimer.setTimeout(meds->getTimeOfDay(), createAlert, meds);
}

void setup()
{
    Serial.begin(9600);
    Medication *meds = new Medication("Vitamin A", 2000, 1000);
    setupAlert(meds);
    Medication *meds2 = new Medication("Vitamin B", 4000, 3000);
    setupAlert(meds2);
}

void loop()
{
    ttimer.run();
}
