// Importing all the libraries needed
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

// Defining file paths as destFile, transFile, reportFile so that it is easier to identify
// It also makes your path files flexible because you can just edit here and not on the whole code
#define destFile "files/destination.txt"
#define transFile "files/transaction.txt"
#define reportFile "files/report.txt"

// Defining TOTAL as an integer 50
#define TOTAL (50)

// Importing all the code files needed
#include "header/structs.h"
#include "codes/manageDestination.c"
#include "codes/reserveTicket.c"
#include "codes/buyTicket.c"
#include "codes/salesReport.c"
#include "codes/mainMenu.c"


int main(void)
{
    // Array of structs of the destinations, price, and its tax
    Category currentCategories[TOTAL];

    // Array of structs of the sales report
    Report salesReport[TOTAL];

    // For index
    unsigned int total = 0;

    getAndPasteCategories(&total, &currentCategories);
    initializeReport(&salesReport, &currentCategories, &total);

    mainMenu(&currentCategories, &total, &salesReport);

    return 0;
}
