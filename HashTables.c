// Oisin Cousins 18323211 23/10/20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 100
#define ARRAY_SIZE 60000
int collisions, numterms = 0;

typedef struct Node Node;
struct Node
{

    char id[MAX_STRING_SIZE];
    char did[MAX_STRING_SIZE];
    char surname[MAX_STRING_SIZE];
    char forename[MAX_STRING_SIZE];
    char age[MAX_STRING_SIZE];
    char person_type[MAX_STRING_SIZE];
    char gender[MAX_STRING_SIZE];
    char nationality[MAX_STRING_SIZE];
    char religion[MAX_STRING_SIZE];
    char occupation[MAX_STRING_SIZE];
    Node *next;
    int freq;
    char key[MAX_STRING_SIZE];
};

/*struct item{
    int freq;
    char key[MAX_STRING_SIZE];
    Node* next;
};*/

struct Node Harray[ARRAY_SIZE];
//struct Item* Item;
//struct Item* item;

void makeArray()
{
    //printf("Entered making array\n");
    for (int x = 0; x < ARRAY_SIZE; x++)
    {
        Harray[x].key[0] = '\n';
        Harray[x].freq = 0;
        Harray[x].next = NULL;
    }
}

int hash1(char *s)
{
    //printf("Entered hash1\n");
    int hash = 0;
    int i = 1;
    while(*s){
        hash = (hash + (*s)*i);
        s++;
        i++;
    }
    return (hash % ARRAY_SIZE);
}

int hash2(char *s)
{
    //printf("Entered hash2\n");
    int hash = 0;
    while (*s)
    {
        hash = (hash + *s);
        s++;
    }
    hash = hash + (numterms);
    return (hash % ARRAY_SIZE);
}
int hash3(char *s, int i)
{
    //printf("Entered hash3\n");
    return (hash1(s) * i + hash2(s) ) % ARRAY_SIZE;
}

int search(char *key)
{
    //printf("Entered search\n");
    //get hash
    int Hindex = hash1(key);
    int tempo = Hindex;

    //find key if there
    do
    {
        //printf("Entered while\n");
        if (strcmp(Harray[Hindex].key, key) == 0)
        {
            //printf("Found %s\n", key);
            return Hindex;
        }
        Hindex++;
        Hindex %= ARRAY_SIZE; //wrap around

    } while (Hindex != tempo);
    //printf("Returning -1\n");
    return -1;
}

void insert(Node temp)
{
    //printf("Entered insert \n");
    //printf("blah %s\n", temp.surname);
    Node *current = NULL;
    Node *next = NULL;
    char *s = temp.surname;
    int i = 0;
    int index = hash3(s, i);
    int a = search(s);
    if (a != -1)
    {
        //printf("HI\n");
        Harray[a].freq++;
        numterms++;
        Node *newNode = (Node *)malloc(sizeof(Node));

        current = &Harray[a];
        //printf("cake\n");
        while (current->next != NULL)
        {
            current = current->next;
            //printf("looping\n");
        }
        //printf("Exit loop\n");

        current->next = newNode;
        newNode->next = NULL;
        
        strcpy(newNode->surname, temp.surname);
        //printf("bleh %s  %d\n", newNode->surname, Harray[a].freq);

        strcpy(newNode->id, temp.id);
        strcpy(newNode->did, temp.did);
        strcpy(newNode->forename, temp.forename);
        strcpy(newNode->age, temp.age);
        strcpy(newNode->person_type, temp.person_type);
        strcpy(newNode->gender, temp.gender);
        strcpy(newNode->nationality, temp.nationality);
        strcpy(newNode->religion, temp.religion);
        strcpy(newNode->occupation, temp.occupation);
        //printf("pie\n");
    }
    else
    {
        while (1)
        {
            //printf("Entered while\n");
            if (Harray[index].key[0] == '\n')
            {

                strcpy(Harray[index].key, s);
                Harray[index].freq++;
                numterms++;
                //Harray[index].next = temp;

                strcpy(Harray[index].surname, temp.surname);
                strcpy(Harray[index].id, temp.id);
                strcpy(Harray[index].did, temp.did);
                strcpy(Harray[index].forename, temp.forename);
                strcpy(Harray[index].age, temp.age);
                strcpy(Harray[index].person_type, temp.person_type);
                strcpy(Harray[index].gender, temp.gender);
                strcpy(Harray[index].nationality, temp.nationality);
                strcpy(Harray[index].religion, temp.religion);
                strcpy(Harray[index].occupation, temp.occupation);

                break;
            }
            else
            {
                i++;
                index = hash3(s, i);
                collisions++;
            }
        }
    }
}

int next_field(FILE *csv, char *buffer, int max_len)
{
    char c;
    int n = 0;
    bool qm = 0;
    do
    {
        c = fgetc(csv);
        if (c == '"')
        {
            if (qm == 0)
            {
                qm = 1;
            }
            else
            {
                qm = 0;
            }
        }
        else if (c == ',' && qm == 0)
        {
            buffer[n] = '\0';
            return 0;
        }
        else if (c == '\n' || c == EOF)
        {
            return 1;
        }
        else
        {
            buffer[n] = c;
            n++;
        }

    } while (n < max_len);
}
void print_table()
{
    //printf("Entered print table\n");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (Harray[i].key[0] == '\n')
        {
            printf("\t%d\t----\n", i);
        }
        else
        {
            printf("\t%d\t%s\t%d\n", i, Harray[i].key, Harray[i].freq);
        }
    }
}

void load()
{
    //printf("Entered load\n");
    char *field;
    int a;
    Node temp;

    field = (char *)malloc(sizeof(char) * MAX_STRING_SIZE);
    FILE *csv = fopen("people.csv", "r");
    //printf("opened\n");
    if (csv == NULL)
        perror("Error opening file");
    else
    {
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);

        while (!feof(csv))
        {

            a = next_field(csv, field, MAX_STRING_SIZE);
            //printf("%s\n\n\n", field);
            strcpy(temp.id, field);
            //printf("%s\n\n\n", temp.id);

            a = next_field(csv, field, MAX_STRING_SIZE);
            strcpy(temp.did, field);

            a = next_field(csv, field, MAX_STRING_SIZE);
            strcpy(temp.surname, field);

            a = next_field(csv, field, MAX_STRING_SIZE);
            strcpy(temp.forename, field);

            a = next_field(csv, field, MAX_STRING_SIZE);
            strcpy(temp.age, field);

            a = next_field(csv, field, MAX_STRING_SIZE);
            strcpy(temp.person_type, field);

            a = next_field(csv, field, MAX_STRING_SIZE);
            strcpy(temp.gender, field);

            a = next_field(csv, field, MAX_STRING_SIZE);
            strcpy(temp.nationality, field);

            a = next_field(csv, field, MAX_STRING_SIZE);
            strcpy(temp.religion, field);

            a = next_field(csv, field, MAX_STRING_SIZE);
            strcpy(temp.occupation, field);

            //printf("wah %s\n", temp.surname);
            insert(temp);
        }
    }
    //printf("finishing load\n");
    free(field);
    fclose(csv);
}

void print_list(int a)
{
    printf("Person ID  Deposition ID Surname Forename  Age Person Type Gender Nationality Religion Occupation\n");
    Node *node = &Harray[a];
    do
    {
        printf("%s      %s    %s  %s    %s   %s   %s   %s   %s   %s \n", node->id, node->did, node->surname, node->forename, node->age, node->person_type, node->gender, node->nationality, node->religion, node->occupation);
        node = node->next;
    } while (node != NULL);
}

void node_destro(){
    for(int i = 0; i < ARRAY_SIZE; i++){
        if(Harray[i].freq > 1){
            Node* temp = Harray[i].next;
            while(temp != NULL){
                Node* temp1 = temp->next;
                free(temp);
                temp = temp1;
            }
        }
    }
}

int main()
{
    char name[MAX_STRING_SIZE];
    makeArray();
    //printf("Loading\n");
    load();
    //printf("printing\n");
    print_table();
    //printf("finished printing\n");

    char input[MAX_STRING_SIZE];

    printf("Capacity      : %d\n", ARRAY_SIZE);
    printf("Numterms      : %d\n", numterms);
    printf("Collisions    : %d\n", collisions);
    printf("Enter term to get frequency or type \"quit\" to escape: ");
    scanf("%[^\n]%*c", input);
    while (strcmp(input, "quit") != 0)
    {

        //printf("%s\n", input);
        int a = search(input);
        if (a == -1)
        {
            printf("%s not in table\n", input);
        }
        else
        {
            printf("%s: %d\n", Harray[a].key, Harray[a].freq);
            print_list(a);
        }
        printf("Enter term to get frequency or type \"quit\" to escape: ");
        scanf("%[^\n]%*c", input);
    }
    printf("See ya later nerd!\n");
    node_destro(); //freeing memory
}