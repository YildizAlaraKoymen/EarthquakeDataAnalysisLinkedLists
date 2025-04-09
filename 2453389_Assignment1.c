#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_MAX 20

/*

    We are supposed to create a linked list and for each nodes of the list link another linked list
    for this algorithm.

    For example:

    |list 0|->|list 1|->|list 2|->|list 3|-> NULL
      |         |         |         |
    |Node|    |Node|    |Node|    |Node|
      |         |         |         |
    |Node|     NULL     |Node|     NULL
      |                   |
     NULL               |Node|
                          |
                         NULL
*/

struct Node //Node declaration: Nodes will hold the data.
{
    int Date_year;
    int Date_month;
    int Date_day;
    double Magnitude;
    double Latitude;
    double Longtitude;
    int Tsunami;

    struct Node *next_node;
};

struct list //List declaration: Lists will hold only the place name.
{
    struct Node *head;

    char Place[STRING_MAX];

    struct list *next_list;
};

void Make_Empty_List(struct list *l) //Allocates memory for a node in the list.
{
    l->head = malloc(sizeof(struct Node));

    //IF THERE IS AN ERROR WITH MEMMORY ALLOCATION:
    if(l->head == NULL)
    {
        printf("\nxxx Out Of Memmory xxx\n");
        exit(1);
    }
    else
        l->head->next_node = NULL;

};

struct list *Create_list() //Allocates memory for a list
{
    struct list *l;

    l = malloc(sizeof(struct list));

    l->next_list = NULL;

    //IF THERE IS AN ERROR WITH MEMMORY ALLOCATION:
    if(l == NULL)
    {
        printf("\nxxx Out Of Memmory xxx\n");
        exit(1);
    }
    else
        Make_Empty_List(l);

    return l;
};

struct list *load_data(FILE *fp)
{
    char prev_str[STRING_MAX]; //previous string to check if Place names are same
    char str[STRING_MAX]; //Place

    int y, m, d, t; //year, month, day, tsunami
    double ma, la, lo; //magnitude, latitude, longtitude

    struct list *l;
    l = Create_list();

    struct Node *tempnode;
    tempnode = NULL; //a temporary node is needed to traverse the connected nodes

    rewind(fp);

    struct list *templist; //a temporary list is needed to traverse the connected lists
    templist = l; //templist->head->next_node = NULL; templist->next_list = NULL;

    int i = 0;
    while(fscanf(fp, "%[^,],%d,%d,%d,%lf,%lf,%lf,%d\n", str, &y, &m, &d, &ma, &la, &lo, &t)!= EOF)
    {
        if(i == 0) //Filling the first list and node
        {
            strcpy(prev_str, str);
            strcpy(templist->Place, str);
            templist->head->Date_year = y;
            templist->head->Date_month = m;
            templist->head->Date_day = d;
            templist->head->Magnitude = ma;
            templist->head->Latitude = la;
            templist->head->Longtitude = lo;
            templist->head->Tsunami = t;

            templist->head->next_node = NULL;
        }
        else
        {
            if(strcmp(prev_str, str) == 0) //If the Place names are the same
            {                              //create another node, and fill that node.

                if(tempnode == NULL)
                    tempnode = templist->head;

                tempnode->next_node = malloc(sizeof(struct Node));//allocate next node

                //IF THERE IS AN ERROR WITH MEMMORY ALLOCATION
                if(tempnode->next_node == NULL)
                {
                    printf("\nxxx Out Of Memmory xxx\n");
                    exit(1);
                }
                tempnode->next_node->next_node = NULL;

                tempnode = tempnode->next_node;//go to the next node,

                tempnode->Date_year = y;       //fill the next node
                tempnode->Date_month = m;
                tempnode->Date_day = d;
                tempnode->Magnitude = ma;
                tempnode->Latitude = la;
                tempnode->Longtitude = lo;
                tempnode->Tsunami = t;

                strcpy(prev_str, str);

            }
            else
            {   //If place names are different, create another list and a node within that list, fill that.
                templist->next_list = malloc(sizeof(struct list));//allocate next list

                //IF THERE IS AN ERROR WITH MEMMORY ALLOCATION
                if(templist->next_list == NULL)
                {
                    printf("\nxxx Out Of Memmory xxx\n");
                    exit(1);
                }

                templist->next_list->next_list = NULL;
                templist->next_list->head = malloc(sizeof(struct Node)); //allocate node in new list

                //IF THERE IS AN ERROR WITH MEMMORY ALLOCATION
                if(templist->next_list->head == NULL)
                {
                    printf("\nxxx Out Of Memmory xxx\n");
                    exit(1);
                }

                templist->next_list->head->next_node = NULL;

                templist = templist->next_list; //go to next list

                strcpy(templist->Place, str);
                templist->head->Date_year = y;
                templist->head->Date_month = m;
                templist->head->Date_day = d;
                templist->head->Magnitude = ma;
                templist->head->Latitude = la;
                templist->head->Longtitude = lo;
                templist->head->Tsunami = t;

                strcpy(prev_str, str);
            }
        }
        i++;

    }

    return l;
}

void Display_Data(struct list *l) //This function was created to check if the data was filled correctly.
{                                 //Prints all the data in each list and node
    struct list *temp;
    temp = l;
    struct Node *tempnode;
    while(temp != NULL)
    {
        printf("%s\n", temp->Place);
        tempnode = temp->head;
        while(tempnode != NULL)
        {
            printf("%d-%d-%d, %.1lf, %.4lf, %.4lf, %d", tempnode->Date_year, tempnode->Date_month, tempnode->Date_day, tempnode->Magnitude, tempnode->Latitude, tempnode->Longtitude, tempnode->Tsunami);
            tempnode = tempnode->next_node;
            printf("\n");
        }
        temp = temp->next_list;
        printf("\n");
    }
}

void remove_earthquake(struct list *l, double tr)
{
    int count = 0;

    if(l != NULL)//check if list is empty
    {
        struct Node *tempnode, *temphead, *prev;
        struct list *temp;

        temp = l;
        while(temp != NULL)
        {
            tempnode = temp->head;
            temphead = tempnode; //hold the starting node of the connected nodes
            while(tempnode != NULL)
            {
                struct Node *removenode; //delete first node
                if(temphead->Magnitude < tr)
                {
                    removenode = tempnode;
                    temphead = tempnode->next_node;
                    free(removenode);
                    temp->head = temphead;
                    count++;
                }
                else if(tempnode->Magnitude < tr) //delete last and middle node
                {
                    removenode = tempnode;
                    prev->next_node = tempnode->next_node;
                    free(removenode);
                    temp->head = temphead;
                    count++;
                }

                if(tempnode != NULL) //go to the next node if node is not NULL
                {
                    prev = tempnode; //need to know previous node to delete last or middle element
                    tempnode = tempnode->next_node; //go to next node
                }
            }
            temp = temp->next_list; //go to next list

        }

    }
    else
        printf("\nxxx List is empty xxx\n");

    printf("The number of removed nodes: %d\n", count);
}

void count_earthquakes(struct Node *head) //Will count the nodes and sum the tsunamis
{
    struct Node *temp;
    temp = head;

    int count = 0, sum = 0;

    while(temp != NULL)//stop when temp is null
    {
        sum = sum + temp->Tsunami;
        count++;
        temp = temp->next_node; //go to next node
    }
    //print the earthquake and tsunami count
    printf("The number of earthquake is: %d and the Tsunami is %d\n", count, sum);
}

double average_magnitude(struct Node *head) //returns average magnitude
{
    struct Node *temp;
    temp = head;

    double sum = 0;
    double count = 0;
    double average;

    while(temp!= NULL)//stop when temp is null
    {
        sum = sum + temp->Magnitude; //will sum the magnitude
        count = count + 1.0;   //count each node.
        temp = temp->next_node;//go to next node
    }

    average = sum/count;

    return average;
}

void Show_Statistics(struct list *l)
{
    struct list *temp;

    temp = l;

    char s[STRING_MAX];
    printf("Enter a user name:");
    scanf("%s", &s);

    while(temp != NULL) //Will traverse lists and nodes till the Place names match
    {
        if((strcmp(s, temp->Place) == 0))
        {
            if(temp->head == NULL)
            {
                printf("\nxxx The country is empty xxx\n");
                return(Show_Statistics(l));
            }
            else
                break;
        }
        temp = temp->next_list;
    }
    if(temp == NULL)
    {
        printf("\nxxx Country/Ocean doesn't exist xxx\n");
        return(Show_Statistics(l));
    }
    else
    {   //Will print earthquake,tsunami and average magnitude
        count_earthquakes(temp->head);
        printf("The average of earthquake magnitude is: %.1lf\n", average_magnitude(temp->head));
    }

}

int main()
{
    char file_name[STRING_MAX];

    printf("Welcome to Earthquakes Data Analysis Program\n");
    printf("Enter file name: ");
    scanf("%s", &file_name);

    FILE *fp;
    fp = fopen(file_name, "r");

    //IF THERE IS AN ERROR WITH FILE ALLOCATION
    if(fp == NULL)
    {
         printf("\n\nxxx Error loading file xxx\n\n");
         return -1;
    }

    struct list *myList;

    myList = load_data(fp);

    //IF THERE IS AN ERROR WITH LIST ALLOCATION
    if(myList == NULL)
    {
         printf("\n\nxxx Error loading file xxx\n\n");
         return -1;
    }
    else
        printf("The earthquake characteristics is successfully loaded.\n");

    int answ;

    //Display_Data(myList); <-- I used this function to check if the code was working properly.
    while(answ != 3)
    {
        printf("---------------------------------------------------------------\n");
        printf("Operations Menu\n");
        printf("---------------------------------------------------------------\n");
        printf("1. Remove Earthquake\n");
        printf("2. Show Statistics\n");
        printf("3. Exit\n");
        printf("---------------------------------------------------------------\n");

        printf("Enter your option: "),
        scanf("%d", &answ);

        if(answ == 1)
        {
            double treshhold;
            printf("Enter a threshold value for the magnitude:");
            scanf("%lf", &treshhold);

            remove_earthquake(myList, treshhold);
            //Display_Data(myList); //<-- I used this function to check if the code was working properly.
        }
        else if(answ == 2)
        {
            char name[STRING_MAX];
            Show_Statistics(myList);
        }
        else if(answ == 3)
        {
            printf("See you, bye bye!\n");
            return 0;
        }
        else
        {
            printf("\nxxx Command not recognized xxxx\n");
        }
    }


}
