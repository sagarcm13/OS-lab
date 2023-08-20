#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct block
{
    int bno;
    struct block *next;
};

struct fileTable
{
    char name[20];
    int sb, nob, bloks[30];
    struct block *blocks;
} ft[30];

void displayFileDetailsWithStartingBlock(struct fileTable file)
{
    printf("\nFILE NAME   START BLOCK   NO OF BLOCKS   BLOCKS OCCUPIED\n");
    printf("%s\t\t%d\t\t%d\t", file.name, file.sb, file.nob);
    for (int j = 0; j < file.nob; j++)
    {
        printf("%d, ", file.sb + j);
    }
    printf("\n");
}

void displayFileDetailsWithLinkedList(struct fileTable file)
{
    printf("\nFILE NAME  NO OF BLOCKS   BLOCKS OCCUPIED\n");
    printf("%s\t\t%d\t", file.name, file.nob);
    struct block *temp = file.blocks;
    for (int j = 0; j < file.nob; j++)
    {
        printf("%d -> ", temp->bno);
        temp = temp->next;
    }
    printf("\n");
}

void displayFileDetailsWithArray(struct fileTable file)
{
    printf("\nFILE NAME  NO OF BLOCKS   BLOCKS OCCUPIED\n");
    printf("%s\t\t%d\t", file.name, file.nob);
    for (int j = 0; j < file.nob; j++)
    {
        printf("%d, ", file.bloks[j]);
    }
    printf("\n");
}

void freeLinkedList(struct block *head)
{
    while (head != NULL)
    {
        struct block *temp = head;
        head = head->next;
        free(temp);
    }
}

void main()
{
    int choice, n;
    char searchName[20];
    struct block *temp;

    printf("Allocation Strategies\n");
    printf("1. Sequential File Allocation\n");
    printf("2. Linked File Allocation\n");
    printf("3. Indexed File Allocation\n");
    printf("4. Exit\n");
    while (choice != 4)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // File Table with Starting Block
            printf("Enter no of files: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                printf("\nEnter file name %d: ", i + 1);
                scanf("%s", ft[i].name);
                printf("Enter starting block of file %d: ", i + 1);
                scanf("%d", &ft[i].sb);
                printf("Enter no of blocks in file %d: ", i + 1);
                scanf("%d", &ft[i].nob);
            }
            break;

        case 2:
            // File Table with Linked List of Blocks
            printf("Enter no of files: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                printf("\nEnter file name %d: ", i + 1);
                scanf("%s", ft[i].name);
                printf("Enter no of blocks in file %d: ", i + 1);
                scanf("%d", &ft[i].nob);
                ft[i].blocks = (struct block *)malloc(sizeof(struct block));
                temp = ft[i].blocks;
                printf("Enter the blocks of the file: ");
                scanf("%d", &temp->bno);
                temp->next = NULL;
                for (int j = 1; j < ft[i].nob; j++)
                {
                    temp->next = (struct block *)malloc(sizeof(struct block));
                    temp = temp->next;
                    scanf("%d", &temp->bno);
                }
                temp->next = NULL;
            }
            break;

        case 3:
            // File Table with Array of Blocks
            printf("Enter no of files: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                printf("\nEnter file name %d: ", i + 1);
                scanf("%s", ft[i].name);
                printf("Enter no of blocks in file %d: ", i + 1);
                scanf("%d", &ft[i].nob);
                printf("Enter the blocks of the file: ");
                for (int j = 0; j < ft[i].nob; j++)
                {
                    scanf("%d", &ft[i].bloks[j]);
                }
            }
            break;

        case 4:
            printf("Exiting the program.\n");
            return;

        default:
            printf("Invalid choice. Please select a valid option.\n");
            return;
        }

        // Searching for a file
        printf("Enter the file name to be searched: ");
        scanf("%s", searchName);

        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (strcmp(searchName, ft[i].name) == 0)
            {
                found = 1;
                switch (choice)
                {
                case 1:
                    displayFileDetailsWithStartingBlock(ft[i]);
                    break;
                case 2:
                    displayFileDetailsWithLinkedList(ft[i]);
                    break;
                case 3:
                    displayFileDetailsWithArray(ft[i]);
                    break;
                }
                break;
            }
        }

        if (!found)
        {
            printf("\nFile Not Found\n");
        }

        // Free allocated memory for linked lists
        for (int i = 0; i < n; i++)
        {
            if (choice == 2)
            {
                freeLinkedList(ft[i].blocks);
            }
        }
    }
}
