void salesReportDisplay(Report (*salesReport)[], int *total)
{   
    // USING FOR LOOPS TO PRINT ALL OF THE DATAS IN THE SALES REPORT ARRAY OF STRUCTS IN THE PROGRAM
    // THE ARRAY OF STRUCTS ARE ALWAYS UPDATED WHENEVER YOU EITHER BUY A RESERVED OR NON-RESERVED TICKET
    // AFTER DISPLAYING THE SALES REPORT IT WILL THEN CREATE A FILE THAT CONTAINS THE COPY OF THE ARRAY OF STRUCTS
    FILE *file;
    file = fopen(reportFile, "w");
    system("cls");
    if (total == 0)
    {
    printf("\n\n\t\t\tThere's no sales report right now... ");
    }
    else
    {
        printf("\n\n\t\t\t%-14s %-9s %-10s %8s\n\n", "Flight", "Quantity", "Amount", "Travel Tax");
        for (int i = 0; i < *total; i++)
        {
        printf("\n\t\t\t%-14s %-9d %-10.2f %.2f\n", (*salesReport)[i].destination, (*salesReport)[i].quantity, (*salesReport)[i].price, (*salesReport)[i].tax);
        }

    }
    fprintf(file, "\n\n\t\t\t%-14s %-9s %-10s %8s\n\n", "Flight", "Quantity", "Amount", "Travel Tax");
    for (int i = 0; i < *total; i++)
    {
        fprintf(file, "\n\t\t\t%-14s %-9d %-10.2f %.2f", (*salesReport)[i].destination, (*salesReport)[i].quantity, (*salesReport)[i].price, (*salesReport)[i].tax);
    }

    printf("\n\n\t\t\tPress any key to RETURN");
    char ret = getch();
    return;
}
