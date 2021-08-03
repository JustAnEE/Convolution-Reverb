#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

class Song {

public:

// Attributes
unsigned char* chunkID = (unsigned char*) malloc (sizeof(unsigned char)*4) ; // RIFF
uint32_t chunkSize; // Size of entire file minus 8 bytes.
unsigned char* format = (unsigned char*) malloc (sizeof(unsigned char)*4) ; // WAVE
unsigned char subchunk1ID[4];
uint32_t subchunk1Size;
uint32_t audioFormat;
uint32_t numChannels;
uint32_t sampleRate;
uint32_t byteRate;
uint32_t blockAlign;
uint32_t bitsPerSample;
unsigned char* subchunk2ID = (unsigned char*) malloc (sizeof(unsigned char)*4) ;
uint32_t subchunk2Size;
uint32_t num_of_samples;
float *audio_array;


/* Methods:
These FILE * methods collect the header information from the .wav file and
set the corresponding attributes in the class. They also return the file
pointer in order to update it in the main function. */
FILE *set_chunkID(FILE *filestart);
FILE *set_chunkSize(FILE *fp);
FILE *set_format(FILE *fp);
FILE *set_subchunk1ID(FILE *fp);
FILE *set_subchunk1Size(FILE *fp);
FILE *set_audioFormat(FILE * fp);
FILE *set_numChannels(FILE *fp);
FILE *set_sampleRate(FILE *fp);
FILE *set_byteRate(FILE *fp);
FILE *set_blockAlign(FILE *fp);
FILE *set_bitsPerSample(FILE *fp);
FILE *set_subchunk2ID(FILE *fp);
FILE *set_subchunk2Size(FILE *fp);
FILE *get_data(FILE *fp);

};


int main(void){

  Song test;
  FILE *wavFile;
  wavFile = fopen("filepath", "r");

  // -- Unreadable code: Will change later.
  wavFile = test.set_chunkID(wavFile);
  wavFile = test.set_chunkSize(wavFile);
  wavFile = test.set_format(wavFile);
  wavFile = test.set_subchunk1ID(wavFile);
  wavFile = test.set_subchunk1Size(wavFile);
  wavFile = test.set_audioFormat(wavFile);
  wavFile = test.set_numChannels(wavFile);
  wavFile = test.set_sampleRate(wavFile);
  wavFile = test.set_byteRate(wavFile);
  wavFile = test.set_blockAlign(wavFile);
  wavFile = test.set_bitsPerSample(wavFile);
  wavFile = test.set_subchunk2ID(wavFile);
  wavFile = test.set_subchunk2Size(wavFile);

  // -- Number of samples per channel
  test.num_of_samples = test.subchunk2Size/4;

  wavFile = test.get_data(wavFile);

  fclose(wavFile);

  // Testing stuff
  cout << "ChunkID: " << test.chunkID << "\n";
  cout << "ChunkSize: " << test.chunkSize << "\n";
  cout << "Format: " << test.format << "\n";
  cout << "SubChunk1ID: " << test.subchunk1ID << "\n";
  cout << "SubChunk1 Size:" << test.subchunk1Size << "\n";
  cout << "Audio Format: " << test.audioFormat << "\n";
  cout << "Number of Channels:" << test.numChannels << "\n";
  cout << "Sample Rate (Hz): " << test.sampleRate << "\n";
  cout << "Byte Rate (bytes/s): " << test.byteRate << "\n";
  cout << "Bytes in One Data Block: " << test.blockAlign << "\n";
  cout << "Bits Per Sample: " << test.bitsPerSample << "\n";
  cout << "SubChunk2ID: " << test.subchunk2ID << "\n";
  cout << "SubChunk2Size: " << test.subchunk2Size << "\n";
  cout << "Num of Samples: " << test.num_of_samples << "\n";

  // Releasing allocated memory
  free(test.chunkID);
  free(test.format);
  free(test.subchunk2ID);
  free(test.audio_array);

  return 0;

}


FILE* Song :: set_chunkID(FILE *filestart){


  fread(chunkID, 4, 1, filestart);


  return filestart;

}


FILE*  Song :: set_chunkSize(FILE *fp){

  unsigned char buffer[4];
  fread(buffer, sizeof(buffer), 1, fp);

  // -- Convert to Big endian
  chunkSize = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);

  return fp;

}


FILE* Song :: set_format(FILE *fp){


  fread(format, sizeof(format), 1, fp);

  return fp;

}


FILE* Song :: set_subchunk1ID(FILE *fp){

  fread(subchunk1ID, sizeof(subchunk1ID), 1, fp);

  return fp;

}


FILE* Song :: set_subchunk1Size(FILE  *fp){

  unsigned char buffer[4];

  fread(buffer, sizeof(buffer), 1, fp);

  subchunk1Size = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);

  return fp;

}


FILE* Song :: set_audioFormat(FILE *fp){

  unsigned char buffer[2];

  fread(buffer, sizeof(buffer), 1, fp);


  audioFormat = buffer[0] | (buffer[1] << 8);

  return fp;

}


FILE* Song :: set_numChannels(FILE *fp){

    unsigned char buffer[2];

    fread(buffer, sizeof(buffer), 1, fp);

    numChannels = buffer[0] | (buffer[1] << 8);

    return fp;

}


FILE* Song :: set_sampleRate(FILE *fp){

  unsigned char buffer[4];

  fread(buffer, 4, 1, fp);

  sampleRate = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24) ;


  return fp;

}


FILE* Song :: set_byteRate(FILE *fp){

  unsigned char buffer[4];

  fread(buffer, sizeof(buffer), 1, fp);

  byteRate = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24) ;

  return fp;

}


FILE* Song :: set_blockAlign(FILE *fp){

  unsigned char buffer[2];

  uint32_t size = 1;
  fread(buffer, sizeof(buffer), 1, fp);

  blockAlign =  buffer[0] | (buffer[1] << 8) ;

  return fp;

}


FILE* Song :: set_bitsPerSample(FILE *fp){

  unsigned char buffer[2];

  uint32_t size = 1;
  fread(buffer, sizeof(buffer), 1, fp);

  bitsPerSample = buffer[0] | (buffer[1] << 8);

  return fp;

}


FILE* Song :: set_subchunk2ID(FILE *fp){

unsigned char data[] = "data";

int i = 1;
while(!feof(fp)){

    fread(subchunk2ID, 4, 1, fp);

    if ((subchunk2ID[0] == data[0]) && (subchunk2ID[1] == data[1]) && (subchunk2ID[2] == data[2]) && (subchunk2ID[3] == data[3])){
      // Now subchunk2ID is set to data and the file pointer is ready at the next byte.
      break;
    }
}

  return fp;

}


FILE* Song :: set_subchunk2Size(FILE *fp){

  unsigned char buffer[4];

  fread(buffer, sizeof(buffer), 1, fp);

  subchunk2Size = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);

  return fp;

}


FILE* Song :: get_data(FILE *fp){

  audio_array = (float*) malloc (sizeof(float)*num_of_samples);
  unsigned char *buffer = (unsigned char*) malloc (sizeof(unsigned char)*4);

  // The size of one sample is 4 bytes.
  for (int i = 0; i < num_of_samples; i++){

    fread(buffer, sizeof(buffer), 1, fp);

    audio_array[i] = buffer[0] | (buffer[1] << 8);

  }

  cout << audio_array[0] << "\n" << audio_array[1] << "\n" << audio_array[2] << "\n";

  return fp;
}
