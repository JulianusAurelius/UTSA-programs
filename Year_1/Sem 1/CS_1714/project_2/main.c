#include<stdio.h>
#include<stdlib.h>
#include"route-records.h"

//Known issues:
//

int main( int argc, char *argv[] )
{
  /* 1. Declare variables here */
    FILE* csv = NULL;
    RouteRecord* routeRecord;
    char choice[2];
    int num;
    int length;
    char tempOrigin[4];
    char tempDestination[4];
    char tempAirline[3];
    int TRUE = 1;
    /* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program */
    if (argc < 2) {
        printf("ERROR: Missing file name\n");
        return 1;
    }
    else if (argc > 2) {
        printf("ERROR: Too many arguments\n");
        return 1;
    }
    /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */
    printf("Opening %s\n", argv[1]);
    csv = fopen(argv[1], "r");
    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
    if (csv == NULL) {
        printf("ERROR: Could not pen file\n");
        return 1;
    }

    // 5. Do the following to load the records into an array of RouteRecords

    	// 5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer.
    routeRecord = createRecords(csv);
    	// 5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ???
    length = fillRecords(routeRecord, csv);
    printf("Unique routes operated by airlines: %d\n\n", length);
    	// 5.3 Close the the file.
    fclose(csv);

    // 6. Create an infinite loop that will do the following:
    while (TRUE)
    {
   		// 6.1 Call printMenu()
      printMenu();
   		// 6.2 Ask the user to input a value for the menu
      scanf("%s", choice);
      //printf("\n");
   		// 6.3 Handle the case in which a non-integer value is entered
      num = atoi(choice);
      switch (num)
      {
      case 1:
        printf("Enter origin: ");
        scanf("%s", tempOrigin);
        printf("Enter destination: ");
        scanf("%s", tempDestination);
        printf("\n");
        searchRecords(routeRecord, length, tempOrigin, tempDestination, ROUTE);
        break;

      case 2:
        printf("Enter origin: ");
        scanf("%s", tempOrigin);
        printf("\n");
        searchRecords(routeRecord, length, tempOrigin, tempDestination, ORIGIN);
        break;

      case 3:
        printf("Enter destination: ");
        scanf("%s", tempDestination);
        printf("\n");
        searchRecords(routeRecord, length, tempDestination, tempOrigin, DESTINATION);
        break;

      case 4:
        printf("Enter airline: ");
        scanf("%s", tempAirline);
        printf("\n");
        searchRecords(routeRecord, length, tempAirline, tempDestination, AIRLINE);
        break;

      case 5:
        printf("Good-bye!\n");
        TRUE = 0;
        break;

      default:
        printf("Invalid choice.\n");
        break;
      }
    }
    free(routeRecord);
    return 0;
}
