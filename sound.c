#include <stdio.h>
#include "sound.h"
#include <math.h>
#include "screen.h"


void showID( char *idname ,char  *id)  {
	int i;
	printf("%s : " , idname);

	for (i = 0 ; i<4 ; i++)
		printf("%c" , id[i]);
	puts(""); 

}

// this function gets one second of samples (16000), and calculates 80 
// pieces of decibel value , we know we need to calculate one decibel 
// value from 200 samples , decibel value is calculated by RMS formula  
void displayWAVDATA(short s[]) {
	double rms[80];
	int dB[80];
	short *ptr=s;     // we use a pointer , pointing to the beginning of 
// an array
	int i, j ;      // for nested loop counters , outer loop repeats 80 times
					// the inner loop  repeats 200 times  

	for(i = 0 ; i<80 ; i++)  {
		double sum  = 0;
			for(j=0 ; j<200 ; j++ ) {
				sum +=(*ptr) * (*ptr);
				ptr++;   // pinting to the next sample

	}
	rms[i] = sqrt(sum/200);



#ifdef DEBUG
	printf("rms[%d] = %f\n" ,i , rms[i]);
#endif 
	dB[i] = 20*log10(rms[i]);

}
	


#ifndef DEBUG

	barChart(dB);

#endif 



}
void displayWAVHDR(struct WAVHDR h) {
#ifdef DEBUG

	showID("ChunkID " , h.ChunkID );
	printf("Chunk size : %d\n" , h.ChunkSize );
	showID("Format " , h.Format );
	showID("SubChunk1ID " , h.Subchunk1ID );
	printf("SubChunk1Size : %d\n " , h.Subchunk1Size );
	printf("AudioFormat : %d\n" , h.AudioFormat );
	printf("Number of Channels : %d\n" , h.NumChannels );
	printf("Sample Rate %d\n :" , h.SampleRate);
	printf("Byte Rate :%d\n" , h.ByteRate );
	printf("Block Align : %d\n " , h.BlockAlign );
	printf("Bits Per Sample : %d\n " , h.BitsPerSample );
	showID("Subchunk2ID" , h.Subchunk2ID);
	printf("Subchunk 2 Size : %d\n" , h.Subchunk2Size);
	
#else
	setColors(WHITE,bg(RED));
	printf("\033[1;1H]");
	printf("test.wav                   ");
	setColors(YELLOW,bg(BLUE));
	printf("\033[1;21H");
	printf("Sample rate : %d      ", h.SampleRate);
	setColors(CYAN , bg(MAGENTA));
	printf("\033[1;41H");
	printf("Duration :%.2f          ",(float)h.Subchunk2Size/h.ByteRate);
	setColors(RED , bg(YELLOW));

#endif	



}
	

	
