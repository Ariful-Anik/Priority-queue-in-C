
# include<stdio.h>
# include<malloc.h>

typedef struct node
{
    int priority;
    int info;
    char name[20];
    long int size;
    struct node *link;
} NODE;
NODE *front = NULL;

// insert method
void insert(int data,char *senderName,int priority,long int size)
{
    NODE *temp,*q;

    temp = (NODE *)malloc(sizeof(NODE));
    temp->info = data;
    strcpy(temp->name,senderName);
    temp->priority = priority;
    temp->size=size;
    // condition to check whether the first element is empty or the element to be inserted has more priority than the first element
    if( front == NULL || priority < front->priority )
    {
        temp->link = front;
        front = temp;
    }
    else
    {
        q = front;
        while( q->link != NULL && q->link->priority <= priority )
            q=q->link;
        temp->link = q->link;
        q->link = temp;
    }
}


// delete method

void del()
{
    NODE *temp;
    // condition to check whether the Queue is empty or not
    if(front == NULL)
        printf("Queue Underflow\n");
    else
    {
        temp = front;
        printf("Deleted item is %d\n", temp->info);
        front = front->link;
        free(temp);
    }
}
void update(int data)
{
    NODE *temp = front;
    while(temp!=NULL)
    {
        if(temp->info==data)
        {

            printf("\nRecord with ID %d Found !!!\n", data);
            printf("Enter new priority : ");
            scanf("%d",&temp->priority);


            printf("\nUpdation Successful!!!\n");
            return;
        }
        temp = temp->link;

    }
    printf("\nPerson with id %d is not found !!!\n", data);
}


void writeData()
{
    NODE * temp = front;
    FILE *fp = fopen("Info.doc","w");
    while (temp!=NULL)
    {
        fwrite(temp,sizeof(NODE),1,fp);
        temp = temp->link;
    }
    fclose(fp);
    //printf("\nData saved Automatically.. !");

}
void readData()
{
    NODE *temp,*q;


    NODE s1;
    FILE *fp = fopen("Info.doc","r");
    while(fread(&s1,sizeof(NODE),1,fp))
    {
        temp = (NODE *)malloc(sizeof(NODE));
    temp->info = s1.info;
    strcpy(temp->name,s1.name);
    temp->priority = s1.priority;
    temp->size=s1.size;
        if( front == NULL || s1.priority < front->priority )
    {
        temp->link = front;
        front = temp;
    }
    else
    {
        q = front;
        while( q->link != NULL && q->link->priority <= s1.priority )
            q=q->link;
        temp->link = q->link;
        q->link = temp;
    }
    }
    //printf("Data read complete");
}

long int findSize(char file_name[])
{
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");

    // checking if the file exist or not
    if (fp == NULL)
    {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file
    long int res = ftell(fp);

    // closing the file
    fclose(fp);

    return res;
}
// display method
void display()
{
    NODE *ptr;
    ptr = front;
    if(front == NULL)
        printf("Queue is empty\n");
    else
    {
        printf("\n\t\t\t---Queue List---\n\n");
        printf("---------------------------------------------------------------------------\n");
        printf("---------------------------------------------------------------------------\n");
        printf("    Priority     |      Size        |     ID      |  Sender Name\n\n");
        while(ptr != NULL)
        {
            printf("    %5d        |  %5d bytes     |  %5d      |  %5s\n",ptr->priority,ptr->size,ptr->info,ptr->name);
            ptr = ptr->link;
        }
        printf("---------------------------------------------------------------------------\n");
        printf("---------------------------------------------------------------------------\n");
    }
}
/*End of display*/

// main method
int main()
{
    system("COLOR 3F");
    int choice, data,num, priority;
    char name[100];
    printf("\t\t\t----Welcome To the System----\n\n");
    readData();
    do
    {
        printf("\n\t\t\t1.Insert\n");
        printf("\t\t\t2.Delete\n");
        printf("\t\t\t3.Display\n");
        printf("\t\t\t4.Change priority\n");
        printf("\t\t\t5.Exit\n");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            printf("\nEnter Unique Id Number : ");
            scanf("%d",&data);
            printf("Enter Sender Name : ");
            fflush(stdin);
            fgets(name,100,stdin);
            //fflush(stdin);
            printf("Enter its priority : ");
            scanf("%d",&priority);

            char file_name[] = { "Info.doc" };
            long int res = findSize(file_name);
            printf("File size :-- calculated automatically--\n");
            insert(data,name,priority,res);
            writeData();
            printf("-\tInformation Saved-\n");
            break;
        case 2:
            del();
            writeData();
            break;
        case 3:
            display();
            break;
        case 4:
            printf("\nEnter the unique ID to change priority : ");
            scanf("%d",&num);
            update(num);
            break;

        case 5:
            exit(0);
            break;

        default :
            printf("Wrong choice\n");
        }
    }
    while(choice!=5);

    return 0;
}
