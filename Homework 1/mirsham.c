#include <stdio.h>
#include <string.h>

#define LINE_SIZE 256

void addRegistry(FILE *fp); // add a new registry
void findRegistry(FILE *fp, char const *idFind);    // find a registry and print found data
void printRegistry(FILE *fp);   // print registries

int main(int argc, char const *argv[])
{
    FILE *fp = NULL;
    if (argc < 2)   // not enough arguments
    {
        fputs("missing arguments", stderr);
        return 0;
    }
    if (strcmp(argv[1], "find") == 0)   // find
    {
        if (argc < 3)   // not enough arguments
        {
            fputs("missing arguments", stderr);
            return 0;
        }
        if((fp = fopen(argv[argc - 1], "r")) == NULL)   // open read
            fputs("error opening file", stderr);
        findRegistry(fp, argv[2]);  // execute find function
    }
    else if (strcmp(argv[1], "add") == 0)   // add
    {
        if((fp = fopen(argv[argc - 1], "a+")) == NULL)  // open add+read
            fputs("error opening file", stderr);
        addRegistry(fp);    // execute add function
    }
    else if (strcmp(argv[1], "print") == 0) // print
    {
        if((fp = fopen(argv[argc - 1], "r")) == NULL)   // open read
            fputs("error opening file", stderr);
        printRegistry(fp);  // execute print
    }
    fclose(fp); // close file
    return 0;
}

int registryExists(FILE *fp, char *id)  // check if id exists in the file
{
    char buf[LINE_SIZE] = {0};
    int fieldIndex = 0;
    while (fgets(buf, LINE_SIZE, fp) != NULL)
    {
        if (buf[0] == '#' || buf[0] == '\n')
            continue;
        if (buf[0] == '-')
        {
            fieldIndex = 0;
            continue;
        }
        if (fieldIndex == 1 && strcmp(buf, id) == 0)
            return 1;
        ++fieldIndex;
    }
    return 0;
}

void addRegistry(FILE *fp)  // add a registry if id doesn't already exists
{
    rewind(fp);
    char name[LINE_SIZE] = {0};
    char id[LINE_SIZE] = {0};
    char street[LINE_SIZE] = {0};
    char city[LINE_SIZE] = {0};

    // get data
    fgets(name, LINE_SIZE, stdin);
    fgets(id, LINE_SIZE, stdin);
    fgets(street, LINE_SIZE, stdin);
    fgets(city, LINE_SIZE, stdin);

    if (registryExists(fp, id)) // check if id exists
    {
        fputs("A citizen with same id is already registered", stdout);
        return;
    }

    // add data
    fputc('\n', fp);
    fputs(name, fp);
    fputs(id, fp);
    fputs(street, fp);
    fputs(city, fp);
    fputc('-', fp);
}

void findRegistry(FILE *fp, char const *idFind) // find a citizen and print info by ID
{
    char buf[LINE_SIZE] = {0};
    char name[LINE_SIZE] = {0};
    char id[LINE_SIZE] = {0};
    char street[LINE_SIZE] = {0};
    char city[LINE_SIZE] = {0};
    int fieldIndex = 0;
    int flag = 0;
    while (!flag && fgets(buf, LINE_SIZE, fp) != NULL)  // read registries until found or EOF
    {
        if (buf[0] == '#' || buf[0] == '\n')    // skip if line starts with # or empty line
            continue;
        if (buf[0] == '-')  // found a registry
        {
            fieldIndex = 0;
            continue;
        }
        buf[strlen(buf) - 1] = '\0';
        switch (fieldIndex)
        {
        case 0:
            strcpy(name, buf);
            break;
        case 1:
            strcpy(id, buf);
            if (fieldIndex == 1 && strcmp(id, idFind) == 0) // check if id matches
                flag = 1;
            break;
        case 2:
            strcpy(street, buf);
            break;
        case 3:
            strcpy(city, buf);
            break;
        default:
            fputs("find switch got to default, it shouldn't, b-baka~!", stderr);
            break;
        }
        ++fieldIndex;
    }
    if (flag)   // print accordingly
        fprintf(stdout, "%20s\t%15s\t%20s\t%15s\n", name, id, street, city);
    else
        fprintf(stdout, "Citizen doesn't exist\n");
}

void printRegistry(FILE *fp)    // prints citizens list
{
    char buf[LINE_SIZE] = {0};
    char name[LINE_SIZE] = {0};
    char id[LINE_SIZE] = {0};
    char street[LINE_SIZE] = {0};
    char city[LINE_SIZE] = {0};
    int fieldIndex = 0;
    while (fgets(buf, LINE_SIZE, fp) != NULL)   // read until EOF
    {
        if (buf[0] == '#' || buf[0] == '\n')    // skip if line starts with # or empty line
            continue;
        if (buf[0] == '-')  // found a registry
        {
            fieldIndex = 0;
            continue;
        }
        buf[strlen(buf) - 1] = '\0';
        switch (fieldIndex)
        {
        case 0:
            strcpy(name, buf);
            break;
        case 1:
            strcpy(id, buf);
            break;
        case 2:
            strcpy(street, buf);
            break;
        case 3:
            strcpy(city, buf);
            fprintf(stdout, "%20s\t%15s\t%20s\t%15s\n", name, id, street, city);    // print citizen's info
            break;
        default:
            fputs("print switch got to default, it shouldn't, b-baka~!", stderr);
            return;
        }
        ++fieldIndex;
    }
}