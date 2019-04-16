#include <stdio.h>
#include "sound.h"
#include <math.h>
#include "screen.h"
void fillID(char *d, const char *s)  
{
	for(int i= 0 ; i<4 ; i++)
	*d++ =*s++;
}

void testTone(int c, int fl , int fr , float d)
{

	if(c<1 || c>2) { 
		printf("Wrong number of channels .\n");
		return;
	 }
	if(fl <50  || fl>16000) {
		printf("Frequency is out of range\n");
		return;
	}
	if(d<1.0 || d>10.0) {
		printf("Wrong duration\n");
		return;
	}
	// All the arguments are okay , the rest of code is to make a correct wave
   // header 2) generate correct samples 3) write both header and samples to 
	// a file 
	struct  WAVHDR h;
	int samples = 44100*d;
	fillID(h.ChunkID,"RIFF");
	fillID(h.Format,"WAVE");
	fillID(h.Subchunk1ID,"fmt  ");
	fillID(h.Subchunk2ID, "data  ");
	h.Subchunk1Size = 16;    // constant value 
	h.AudioFormat = 1;
	h.SampleRate = 44100;
	h.BitsPerSample = 16;
	h.BlockAlign =  c*16/8;
	h.NumChannels = c;
	h.ByteRate = 44100*c*16/8;
	h.Subchunk2Size = samples*c*16/8;
	h.ChunkSize = h.Subchunk2Size + 36;

	FILE *fp = fopen("testTone.wav","w");

	if( fp == NULL ) {
		printf("Cannot open a file\n");
		return;
	}
	fwrite(&h, sizeof(h), 1 ,fp );   // write the header to file 
	// generate samples and write to a file 
	for(int i = 0 ; i<samples ; i++) {
		short sL = 32767.0* sin(2*PI*fl*i/44100);
		fwrite(&sL, sizeof(short), 1 ,fp );
		if (c==2){
 			short sR =  32767.0*sin(2*PI*fr*i/44100);
			fwrite(&sR , sizeof(short) ,1,fp );   
		}
	}  // end of for
	fclose(fp); // close the file
	printf("TestTone is generated.\n");

}
void showID( char *idname ,char  *id)  {
	int i;
	printf("%s : " , idname);

	for (i = 0 ; i<4 ; i++)
		printf("%c" , id[i]);
	puts(""); 

}

int findPeaks(int d[])  {
    int c = 0;
    for(int i ; i<80 ; i++ )  {
        if(d[i] >= 75  && d[i-1]<75) c++;
    }
	if(d[0] >=75 ) c++;
	return c;

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
	int peaks = findPeaks(dB);
	setColors(WHITE, bg(BLACK));
	printf("\033[1;61H");
	printf("Peaks: %d            \n",peaks);

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
	

	
