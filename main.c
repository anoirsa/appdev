
#include<stdlib.h>  // for random values
// #include<time.h>   // for randomization (using system time)
#include "screen.h"
#include<stdio.h>
#include "sound.h"
#include <signal.h>
#include "comm.h"

int main() {
	FILE *f;
	short sd[RATE];
	while(1) {
		int ret = system(RCMD);
		if( ret == SIGINT)  break;		
		f = fopen("test.wav" , "r");
		if(f==NULL) {
			printf("CaNNOT OPEN THE FILE\n");
			return 1;
	}
	// int dec[COL],i;   //80 pieces of sound decibels
	//  srand(time(NULL));
	// for( i=0 ; i<COL ; i++) dec[i]= rand()%70+30;
		clearScreen();
//		setColors(RED, bg(YELLOW));

		struct WAVHDR hdr;
		fread(&hdr,sizeof(hdr) , 1 , f); // read WAV header
		fread(&sd , sizeof(sd) , 1 , f);
		fclose(f);
		displayWAVHDR(hdr);
		displayWAVDATA(sd);
		sendDATA(sd);
	}
	// barChart(dec);
	//printf("Message form main\n");
	resetColors();
	//  getchar();
}
