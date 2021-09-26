#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MIN 99999999
#define MAX_STRING_SIZE 100
#define ARRAY_SIZE 8000

struct node
{

    char name[MAX_STRING_SIZE];
    char longitude[MAX_STRING_SIZE];
    char latitude[MAX_STRING_SIZE];
    int id;
    
};

struct node stops[ARRAY_SIZE];
int graph[ARRAY_SIZE][ARRAY_SIZE];
int count = 0;
int gcount = 0;

void init(){
    for(int i = 0; i<ARRAY_SIZE; i++){
        stops[i].id = 0;
    }
}

void initg(){
    for(int i = 0; i<ARRAY_SIZE; i++){
        for(int a = 0; a<ARRAY_SIZE; a++){
        graph[i][a] = MIN;
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



void load()
{
    //printf("Entered load\n");
    char *field;
    int a;
    struct node temp;
    
    field = (char *)malloc(sizeof(char) * MAX_STRING_SIZE);
    FILE *csv = fopen("vertices.csv", "r");
    //printf("opened\n");
    if (csv == NULL)
        perror("Error opening file");
    else
    {
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        

        while (!feof(csv))
        {

            a = next_field(csv, field, MAX_STRING_SIZE);
            temp.id= atoi(field);

            a = next_field(csv, field, MAX_STRING_SIZE);
            strcpy(temp.name, field);
            memset(field, '\0', MAX_STRING_SIZE);

            a = next_field(csv, field, MAX_STRING_SIZE);
            strcpy(temp.latitude, field);
            memset(field, '\0', MAX_STRING_SIZE);

            a = next_field(csv, field, MAX_STRING_SIZE);
            strcpy(temp.longitude, field);
            memset(field, '\0', MAX_STRING_SIZE);

            stops[temp.id] = temp;
            count++;
        }
    }
    printf("finishing load\n");
    free(field);
    fclose(csv);
}

void loadgraph(){
    //printf("Entered load\n");
    char *field;
    int a;
    //struct node temp;
    int x,y,z;
    field = (char *)malloc(sizeof(char) * MAX_STRING_SIZE);
    FILE *csv = fopen("edges.csv", "r");
    //printf("opened\n");
    if (csv == NULL)
        perror("Error opening file");
    else
    {
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        a = next_field(csv, field, MAX_STRING_SIZE);
        

        while (!feof(csv))
        {

            a = next_field(csv, field, MAX_STRING_SIZE);
            x = atoi(field);

            a = next_field(csv, field, MAX_STRING_SIZE);
            y = atoi(field);

            a = next_field(csv, field, MAX_STRING_SIZE);
            z = atoi(field);
            
            graph[x][y] = z;
            graph[y][x] = z;
            gcount++;
        }
    }
    printf("finishing load\n");
    free(field);
    fclose(csv);
}
void print_stops()
{
    printf("\n");
    int a = 0;
    while(a < ARRAY_SIZE)
    {
        if(stops[a].id != 0){
            printf("%d      %s    %s  %s \n", stops[a].id, stops[a].name, stops[a].longitude, stops[a].latitude);
        }
        a++;
    } 
}

void print_graph(){
    printf("\n");
    for(int i = 0; i<ARRAY_SIZE; i++){
        for(int a = 0; a<ARRAY_SIZE; a++){
        if(graph[i][a] != MIN){
        printf("%d  %d  %d\n",i,a,graph[i][a]);
        }
    }
    }
    
}

void printnode(int a){
    printf("%d      %s    %s  %s \n", stops[a].id, stops[a].name, stops[a].longitude, stops[a].latitude);
}

void dijkstra(int cost[ARRAY_SIZE][ARRAY_SIZE], int start, int end){
    int  dist[ARRAY_SIZE], prev[ARRAY_SIZE], perm[ARRAY_SIZE], current, min, distance, previous;

    for(int i = 0; i < ARRAY_SIZE; i++){
        dist[i] = cost[start][i];
        prev[i] = start;
        perm[i] = 0;
    }
    
    dist[start] = 0;
    perm[start] = 1;
    int count = 1;
    current = 0;

    printf("\nRoute:\n ");
    printnode(start);

    while(perm[end]==0){
        min = MIN;

        for(int i = 1; i < ARRAY_SIZE; i++){
            distance = dist[current] + cost[current][i];

            if(distance < dist[i] && perm[i] == 0){
                dist[i] = distance;
                prev[i] = current;
            }
            
            if(min > dist[i] && perm[i] == 0){
                min = dist[i];
                current = i;
            }
        }
        
        perm[current] = 1;
        printf(" - ");
        printnode(current);
        
    }
    printf("\n");

    for(int i = 1; i < ARRAY_SIZE; i++){
        if(i == end){
        printf("Distance: A-> ");
        printnode(i);
        printf(" = %d\n", dist[i]);
        }
    }
    printf("\n\n");
}

int main(){
    init();
    load();
    //print_stops();
    
    initg();
    loadgraph();
    //print_graph();

    dijkstra(graph, 300, 253);

}