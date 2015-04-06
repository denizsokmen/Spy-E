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

#include "sound/Sounds.h"

#define NO_NAME "NONAME"

#define TEMP_FMT_AU AL_FORMAT_STEREO16

#define swap_uint32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) |  \
                       (((x) & 0x0000FF00) << 8) | ((x) << 24))    \

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

bool check_wave_riff(char* data_t, char* WAVE_t){
   bool ifWAVEriff = false;
   if((data_t[0] == 'd' && data_t[1] == 'a' && data_t[2] == 't' && data_t[3] == 'a') &&
      (WAVE_t[0] == 'W' && WAVE_t[1] == 'A' && WAVE_t[2] == 'V' && WAVE_t[3] == 'E')){ 
      /* WAVE */
      ifWAVEriff = true;
      printf("RIFF WAVE FILE, confirmed...");
   }
   return ifWAVEriff;
}

bool check_SUN_AU(char* AU_t){
   bool ifSUNau = false;
   if(AU_t[0] == '.' && AU_t[1] == 's' && AU_t[2] == 'n' && AU_t[3] == 'd'){ 
      /* .snd */
      ifSUNau = true;
      printf("Sun AU FILE, confirmed...");
   }
   return ifSUNau;
}

int Sounds::find_source_by_name(const std::string sound_name){
   for(int c = 0; c<sounds.size(); c++){
      /* printf("c1: %s |",   sound_name);
         printf("c2: %s | \n",sounds[c].name); */
      if(!(sounds[c].name != sound_name)){
         return (sounds[c].source);
      }else{
         // Need to add error function here!
      }
   }
}

Sounds::Sounds() {
   /* For deleting all the buffers at once

      this->number_of_sounds = number_of_sounds;
      sounds = (sound*) malloc(number_of_sounds);

      sound_buffers = (ALuint*) malloc(number_of_sounds);
      sound_sources = (ALuint*) malloc(number_of_sounds);

      current_context = alcGetCurrentContext();
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

Sounds::~Sounds() {
   alcMakeContextCurrent(NULL);

   alcDestroyContext(current_context);
   alcCloseDevice(current_device); 
   
   // This need to be reimplemented   

   /* alDeleteSources(number_of_sounds, sound_sources);
      alDeleteBuffers(number_of_sounds, sound_buffers);*/
   
   for(int c = 0; c<sounds.size(); c++){
       alDeleteSources(1,&sounds[c].source);
       alDeleteBuffers(1,&sounds[c].buffer);
   }
}

int Sounds::loadWAV(const std::string name, const std::string file_name){

/*                  ALUT Version                  */     

/* sound_buffers[current_sound] = alutCreateBufferFromFile(sound_name); */ 

   FILE *file_ptr;
   file_ptr = fopen(file_name.data(),"rb");

   sound c_sound; // rel

   if (file_ptr) 
   { 
      RIFF_Wave_file* sound_file = (RIFF_Wave_file*) malloc(sizeof(RIFF_Wave_file));
      fread(sound_file ,sizeof(RIFF_Wave_file), 1, file_ptr);

      ALenum format = get_format(sound_file->bits_per_sample, 
                                 sound_file->channels);

   /* File chunk check */
      check_wave_riff(sound_file->data_t, sound_file->WAVE_t);
   /*   
      printf("------------- INFO -------------    \n");
      printf("RIFF WAVE File :                    \n", sound_file->format_type);
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
                                          
      alGenBuffers(1, &c_sound.buffer);
      alGenSources(1, &c_sound.source);
     
      // If there is a problem with generating Source
      if(alGetError() != AL_NO_ERROR){ 
         printf("Couldn't Generate Source! (alGenSource/s()) \n");
      } 
        
      alBufferData(c_sound.buffer, 
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
      alSourcei(c_sound.source, AL_BUFFER, 
                c_sound.buffer);
         
      c_sound.name = name;
      sounds.push_back(c_sound);

      return c_sound.source;
   }else{printf("Couldn't Find File! (fopen()) \n");}
   // a function is needed for giving errors.
   // ? what to return here

}

int Sounds::loadAU(const std::string name, const std::string file_name){

   FILE *file_ptr;
   file_ptr = fopen(file_name.data(),"rb");

   sound c_sound;

   if (file_ptr) 
   { 
      AU_file* sound_file = (AU_file*) malloc(sizeof(AU_file));
      fread(sound_file ,sizeof(AU_file), 1, file_ptr);

   /* Need to be swap Little endian */
      sound_file->chunk_size  = swap_uint32(sound_file->chunk_size);
      sound_file->data_size   = swap_uint32(sound_file->data_size);
      sound_file->sample_rate = swap_uint32(sound_file->sample_rate);
      sound_file->channels    = swap_uint32(sound_file->channels);

   /* ALenum format = get_format(sound_file->bits_per_sample, 
                                 sound_file->channels); */

      check_SUN_AU(sound_file->AU_t);
   /*   
      printf("------------- INFO -------------    \n");
      printf("Sun AU File :                       \n", sound_file->format_type);
      printf("CHANNEL NUMBER             %d       \n", sound_file->channels);
      printf("FREQUENCY :                %d       \n", sound_file->sample_rate);
      printf("DATA SIZE :                %d BYTES \n", sound_file->data_size);
   */       

      unsigned char* data = new unsigned char[sound_file->data_size];
      printf("%d BYTES of sound data loaded. \n", 
              fread(data, sizeof(unsigned char),sound_file->data_size,file_ptr));
      
      ALuint freq = sound_file->sample_rate; // as unsigned int of OpenAL
                                          
      alGenBuffers(1, &c_sound.buffer);
      alGenSources(1, &c_sound.source);
     
      if(alGetError() != AL_NO_ERROR){ 
         printf("Couldn't Generate Source! (alGenSource/s()) \n");
      } 
        
      alBufferData(c_sound.buffer, 
                   TEMP_FMT_AU, // This need to be re-implemented
                   data, 
                   sound_file->data_size,
                   freq);

      delete(sound_file);
      free(data);

      if(alGetError() != AL_NO_ERROR){ 
         printf("Couldn't Load Buffer! (alBufferData()) \n");
      } 
      
      alSourcei(c_sound.source, AL_BUFFER, 
                c_sound.buffer);
         
      c_sound.name = name;
      sounds.push_back(c_sound);

      return c_sound.source;
   }else{printf("Couldn't Find File! (fopen()) \n");}
   // a function is needed for giving errors.
   // ? what to return here

}

int Sounds::open(const std::string file_name){
   return loadWAV(NO_NAME,file_name);
}

int Sounds::open(const std::string sound_name,const std::string file_name){
   return loadWAV(sound_name, file_name);
}

void Sounds::play(ALuint sound){
   alSourcePlay(sound);
}

void Sounds::play(const std::string sound_name){
   alSourcePlay(find_source_by_name(sound_name));
}

void Sounds::loop(ALuint sound, bool do_loop){
   if(do_loop)
      alSourcei(sound, AL_LOOPING,  AL_TRUE);
   else
      alSourcei(sound, AL_LOOPING,  AL_FALSE);
}

void Sounds::stop(ALuint sound){
   alSourceStop(sound);
}

// Float and Double can be used as substitute of ALfloat
void Sounds::set_listener_velocity(ALfloat x, ALfloat y, ALfloat z){
    ALfloat listener_velocity[] = {x, y, z};
    alListenerfv(AL_VELOCITY, listener_velocity);
}
void Sounds::set_listener_position(ALfloat x, ALfloat y, ALfloat z){
    ALfloat listener_position[] = {x, y, z};
    alListenerfv(AL_POSITION, listener_position);
}
void Sounds::set_listener_orientation(ALfloat x, ALfloat y, ALfloat z,
                              ALfloat x2, ALfloat y2, ALfloat z2){
    // position and up(focues)
    ALfloat listener_orientation[] = {x,  y,  z, x2, y2, z2};
    alListenerfv(AL_ORIENTATION, listener_orientation);
}

// sound as sound source
void Sounds::set_source_velocity(ALuint sound, ALfloat x, ALfloat y, ALfloat z){
    ALfloat listener_velocity[] = {x, y, z};
    alSourcefv(sound, AL_VELOCITY, listener_velocity);
}
void Sounds::set_source_position(ALuint sound, ALfloat x, ALfloat y, ALfloat z){
    ALfloat source_position[] = {x, y, z};
    alSourcefv(sound, AL_POSITION, source_position);  
}
