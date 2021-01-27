int getInfo(FILE *file, Category *current, int *total)
{
    // Getting datas from the destination file
    int result;

    while ((result = fscanf(file, "%s %d %f", &current->destination, &current->price, &current->tax)) == 1)
    {
        return getInfo(file, current, total);
    }

    if (result == EOF)
    {
        fclose(file);
        return 0;
    }
    else if (result != 3)
    {
        printf("\aError reading data\n");
        return 0;
    }
    else
    {
        *total += 1;
        return 1;
    }
}

void paste(Category *category, int index, Category (*categories)[])
{
    int i = index - 1;

    // Pasting the data into the array of structs
    strcpy(((*categories)[i]).destination, category->destination);
    (*categories)[i].price = category->price;
    (*categories)[i].tax = category->tax * 0.01;

    return;
}

void getAndPasteCategories(int *total, Category (*categories)[])
{

    // Combing the getInfo() and paste() programs to get and paste the categories from the file to the structs.
    FILE *file;
    *total = 0;
    file = fopen(destFile, "r");
    if (!file)
    {
        printf("\aError opening %s file\n", destFile);
        return;
    }
    int i = 0;

    Category category;
    while (getInfo(file, &category, total))
    {
        paste(&category, ++i, categories);
    }

    return;
}

void addDestination(Category (*categories)[], int *total)
{
    // Adding a destination
    getAndPasteCategories(total, categories);
    system("cls");
    int index = *total + 1;
    FILE *file;
    char tempDesti[50];
    int tempPrice;
    int tempTax;
    char answer[1];
    char anoAnswer[1];
    int tatax;

    // User's display, getting the datas needed
    printf("\n\n\t\t\tDestination code: %03d", index);
    printf("\n\t\t\tEnter new destination: ");
    scanf("%s", tempDesti); 
    printf("\n\t\t\tEnter price ticket: ");
    scanf("%d", &tempPrice);
    while (tempPrice <= 0)
    {
        printf("\n\t\t\tEnter valid price");
        printf("\n\t\t\tEnter price ticket: ");
        scanf("%d", &tempPrice);
    }
    printf("\n\t\t\tEnter tax: ");
    scanf("%d", &tatax);
    while (tatax <= 0 || tatax >= 99)
    {
        printf("\n\t\t\tEnter valid tax");
        printf("\n\t\t\tEnter tax: ");
        scanf("%d", &tempPrice);
    }
    tempTax = tatax;
    int currentPrice = tempPrice;


    printf("\n\t\t\tSAVE this record [Y/N]: ");
    scanf("%s", answer);

    if (!strcmp(answer, "Y") || !strcmp(answer, "y"))
    {
        // Appending the dats gathered to the new array of structs
        file = fopen(destFile, "a");
        fprintf(file, "%-17s %-15d %d%%\n", tempDesti, currentPrice, tempTax);
        (*total)++;
        fclose(file);

        strcpy((*categories)[index].destination, tempDesti);
        (*categories)[index].price = tempPrice;
        (*categories)[index].tax = (float)tempTax * 0.01;

        fclose(file);
    }

    // Conditional statements
    printf("\n\t\t\tAnother record [Y/N]?");
    scanf("%s", anoAnswer);
    if (!strcmp(anoAnswer, "Y") || !strcmp(anoAnswer, "y"))
    {
        addDestination(categories, total);
    }
    if (!strcmp(anoAnswer, "N") || !strcmp(anoAnswer, "n"))
    {
        return;
    }

    return;
}

void editDestination(Category (*categories)[], int *total)
{
    // Editing the price of the selected destination
    FILE *file;
    getAndPasteCategories(total, categories);
    system("cls");
    int destChoice;
    int tempPrice;
    char answer[1];
    char anoAnswer[1];

    // User's display, gathering datas
    printf("\n\t\t\tEnter destination code: ");
    scanf("%d", &destChoice);
    if(destChoice > *total || destChoice <= 0)
    {
        printf("\n\t\t\tInvalid input");
        editDestination(categories, total);
    }
    
    printf("\n\t\t\t%s", (*categories)[destChoice - 1].destination);
    printf("\n\t\t\tEnter new ticket price: ");
    scanf("%d", &tempPrice);
    while (tempPrice <= 0)
    {
        printf("\n\t\t\tEnter valid price");
        printf("\n\t\t\tEnter price ticket: ");
        scanf("%d", &tempPrice);
    }

    char ui[3][50] = {"Destination", "Price per Destination", "Travel tax"};
    int currentPrice = tempPrice;
    printf("\t\t\tSAVE changes [Y/N]?");
    scanf("%s", answer);
    if (!strcmp(answer, "Y") || !strcmp(answer, "y"))
    {
        // Directing to the selected array of structs then getting the price of it
        // after that the selected price will be then changed into the new wanted price
        (*categories)[destChoice - 1].price = currentPrice;
        file = fopen(destFile, "w+");

        fprintf(file, "%-15s %s %s\n\n", ui[0], ui[1], ui[2]);

        for (int i = 0; i < *total; i++)
        {
            float tax = ((*categories)[i].tax) * 100;
            fprintf(file, "%-17s %-15d %.f%%\n", (*categories)[i].destination, (*categories)[i].price, tax);
        }
        fclose(file);
    }

    // Conditional Statements
    printf("\n\t\t\tEdit another record [Y/N]?");
    scanf("%s", anoAnswer);
    if (!strcmp(anoAnswer, "Y") || !strcmp(anoAnswer, "y"))
    {
        editDestination(categories, total);
    }
    if (!strcmp(anoAnswer, "N") || !strcmp(anoAnswer, "n"))
    {
        return;
    }
    return;
}

void deleteDestination(Category (*categories)[], int *total)
{
    // Delete a destination
    getAndPasteCategories(total, categories);
    system("cls");
    FILE *file;
    int destChoice;
    int result;
    char answer[1];

    // User's display, gathering datas
    printf("\n\n\t\t\tEnter destination code: ");
    scanf("%d", &destChoice);
    if (destChoice > *total || destChoice < 0)
    {
        return deleteDestination(categories, total);
    }
    int index = destChoice - 1;

    // Displaying the user's selected destination
    printf("\n\t\t\tDestination name: %s", (*categories)[index].destination);
    printf("\n\t\t\tDestination price: %d", (*categories)[index].price);

    printf("\n\t\t\tAre you sure you want to delete this record[y/n]?");
    scanf("%s", answer);

    if (!strcmp(answer, "Y") || !strcmp(answer, "y"))
    {
        int allCateg = *total - 1;
        printf("\nDeleting this record...");

        // Opening the destination files and then overwriting the array datas here with the new array of structs which is lessen because the user had delete an destination.
        file = fopen(destFile, "w+");
        fprintf(file, "%-15s %s %s\n\n", "Destination", "Price per Destination", "Travel tax");

        // Using for loop to write all of the categories
        for (int i = 0; i < allCateg; i++)
        {
            if (i >= index)
            {
                int holder = i + 1;
                strcpy((*categories)[i].destination, (*categories)[holder].destination);
                (*categories)[i].price = (*categories)[holder].price;
                (*categories)[i].tax = (*categories)[holder].tax;
            }

            float travelTax = (*categories)[i].tax * 100;
            fprintf(file, "%-17s %-15d %.f%%\n", (*categories)[i].destination, (*categories)[i].price, travelTax);
        }
        *total -= 1;
        fclose(file);
    } 
    if (!strcmp(answer, "N") || !strcmp(answer, "n"))
    {
        return;
    }
    return;
}

void displayDestinations(Category (*categories)[], int *total)
{
    // Displaying destinations
    getAndPasteCategories(total, categories);
    system("cls");

    printf("\n\t\t\t   List of Flights");
    printf("\n\t\t\t%-14s %5s\n", "Destination", "Price");

    // Using for loop to display all the content of the array of structs(categories)
    for (int i = 0; i < *total; i++)
    {
        printf("\n\t\t\t%-15s %d", (*categories)[i].destination, (*categories)[i].price);
    }

    printf("\n\n\t\t\tPress ANY KEY to RETURN");
    char ret = getch();
    return;
}

void manageDestinationMenu(int *total, Category (*categories)[])
{
    // Manage Destination Menu
    system("cls");
    int choice;
    char choices[6][50] = {"Add New Destination", "Edit", "Delete", "Display All", "Return to MAIN"};

    // Prompt the menus then let the user select the number then direct the user to the selected number
    printf("\n");
    for (int i = 1; i < 6; i++)
    {
        printf("\n\t\t\t%d.] %s", i, choices[i - 1]);
    }
    printf("\n\n\t\t\tEnter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        addDestination(categories, total);
        manageDestinationMenu(total, categories);
        break;
    case 2:
        editDestination(categories, total);
        manageDestinationMenu(total, categories);
        break;
    case 3:
        deleteDestination(categories, total);
        manageDestinationMenu(total, categories);
        break;
    case 4:
        displayDestinations(categories, total);
        manageDestinationMenu(total, categories);
    case 5:
        break;
    default:
        printf("\n\t\t\tInvalid input");
        sleep(1);
        manageDestinationMenu(total, categories);
        break;
    }
    return;
}
