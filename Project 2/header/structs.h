// typedef struct basically just void the struct function needed to write
// instead of typing struct Category you can just type Category
typedef struct category Category;
typedef struct salesReport Report;
typedef struct temp Temporary;

struct category
{
    char destination[50];
    int price;
    float tax;
};

struct salesReport
{
    char destination[50];
    int quantity;
    float price;
    float tax;
};

struct temp
{
    char destination[50];
    int quantity;
    float price;
    float tax;
};

