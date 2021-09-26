// Oisin Cousins 18323211 23/10/20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 18626
#define MAX_STRING 100

struct igns {
    char title[MAX_STRING];
    char platform[MAX_STRING];
    int score;
    int year;
};

struct igns array[MAX];

int next_field( FILE *f, char *buf, int dax ) {
	int i=0, end=0, quoted=0;
	
	for(;;) {
		// fetch the next character from file		
		buf[i] = fgetc(f);
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted) { break; }
		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n') { end=1; break; } 
		// truncate fields that would overflow the buffer
		if( i<dax-1 ) { ++i; } 
	}

	buf[i] = 0; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}


int swaps = 0;
int comps = 0;

void fetch_ign(FILE *csv, struct igns *pog){
    char buf[MAX_STRING];

    next_field( csv, pog->title, MAX_STRING ); 
    next_field( csv, pog->platform, MAX_STRING );
    next_field( csv, buf, MAX_STRING );  
    pog->score = atoi(buf);
    next_field( csv, buf, MAX_STRING );  
    pog->year = atoi(buf);

};



void print_ign(struct igns *pog){
    printf("   %s, %s, %d, %d\n", pog->title,pog->platform,pog->score,pog->year);
};




void bubblesort(struct igns array[]) 
{ 
   int i, j; 
   bool swapped; 
   for (i = 0; i < MAX-1; i++) 
   { 
     swapped = false; 
     for (j = 0; j < MAX-i-1; j++) 
     { 
        if (array[j].score > array[j+1].score) 
        { 
           swaps++;
           struct igns temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
           swapped = true; 
        }
        comps++; 
     } 
   
     if (swapped == false) 
        break; 
   } 
} 


int main(){
    printf("beginning\n\n");
    FILE *f;
    //struct igns array[MAX];
    struct igns pog;
    
    f  = fopen("ign.csv", "r");
    printf("fetching file\n\n");
    fetch_ign(f, &pog);
    

    int count = 0;

    while(!feof(f)){
        fetch_ign(f, &array[count]);
        //print_ign(&array[count]);
        count++;
    }
    printf("sorting\n\n");
    bubblesort(array);
    for(int i = MAX-10; i < MAX ; i++){
        print_ign(&array[i]);
    }

    
    printf("\n\nSWAPS: %d\n", swaps);
    printf("COMPS: %d\n", comps);
    printf("\n\nTests Complete\n\n");
}
