/*
 * Sound Manager
 *
 * Copyright (c) 2015 by Can Firat Gocmen
 * 
 */

/* Sound Manager object provides processes of loading and playing RIFF Wave
 * files (PCM 8-16 BIT) */

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cstdlib> 
#include <cstdio> 

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include "sound/SoundManager.h"

#define NO_NAME "NONAME"

ALenum get_format(short bit_for_sample, short channels){
   ALenum format=0;

   if(bit_for_sample == 8) 
   { 
      if(channels == 1) 
         format = AL_FORMAT_MONO8; 
      else if(channels == 2) 
         format = AL_FORMAT_STEREO8; 
   } 
   else if(bit_for_sample == 16) 
   { 
      if(channels == 1) 
         format = AL_FORMAT_MONO16; 
      else if(channels == 2) 
         format = AL_FORMAT_STEREO16; 
   } 

   return format;
}

int SoundManager::find_source_by_name(const char* sound_name){
   for(int c = 0; c<sounds.size(); c++){
      /* printf("c1: %s |",   sound_name);
         printf("c2: %s | \n",sounds[c].name); */
      if(strcmp(sounds[c].name, sound_name) == 0){
         return (sounds[c].source);
      }else{
         // Need to add error function here!
      }
   }
}

SoundManager::SoundManager() {	
   // For deleting all the buffers at once

   // this->number_of_sounds = number_of_sounds;
   // sounds = (sound*) malloc(number_of_sounds);

   /* sound_buffers = (ALuint*) malloc(number_of_sounds);
      sound_sources = (ALuint*) malloc(number_of_sounds); */

   number_of_sounds = 0;
   current_sound    = 0;

   sounds.reserve(number_of_sounds);  

/* current_context = alcGetCurrentContext();   
   current_device = alcGetContextsDevice(current_context); */

   // Initiating OpenAL 
   current_device = alcOpenDevice(NULL);                                            
   current_context = alcCreateContext(current_device, NULL);                                   
   alcMakeContextCurrent(current_context);               

/*                  ALUT Version                  */     

/*    int error = alGetError();
      if (error)
         printf("%s\n", alutGetErrorString(error)); */
}

SoundManager::~SoundManager(){
   alcMakeContextCurrent(NULL);

   alcDestroyContext(current_context);
   alcCloseDevice(current_device); 
   
   // This need to be reimplemented   

   /* alDeleteSources(number_of_sounds, sound_sources);
      alDeleteBuffers(number_of_sounds, sound_buffers);*/
   
   for(uint c = 0; c<sounds.size(); c++){
       alDeleteSources(1,&sounds[c].source);
       alDeleteBuffers(1,&sounds[c].buffer);
   }
}

int SoundManager::load(const char* name, const char* file_name){
   number_of_sounds++;
   sounds.resize(number_of_sounds);

/*                  ALUT Version                  */     

/* sound_buffers[current_sound] = alutCreateBufferFromFile(sound_name); */ 

   FILE *file_ptr;
   file_ptr = fopen(file_name,"rb");

   if (file_ptr) 
   { 
      RIFF_Wave_file* sound_file = (RIFF_Wave_file*) malloc(sizeof(RIFF_Wave_file));
      fread(sound_file ,sizeof(RIFF_Wave_file), 1, file_ptr);

      ALenum format = get_format(sound_file->bits_per_sample, 
                                 sound_file->channels);
   /*   
      printf("------------- INFO -------------    \n");
      printf("FORMAT TYPE :              %d       \n", sound_file->format_type);
      printf("BITS PER SAMPLE :          %d       \n", sound_file->bits_per_sample);
      printf("FILE SIZE :                %d       \n", sound_file->size);
      printf("CHANNEL NUMBER             %d       \n", sound_file->channels);
      printf("FREQUENCY :                %d       \n", sound_file->sample_rate);
      printf("AVERAGE BYTES PER SECOND : %d       \n", sound_file->average_bytes_per_second);
      printf("BYTES PER SAMPLE           %d       \n", sound_file->bytes_per_sample);
      printf("BITS PER SAMPLE            %d       \n", sound_file->bits_per_sample);
      printf("DATA SIZE :                %d BYTES \n", sound_file->data_size);
      printf("FORMAT :                   %d       \n", format);
   */       

      unsigned char* data = new unsigned char[sound_file->data_size];
      printf("%d BYTES of sound data loaded. \n", 
              fread(data, sizeof(unsigned char),sound_file->data_size,file_ptr));
      
      ALuint freq = sound_file->sample_rate; // as unsigned int of OpenAL
                                          
      alGenBuffers(1, &sounds[current_sound].buffer);
      alGenSources(1, &sounds[current_sound].source);
     
      // If there is a problem with generating Source
      if(alGetError() != AL_NO_ERROR){ 
         printf("Couldn't Generate Source! (alGenSource/s()) \n");
      } 
        
      alBufferData(sounds[current_sound].buffer, 
                   format,
                   data, 
                   sound_file->data_size,
                   freq);

      delete(sound_file);
      free(data);

      // If there is a problem with loading buffer                 
      if(alGetError() != AL_NO_ERROR){ 
         printf("Couldn't Load Buffer! (alBufferData()) \n");
      } 
      
      // Linking Source
      alSourcei(sounds[current_sound].source, AL_BUFFER, 
                sounds[current_sound].buffer);
         
      strncpy(sounds[current_sound].name,name,sizeof(name));
      current_sound++;

      return sounds[current_sound].source;
   }else{printf("Couldn't Find File! (fopen()) \n");}
   // a function is needed for giving errors.
   // ? what to return here

}

int SoundManager::open(const char* file_name){
   return load(NO_NAME,file_name);
}

int SoundManager::open(const char* sound_name, const char* file_name){
   return load(sound_name, file_name);
}

void SoundManager::play(ALuint sound){
   alSourcePlay(sound);
}

void SoundManager::play(const char* sound_name){
   alSourcePlay(find_source_by_name(sound_name));
}

void SoundManager::loop(ALuint sound, bool do_loop){
   if(do_loop)
      alSourcei(sound, AL_LOOPING,  AL_TRUE);
   else
      alSourcei(sound, AL_LOOPING,  AL_FALSE);
}

void SoundManager::stop(ALuint sound){
   alSourceStop(sound);
}
