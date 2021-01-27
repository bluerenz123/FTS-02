void initializeReport(Report (*salesReport)[], Category (*categories)[], int *total)
{
    // Creating an array of structs for the report sales
    for(int i = 0; i < *total; i++)
    {
        strcpy((*salesReport)[i].destination, (*categories)[i].destination);
        (*salesReport)[i].quantity = 0;
        (*salesReport)[i].price = 0;
        (*salesReport)[i].tax = 0;
    }
}

float discounts(int age, Category (*categories)[], int index)
{
    // Getting an age and returning a price based on the discount
    float price;
    index -= 1;
    if(age <= 1)
    {
        price = 0;
    } else if (age >= 2 && age <= 5)
    {
        price = ((float)((*categories)[index].price) * 0.90);
    } else if (age > 5 && age < 60)
    {
        price = (float)(*categories)[index].price;
    } else if (age > 60)
    {
        price = (float)((*categories)[index].price) * 0.80;
    }

    return price;
}

void buyReserve(Category (*categories)[], int *total, Report (*salesReport)[])
{
    // Buying a reserved ticket
    getAndPasteCategories(total, categories);
    system("cls");
    int index;
    Temporary temp;
    FILE *file;
    FILE *file2;
    int choice;
    char reservation[50];
    char answer[1];
    char tempDesti[50];
    int tempAge;
    int tempPrice;
    char desti[50];
    char reserve[50];

    // User display
    printf("\n\n\t\t\tEnter reservation code: ");
    scanf("%d", &choice);

    // Convert the user's input into a path file and then open it
    sprintf(reservation, "reservations/%d.txt", choice);
    strcpy(reserve, reservation);
    file = fopen(reservation, "r");
    file2 = fopen(transFile, "a");

    // Check if there is a file
    if(!file)
    {
        printf("\n\t\t\tThere is no file");
        char ret = getch();
        return;
    }

    printf("\n\t\t\tProceed to buy Ticket [Y/N]? ");
    scanf("%s", answer);
    int result;
    int result2;

    // Conditional statements
    if (!strcmp(answer, "Y") || !strcmp(answer, "y"))
    {

        // Scan for the following datas inside the file and then add it to the sales report and transaction file
        while((result = fscanf(file, "%s %d %d", desti, &tempAge, &tempPrice)) == 3)
        {
            fprintf(file2, "\n %-15s %-6d %d", desti, tempAge, tempPrice);
        }

        result2 = fscanf(file, "%s %d %f %f", &temp.destination, &temp.quantity, &temp.price, &temp.tax);

        index = atoi(desti);
        (*salesReport)[index-1].quantity += temp.quantity;
        (*salesReport)[index-1].price += temp.price;
        (*salesReport)[index-1].tax += temp.tax;
        
        fclose(file2);
        fclose(file);
    }
    remove(reserve);

    // Return to main
    if (!strcmp(answer, "N") || !strcmp(answer, "N"))
    {
        printf("\n\n\t\t\tpress ANY key to RETURN");
        char ret = getch();
        return;
    }
    printf("\n\n\t\t\tpress ANY key to RETURN");
        char ret = getch();
        return;
    

}

void noReserve(Category (*categories)[], int *total, Report (*salesReport)[])
{
    // Buying a non-reserved ticket
    getAndPasteCategories(total, categories);
    FILE *file;
    file = fopen(transFile, "a");
    system("cls");
    int choice;
    int adult;
    int children;
    int tempAdult;
    float tempPrice = 0;
    int tempAge;
    int price;

    // User's display
    printf("\n\t\t\t FLIGHT DESTINATION\n");
    for (int i = 0; i < *total; i++)
    {
        printf("\n\t\t\t%d. %-15s %d", i+1, (*categories)[i].destination, (*categories)[i].price);
    }
    printf("\n\t\t\t%d. RETURN TO MAIN", *total + 1);

    // Prompt user for destination code and number of adults
    printf("\n\n\t\t\tSelect destination: ");
    scanf("%d", &choice);

    if(choice > *total)
    {
        printf("\n\t\t\t Invalid code");
        noReserve(categories, total, salesReport);
    }

    printf("\n\t\t\tHow many adult: ");
    scanf("%d", &adult);

    // Loop the "input user" to how many does the user want
    for(int i = 1; i < adult + 1; i++)
    {
        printf("\n\t\t\tEnter age %d: ", i);
        scanf("%d", &tempAdult);
        if(tempAdult < 150 && tempAdult >= 18)
        {
            tempPrice += discounts(tempAdult, categories, choice);
            tempAge = tempAdult;
            price = discounts(tempAdult, categories, choice);
            // Print the datas gathered into the transaction
            fprintf(file, "\n%-15s %-6d %d",(*categories)[choice - 1].destination, tempAge, price);
        } else {
            i--;
        }
    }

    // Prompt user for number of childrens
    printf("\n\t\t\tHow many children: ");
    scanf("%d", &children);

    // Loop the "input user" to how many does the user want
    for(int i = 1; i < children + 1; i++)
    {
        printf("\n\t\t\tEnter age %d: ", i);
        scanf("%d", &tempAdult);
        if(tempAdult < 18 && tempAdult >= 0)
        {
            tempPrice += discounts(tempAdult, categories, choice);
            tempAge = tempAdult;
            price = discounts(tempAdult, categories, choice);
            // Print the datas gathered into the transaction
            fprintf(file, "\n%-15s %-6d %d",(*categories)[choice - 1].destination, tempAge, price);
        } else{
            i--;
        }
    }

    printf("\n\t\t\t Total ticket price: %.f", tempPrice);

    float tax = tempPrice * (*categories)[choice-1].tax;
    
    // Store the datas into the sales report array of structs
    (*salesReport)[choice-1].quantity += adult + children;
    (*salesReport)[choice-1].price += tempPrice;
    (*salesReport)[choice-1].tax += tax;

    printf("\n\n\t\t\tpress ANY key to RETURN");
    char ret = getch();
    return;
}

void buyTicketScreen(Category (*categories)[], int *total, Report (*salesReport)[])
{
    getAndPasteCategories(total, categories);
    system("cls");
    char menu[3][50] = {"Reserved", "No reservation", "Return to MAIN"};
    int choice;

    // Prompt the menus then let the user select the number then direct the user to the selected number
    for(int i = 0; i < 3; i++)
    {
        printf("\n\t\t\t%d.] %s", i+1, menu[i]);
    }

    printf("\n\n\t\t\tEnter Choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        buyReserve(categories, total, salesReport);
        buyTicketScreen(categories, total, salesReport);
        break;
    case 2:
        noReserve(categories, total, salesReport);
        buyTicketScreen(categories, total, salesReport);
        break;
    case 3:
        return;
        break;
    default:
        printf("\n\t\t\tInvalid choice");
        sleep(1);
        buyTicketScreen(categories, total, salesReport);
        break;
    }
    return;
}

