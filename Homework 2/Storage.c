#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 256

typedef struct
{
    char *name;
    int number;
} Item;

typedef struct
{
    Item *compartments;
} Shelf;

typedef struct
{
    int shelfCount;
    Shelf *shelves;
    int compartmentPerShelf;
    int itemsCount;
    int exestingItems;
} Storage;

Storage *execute(FILE *fp);
void add(Storage *storage, char *product, int count, int shelf, int compartment);
void removeItem(Storage *storage, int shelf, int compartment);
void move(Storage *storage, int shelf1, int compartment1, int shelf2, int compartment2);
void swap(Storage *storage, int shelf1, int compartment1, int shelf2, int compartment2);
void printItem(Storage *storage, int itemNumber);
void printStorage(Storage *storage);
void printStorageMatrix(Storage *storage);
void minimiseStorage(Storage *storage);

int main(int argc, char const *argv[])
{
    FILE *fp = NULL;
    if ((fp = fopen("Storage.txt", "r")) == NULL)
        fprintf(stderr, "error opening file");
    Storage *storage = execute(fp);
    fclose(fp);
    return 0;
}

Storage *execute(FILE *fp)
{
    char buf[LINE_SIZE] = {0};
    Storage *storage = NULL;
    if (!(storage = (Storage *)calloc(1, sizeof(Storage))))
        return NULL;
    while (fgets(buf, LINE_SIZE, fp) != NULL)
    {
        if (buf[0] == '#' || buf[0] == '\n')
            continue;
        char op[6], arg0[256] = {0};
        int arg1 = -1, arg2 = -1, arg3 = -1, arg4 = -1;
        sscanf(buf, "%s", op);
        if (strcmp(op, "_isc") == 0)
        {
            sscanf(buf, "%s %d", op, &arg1);
            storage->shelfCount = arg1;
            storage->shelves = (Shelf *)calloc(arg1, sizeof(Shelf));
        }
        else if (strcmp(op, "_msps") == 0)
        {
            sscanf(buf, "%s %d", op, &arg1);
            storage->compartmentPerShelf = arg1;
            for (int i = 0; i < storage->shelfCount; i++)
            {
                storage->shelves[i].compartments = (Item *)calloc(arg1, sizeof(Item));
            }
        }
        else if (strcmp(op, "_add") == 0)
        {
            sscanf(buf, "%s %s %d %d %d", op, arg0, &arg1, &arg2, &arg3);
            add(storage, arg0, arg1, arg2, arg3);
        }
        else if (strcmp(op, "_rm") == 0)
        {
            sscanf(buf, "%s %d %d", op, &arg1, &arg2);
            removeItem(storage, arg1, arg2);
        }
        else if (strcmp(op, "_mv") == 0)
        {
            sscanf(buf, "%s %d %d %d %d", op, &arg1, &arg2, &arg3, &arg4);
            move(storage, arg1, arg2, arg3, arg4);
        }
        else if (strcmp(op, "_sw") == 0)
        {
            sscanf(buf, "%s %d %d %d %d", op, &arg1, &arg2, &arg3, &arg4);
            swap(storage, arg1, arg2, arg3, arg4);
        }
        else if (strcmp(op, "_pi") == 0)
        {
            sscanf(buf, "%s %d", op, &arg1);
            printItem(storage, arg1);
        }
        else if (strcmp(op, "_ps") == 0)
        {
            printStorage(storage);
        }
        else if (strcmp(op, "_mtrx") == 0)
        {
            printStorageMatrix(storage);
        }
        else if (strcmp(op, "_min") == 0)
        {
            minimiseStorage(storage);
        }
        else
        {
            fprintf(stderr, "Error- action does not exists!\n");
        }
    }
    return storage;
}

void add(Storage *storage, char *product, int count, int shelf, int compartment)
{
    storage->exestingItems += count;
    if (count > storage->compartmentPerShelf)
    {
        int i = storage->shelfCount;
        storage->shelfCount += count / (storage->compartmentPerShelf) + ((count % (storage->compartmentPerShelf)) != 0);
        storage->shelves = (Shelf *)realloc(storage->shelves, storage->shelfCount * sizeof(Shelf));
        for (int j = i; j < storage->shelfCount; j++)
        {
            storage->shelves[j].compartments = (Item *)calloc(storage->compartmentPerShelf, sizeof(Item));
        }
        for (; i < storage->shelfCount; ++i)
        {
            for (int j = 0; j < storage->compartmentPerShelf && count != 0; ++j, --count)
            {
                int nameLen = strlen(product);
                storage->shelves[i].compartments[j].name = (char *)calloc(nameLen + 1, sizeof(char));
                strcpy(storage->shelves[i].compartments[j].name, product);
                storage->shelves[i].compartments[j].number = ++storage->itemsCount;
            }
        }
        return;
    }

    int shelfIndex = shelf, compIndex = compartment, flag = 1, tmpCount = count;
    if (shelfIndex == -1)
        shelfIndex = 0;
    if (compIndex == -1)
        compIndex = 0;

    flag = ((storage->compartmentPerShelf - count - compIndex) >= 0);
    for (int j = compIndex; (j < storage->compartmentPerShelf) && flag && tmpCount; j++, --tmpCount)
    {
        if (storage->shelves[shelfIndex].compartments[j].number != 0)
            flag = 0;
    }
    for (; shelfIndex < storage->shelfCount && !flag; shelfIndex++)
    {
        for (compIndex = 0; compIndex < storage->compartmentPerShelf && !flag; compIndex++)
        {
            tmpCount = count;
            flag = ((storage->compartmentPerShelf - count - compIndex) >= 0);
            for (int j = compIndex; (j < storage->compartmentPerShelf) && flag && tmpCount; j++, --tmpCount)
            {
                if (storage->shelves[shelfIndex].compartments[j].number != 0)
                    flag = 0;
            }
            if (flag)
                break;
        }
        if (flag)
            break;
    }
    if (flag)
    {
        for (; compIndex < storage->compartmentPerShelf && count; ++compIndex, --count)
        {
            int nameLen = strlen(product);
            storage->shelves[shelfIndex].compartments[compIndex].name = (char *)calloc(nameLen + 1, sizeof(char));
            strcpy(storage->shelves[shelfIndex].compartments[compIndex].name, product);
            storage->shelves[shelfIndex].compartments[compIndex].number = ++storage->itemsCount;
        }
    }
    else
    {
        int i = storage->shelfCount++;
        storage->shelves = (Shelf *)realloc(storage->shelves, storage->shelfCount * sizeof(Shelf));
        storage->shelves[i].compartments = (Item *)calloc(storage->compartmentPerShelf, sizeof(Item));
        for (int j = 0; j < storage->compartmentPerShelf && count != 0; ++j, --count)
        {
            int nameLen = strlen(product);
            storage->shelves[i].compartments[j].name = (char *)calloc(nameLen + 1, sizeof(char));
            strcpy(storage->shelves[i].compartments[j].name, product);
            storage->shelves[i].compartments[j].number = ++storage->itemsCount;
        }
    }
    return;
}

void removeItem(Storage *storage, int shelf, int compartment)
{
    if (shelf < 0 || shelf >= storage->shelfCount || compartment < 0 || compartment >= storage->compartmentPerShelf)
    {
        fprintf(stderr, "REMOVE- the item location is not legal!\n");
    }
    if (storage->shelves[shelf].compartments[compartment].name == NULL)
        return;
    free(storage->shelves[shelf].compartments[compartment].name);
    storage->shelves[shelf].compartments[compartment].name = NULL;
    storage->shelves[shelf].compartments[compartment].number = 0;
}

void move(Storage *storage, int shelf1, int compartment1, int shelf2, int compartment2)
{
    if (shelf1 < 0 || shelf1 >= storage->shelfCount || shelf2 < 0 || shelf2 >= storage->shelfCount || compartment1 < 0 || compartment1 >= storage->compartmentPerShelf || compartment2 < 0 || compartment2 >= storage->compartmentPerShelf || storage->shelves[shelf1].compartments[compartment1].name == NULL || storage->shelves[shelf2].compartments[compartment2].name != NULL)
    {
        fprintf(stderr, "SWAP- one/two of the locations are not legal!\n");
        return;
    }
    int nameLen = strlen(storage->shelves[shelf1].compartments[compartment1].name) + 1;
    storage->shelves[shelf2].compartments[compartment2].name = calloc(nameLen, sizeof(char));
    strcpy(storage->shelves[shelf2].compartments[compartment2].name, storage->shelves[shelf1].compartments[compartment1].name);
    storage->shelves[shelf2].compartments[compartment2].number = storage->shelves[shelf1].compartments[compartment1].number;
    removeItem(storage, shelf1, compartment1);
}

void swap(Storage *storage, int shelf1, int compartment1, int shelf2, int compartment2)
{
    if (shelf1 < 0 || shelf1 >= storage->shelfCount || shelf2 < 0 || shelf2 >= storage->shelfCount || compartment1 < 0 || compartment1 >= storage->compartmentPerShelf || compartment2 < 0 || compartment2 >= storage->compartmentPerShelf || storage->shelves[shelf1].compartments[compartment1].name == NULL || storage->shelves[shelf2].compartments[compartment2].name == NULL)
    {
        fprintf(stderr, "SWAP- one/two of the locations are not legal!\n");
        return;
    }
    char *tempName;
    int tempNumber;
    int nameLen = strlen(storage->shelves[shelf1].compartments[compartment1].name) + 1;
    tempName = calloc(nameLen + 1, sizeof(char));
    strcpy(tempName, storage->shelves[shelf1].compartments[compartment1].name);
    tempNumber = storage->shelves[shelf1].compartments[compartment1].number;
    removeItem(storage, shelf1, compartment1);
    move(storage, shelf2, compartment2, shelf1, compartment1);
    storage->shelves[shelf2].compartments[compartment2].name = calloc(nameLen, sizeof(char));
    strcpy(storage->shelves[shelf2].compartments[compartment2].name, tempName);
    free(tempName);
    storage->shelves[shelf2].compartments[compartment2].number = tempNumber;
}

void printItem(Storage *storage, int itemNumber)
{
    if (itemNumber <= 0)
    {
        fprintf(stderr, "PRINT ITEM- the item number is not legal!\n");
    }

    for (int i = 0; i < storage->shelfCount; i++)
    {
        for (int j = 0; j < storage->compartmentPerShelf; j++)
        {
            if (storage->shelves[i].compartments[j].number == itemNumber)
            {
                printf("Item: %s, Number: %d, Position: [%d,%d]\n", storage->shelves[i].compartments[j].name, storage->shelves[i].compartments[j].number, i, j);
                return;
            }
        }
    }
}

void printStorage(Storage *storage)
{
    printf("Total space: %d\n", ((storage->shelfCount) * (storage->compartmentPerShelf)) - (storage->exestingItems));
    printf("Shelves: %d\n", storage->shelfCount);
    printf("Total items: %d\n", storage->exestingItems);
    for (int i = 0; i < storage->shelfCount; i++)
    {
        for (int j = 0; j < storage->compartmentPerShelf; j++)
        {
            if (storage->shelves[i].compartments[j].name == NULL)
                continue;
            printf("Item: %s, Number: %d, Position: [%d,%d]\n", storage->shelves[i].compartments[j].name, storage->shelves[i].compartments[j].number, i, j);
        }
    }
}

void printStorageMatrix(Storage *storage)
{
    printf("%-6s", "");
    for (int i = 0; i < storage->compartmentPerShelf; i++)
    {
        printf("|%-5d", i);
    }
    printf("\n------");
    for (int i = 0; i < storage->compartmentPerShelf; i++)
    {
        printf("------");
    }
    for (int i = 0; i < storage->shelfCount; i++)
    {
        printf("\n%-6d", i);
        for (int j = 0; j < storage->compartmentPerShelf; j++)
        {
            char str[4] = {0};
            if (storage->shelves[i].compartments[j].name != NULL)
            {
                sscanf(storage->shelves[i].compartments[j].name, "%3s", str);
                strupr(str);
            }
            else
            {
                strcpy(str, "X");
            }

            printf("|%-5s", str);
        }
    }
    printf("\n");
}

void minimiseStorage(Storage *storage)
{
    for (int i = 0; i < storage->shelfCount; i++)
    {
        for (int j = 0; j < storage->compartmentPerShelf; j++)
        {
            if (storage->shelves[i].compartments[j].name == NULL)
            {
                int flag = 1;
                for (int k = i; k < storage->shelfCount && flag; k++)
                {
                    for (int l = k == i ? j+1 : 0; l < storage->compartmentPerShelf && flag; l++)
                    {
                        if (storage->shelves[k].compartments[l].name != NULL)
                        {
                            move(storage, k, l, i, j);
                            flag = 0;
                        }
                    }
                }
            }
        }
    }
    for (int i = storage->shelfCount-1; i >= 0; i--)
    {
        int flag = 1;
        for (int j = 0; j < storage->compartmentPerShelf && flag; j++)
        {
            if (storage->shelves[i].compartments[j].name != NULL)
            {
                flag = 0;
            }
        }
        if(flag)
        {
            free(storage->shelves[i].compartments);
            storage->shelfCount--;
            storage->shelves = (Shelf *)realloc(storage->shelves, storage->shelfCount * sizeof(Shelf));
        }
    }
}