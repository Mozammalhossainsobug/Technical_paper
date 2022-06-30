// C program to implement all meta data of a sepecific devices
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Driver code
int main()
{
	FILE* ptr;
	char ch;

	// Opening file in reading mode
	ptr = fopen("/sys/bus/pci/devices/0000:00:1f.4/uevent", "r"); // your device id instead of 0000:00:1f.4
  
  // another way of getting meta info
	//ptr = fopen("/proc/partitions", "r");


	if (NULL == ptr) {
		printf("file can't be opened \n");
	}

	// Printing what is written in file
	// character by character using loop.
	do {
		ch = fgetc(ptr);
		printf("%c", ch);

		// Checking if character is not EOF.
		// If it is EOF stop eading.
	} while (ch != EOF);

	// Closing the file
	fclose(ptr);
	return 0;
}
