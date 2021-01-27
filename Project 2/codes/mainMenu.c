void mainMenu(Category (*categories)[], int *total, Report (*salesReport)[])
{

    // THIS IS THE MAIN MENU IT DIRECTS THE USER TO THE WANTED PROGRAM
    system("cls");
    char menu[5][50] = {"Manage Destination", "Reserve Ticket", "Buy Ticket", "Sales Report", "EXIT"};
    int choice;
    printf("\n\n\t\t\tFLIGHT RESERVATION SYSTEM\n");

    for(int i = 0; i < 5; i++)
    {
        printf("\n\t\t\t%d.] %s", i+1, menu[i]);
    }

    printf("\n\n\t\t\tEnter Choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        manageDestinationMenu(total, categories);
        mainMenu(categories, total, salesReport);
        break;
    case 2:
        reserveTicket(categories, total);
        mainMenu(categories, total, salesReport);
        break;
    case 3:
        buyTicketScreen(categories, total, salesReport);
        mainMenu(categories, total, salesReport);
        break;
    case 4:
        salesReportDisplay(salesReport, total);
        mainMenu(categories, total, salesReport);
        break;
    case 5:
        return;
        break;

    default:
        printf("\n\t\t\tInvalid input.");
        sleep(1);
        mainMenu(categories, total, salesReport);
        break;
    }
    return;
}
