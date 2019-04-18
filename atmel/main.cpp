#include <avr/io.h>
#include "SimpleTimer.h"

void repeatMe() {
	static int i = 0;
	i++;
}

int main()
{
	SimpleTimer timer;
	
	timer.setInterval(1000, repeatMe);
	timer.run();
	

	while (true)
	; // Keep main thread active
}