
#include<stdlib.h>  // for random values
// #include<time.h>   // for randomization (using system time)
#include "screen.h"
#include<stdio.h>
#include "sound.h"
#include <signal.h>
#include "comm.h"

int main(int argc, char **argv) {
	if(argc>1)  {      // if a user has given some command line argument 
 		printf("Test tone generator\n");
		int fR,fL,ch;
		float duration;
		printf("NO . of channels (1 or 2):");
		scanf("%d" , &ch) ;
		if ( ch == 1 ) {
			printf("Mono frequency: ");
			scanf("%d", &fL );
			

		}
		else if(ch == 2) {
			printf("Give me Left and Right freq: ");
			scanf(" %d %d ",&fL , &fR  );
		}
		else   {
			printf("Wrong number of channels\n");
			return 1;
		}
		printf("Duration of sound : ");
		scanf("%f",&duration );
		testTone(ch , fL, fR , duration);
		return 0;

	}
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
