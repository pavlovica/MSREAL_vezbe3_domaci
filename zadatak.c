#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{

	FILE *diode;
	FILE *button;
	char *str;
	size_t num_of_bytes = 6;
	char button0, button1;
	float percentage = 0;
	long int period = 20000L;
	
	while(1)
	{
		//otvaramo fajl dev/led u modu za upis
		diode = fopen("/dev/led", "w");
		if (diode == NULL)
		{
			printf("Problem pri otvaranju /dev/led\n");
			return -1;
		}
		
		//postavljamo diode na 0
		fputs("0b0000\n", diode);
		
		//citanje vrednosti tastera
		button = fopen("/dev/button", "r");
		str = (char *)malloc(num_of_bytes + 1);
		getline(&str, &num_of_bytes, button);
		
		button1 = str[4] - 48;
		button0 = str[5] - 48;
		
		
		while (percentage <= 1 && percentage >= 0)
		{
			//petlja za povecanje i smanjenje faktora ispune
			if (button1 == 1)
			{
				diode = fopen("/dev/led", "w");
				fputs("0b1111", diode);
				percentage += 0.1;
			}
			else if (button0 == 1)
			{
				diode = fopen("/dev/led", "w");
				fputs("0b1111", diode);
				percentage -= 0.1;
			}
		}
		usleep(percentage*period);
		
	}
	return 0;
}
