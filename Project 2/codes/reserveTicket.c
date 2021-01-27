float discount(int age, Category (*categories)[], int index)
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

void reserveTicket(Category (*categories)[],int *total)
{

    // Reserving a ticket and creating a file
    getAndPasteCategories(total, categories);
    FILE *file;
    int choice;
    int adult;
    float tempPrice = 0;
    int tempQuantity;
    int tempAdult;
    int children;
    int tempAge;
    int price;
    
    system("cls");
    printf("\n\n\t\t\t   FLIGHT DESTINATION\n");
    for (int i = 0; i < *total; i++)
    {
        printf("\n\t\t\t%d. %-15s %d", i + 1,(*categories)[i].destination, (*categories)[i].price);
    }
    printf("\n\t\t\t%d. RETURN TO MAIN", *total + 1);

    // User's display, gathering datas needed
    printf("\n\n\t\t\tSelect reserve destination: ");
    scanf("%d", &choice);
    if(choice == (*total + 1))
    {
        return;
    }
    if(choice > *total)
    {
        printf("\n\t\t\tInvalid input");
        reserveTicket(categories, total);
    }

    printf("\n\t\t\tHow many adult: ");
    scanf("%d", &adult);

    // Generate a random integer
    // Convert the integer into a string  using (sprintf) to create a directory file
    // Create a directory file with the random integer name on it
    // The random integer only ranges from 1-99
    srand(time(NULL));
    int r = (rand() % 98) + 1;
    char filename[50];
    sprintf(filename, "reservations/%d.txt", r);
    file = fopen(filename, "w+");

    // Print the transaction details each time a user enter an age
    for(int i = 1; i < adult + 1; i++)
    {  
        printf("\n\t\t\tEnter age %d: ", i);
        scanf("%d", &tempAdult);
        if(tempAdult < 150 && tempAdult >= 18)
        {
            tempPrice += discount(tempAdult, categories, choice);
            tempAge = tempAdult;
            price = discount(tempAdult, categories, choice);
            fprintf(file, "\n %s %d %d", (*categories)[choice-1].destination,tempAge, price);
        } else {
            i--;
        }

    }

    // Print the transaction details each time a user enter an age
    printf("\n\t\t\tHow many children: ");
    scanf("%d", &children);
    for(int i = 1; i < children + 1; i++)
    {
        printf("\n\t\t\tEnter age %d: ", i);
        scanf("%d", &tempAdult);
        if(tempAdult < 18 && tempAdult >= 0)
        {
            tempPrice += discount(tempAdult, categories, choice);
            tempAge = tempAdult;
            price = discount(tempAdult, categories, choice);
            fprintf(file, "\n %s %d %d", (*categories)[choice-1].destination,tempAge, price);
        } else {
            i--;
        }
    }

    printf("\n\t\t\t Total ticket price: %.f", tempPrice);

    // Printing the random reservation code
    printf("\n\t\t\t Your reservation code: %d", r);

    printf("\n\n\t\t\t press ANY key to RETURN ");
    char ret = getch();

    // Printing the index, destination, quantity, amount, and tax into the file which will then be read if you want to buy the reserved ticket you created.
    float tax = tempPrice * (*categories)[choice-1].tax;
    fprintf(file, "\n%d %s \t %d \t%.f \t %.f ", choice,(*categories)[choice-1].destination, adult + children, tempPrice, tax);

    fclose(file);
    return;
}


