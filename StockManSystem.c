#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct store{
    int purchaseId;
    char brandName[50];
    struct store *next;                 
};

typedef struct store Store;
typedef Store *StorePtr;

void menu(StorePtr start);
void readTVs(StorePtr *start ); 
void InsertInfo(StorePtr *start, int purchaseId, const char *brandName);
void printTV(StorePtr start);
void addTV(StorePtr *start);
void enqueue(StorePtr *head, StorePtr *tail, StorePtr newNode);
void printNextOrder(StorePtr head);
void printAllOrder(StorePtr head);
void addOrder(StorePtr *head, StorePtr *tail, StorePtr start);
void processNextOrder(StorePtr *head, StorePtr *start);
void updateTVFile(StorePtr *start);

int main()
{
    int choice, program = 1;

    StorePtr start = NULL;                                  // Start of the linked list initialized to NULL

    StorePtr head = NULL;                                   // Head and tail of the queue initialized to NULL
    StorePtr tail = NULL;
    
    readTVs(&start);                                        // Reads TV details from the txt file

    while(program == 1)                    
    {
        menu(start);                       

        printf("Choose your option : ");
        scanf("%d", &choice);

        switch(choice)                     
        {
            case 1:
            printf("\n");

            printTV(start);

            break;

            case 2:
            addTV(&start);

            printf("\n---------Updated Stock---------\n");

            printf("\n");

            printTV(start);

            break;

            case 3:
            printNextOrder(head);
            
            break;

            case 4:
            printAllOrder(head);

            break;

            case 5:
            addOrder(&head, &tail, start);

            break;

            case 6:
            processNextOrder(&head, &start);

            break;

            case 7:
            updateTVFile(&start);

            break;

            case 8:
            program = 0;

			printf("\nThank you for using the TV program!\n");

            break;

            default:
            printf("Invalid selection\n");

            break;

        }
    } 

    return 0;
}

void menu(StorePtr start)                                   // Menu to display to the user 
{
    printf("\nWelcome to the Online TV List!\n\n");

    printf("(1) Display current TV stock\n");
    printf("(2) Add a new TV to stock\n");
    printf("(3) Display the next order information\n");
    printf("(4) Display all orders\n");
    printf("(5) Add order to the queue\n");
    printf("(6) Process the next TV order\n");
    printf("(7) Update stock list\n");
    printf("(8) Exit\n");

    printf("\n");
}

void readTVs(StorePtr *start)
{
    char line[100];
    char brandName[50];
    int purchaseId;

    FILE *fp = fopen("TV.txt", "r");               

    if (fp == NULL)
    {
        printf("Couldn't open the Text file\n");
        return;
    }

    while (fgets(line, 100, fp) != NULL)                                    // Reads a line from the txt file and stores it in line 
    {
        if (sscanf(line, "%d %[^\n]", &purchaseId, brandName ) == 2)        // Reads the Purchase ID and Brand name and inserts into a linked list
        {
            InsertInfo(start, purchaseId, brandName);
        }
    }

    fclose(fp);
}

void InsertInfo(StorePtr *start, int purchaseId, const char *brandName)
{
    StorePtr newPtr = (StorePtr)malloc(sizeof(Store));                      // Allocates memory using malloc for a new node

    newPtr->purchaseId = purchaseId; 
    strcpy(newPtr->brandName, brandName);;                                        

    newPtr->next = NULL;                                                             

    StorePtr current = *start;
    StorePtr previous = NULL;                                                                                               

    while(current != NULL && strcmp(newPtr->brandName, current->brandName) > 0)     // Loop to insert the new node in the correct place in alphabetical order
    {                                                                                              
        previous = current;                                                     
        current = current->next;                                                
    }

    if(previous == NULL)                        // Inserts node to the beginning of the linked list 
    {
        newPtr->next = *start;                                           
        *start = newPtr;                                                            
    }

    else                                        // Inserts node to either the middle or the end of the linked list
    {
        newPtr->next = current;                                                
        previous->next = newPtr;                                                
    }

} 

void printTV(StorePtr start)
{
    StorePtr current = start;                             // Current pointer initialized to the start of the linked list

    if (current == NULL)
    {
        printf("\nNo TV details available\n");
        return;
    }

    printf("Purchase ID\t\tBrand Name\n");
    printf("-------------------------------------------\n");

    while(current != NULL)
    {
        printf("%-15d%s\n", current->purchaseId, current->brandName);       // Displays the contents in the given format

        current = current->next;                                            // Traverses the linked list
    }

    printf("\n");
}

void addTV(StorePtr *start)
{
    int purchaseId;
    char brandName[50];

    StorePtr newPtr = (StorePtr)malloc(sizeof(Store));              // Memory allocation using malloc for a new node

    printf("Enter purchase ID: ");                                  // User input to add a TV to the stock
    scanf("%d", &purchaseId);

    printf("Enter brand name: ");

    getchar();                                                      // Clears the newline char from the input buffer

    scanf("%[^\n]", brandName);

    newPtr->purchaseId = purchaseId;
    strcpy(newPtr->brandName, brandName);
    newPtr->next = NULL;

    StorePtr current = *start;
    StorePtr previous = NULL;                                        

    while(current != NULL && strcmp(newPtr->brandName, current->brandName) > 0)     // Find the correct position to insert the new node in alphabetical order
    {
        previous = current;
        current = current->next;
    }

    if(previous == NULL)                                             // Inserts the new node at the beginning of the linked list
    {
        newPtr->next = *start;
        *start = newPtr;
    }

    else                                                             // Inserts the new node at the middle or end of the linked list
    {
        newPtr->next = current;
        previous->next = newPtr;
    }

    printf("\nTV added successfully!\n");                           // TV entered by the user successfully added to the linked list

}

void enqueue(StorePtr *head, StorePtr *tail, StorePtr newNode)
{
    if(*head == NULL)                              		// If queue is empty sets the head and tail to the new node
    {
        *head = newNode;
        *tail = newNode;
    }

    else                                                // Adds the new node to the end of the queue since not empty
    {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void printNextOrder(StorePtr head)                     
{
    if(head == NULL)
    {
        printf("\nNo orders in the queue\n");
    }

    else                                                   // Displays the next order details which is stored in the head of the queue                 
    {
        StorePtr nextOrder = head;

        printf("\nNext Order Information\n");
        printf("-------------------------\n");

        printf("TV Name : %s\n", nextOrder->brandName);

        printf("\n");
    }
}

void printAllOrder(StorePtr head)                        
{
    int count = 1;                                         // Count variable to keep track of the number of orders

    StorePtr current = head;                        	   // Current pointer initialized to head of the queue

    if(current == NULL)
    {
        printf("\nCurrently no orders in queue\n");

        return;
    }

    printf("\nAll Orders in queue\n");
    printf("--------------------\n");
    printf("\n");

    while(current != NULL)                                 // Displays all orders in the queue as long as it's not empty
    {
        printf("Order Number : %d\n", count);

        printf("TV Name: %s\n", current->brandName);

        current = current->next;
        count++;

        printf("\n");
    }

    printf("\n");
}

void addOrder(StorePtr *head, StorePtr *tail, StorePtr start)
{
    char brandName[50];
    StorePtr orderTV = (StorePtr)malloc(sizeof(Store));

    StorePtr current = start;

    printf("Enter the TV you're looking to order : ");

    getchar();

    scanf("%[^\n]", brandName);                               // Format specifier given to allow mutiple words to be given until new line    

    while(current != NULL)                                    // Checks if the TV name entered by the user is in the stock(linked list)
    {
        if(strcmp(brandName, current->brandName) == 0)     
        {
            strcpy(orderTV->brandName, brandName);

            orderTV->next = NULL;

            enqueue(head, tail, orderTV);

            printf("\nYour order has been added to the queue!\n");

            return;
        }  

        current = current->next;
    }

    free(orderTV);

    printf("\nTV you entered is not available in the stock\n");
}

void processNextOrder(StorePtr *head, StorePtr *start)
{
    if(*head == NULL)
    {
        printf("\nNo orders in the queue\n");

        return;
    }

    StorePtr getOrder = *head;                              // First order in the queue stored in getOrder

    StorePtr current = *start;                             // Current initialized to the start of the linked list
    StorePtr previous = NULL;                              // Previous pointer initialized to NULL     

    while(current != NULL && strcmp(current->brandName, getOrder->brandName) != 0)    
    {
        previous = current;
        current = current->next;
    } 

    if(current == NULL)              
    {
        printf("\nTV not available in the TV stock\n");

        return;
    }                   

    if(previous == NULL)                                  
    {
        *start = current->next;
    }

    else
    {
        previous->next = current->next;
    }

    *head = (*head)->next;                                  // Head moved to the next order in the queue

    free(current);                                          // Memory deallocated for the current order

    printf("\nTV order has been processed!\n");

}

void updateTVFile(StorePtr *start)                          // Writes the updated contents of the linked list to the file
{
    FILE *fp = fopen("TV.txt", "w"); 

    StorePtr current = *start;

    if (fp == NULL)
    {
        printf("Couldn't open file\n");
        
        return;
    }

    while (current != NULL)                                
    {
        fprintf(fp, "%d %s\n", current->purchaseId, current->brandName); 
        current = current->next;
    }

    fclose(fp);

    printf("\n");

    printf("TV file updated successfully!\n");
}