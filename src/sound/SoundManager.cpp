/*
 * Sound Manager
 *
 * Copyright (c) 2015 by Can Firat Gocmen
 * 
 */

/* Sound Manager object provides processes of loading and playing RIFF Wave
/* files (PCM 8-16 BIT) */

#include <stdio.h>
#include <stdlib.h>  

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include "SoundManager.h"

SoundManager::SoundManager(int number_of_sounds) {	
   this->number_of_sounds = number_of_sounds;
   sound_buffers = (ALuint*) malloc(number_of_sounds);
   sound_sources = (ALuint*) malloc(number_of_sounds);

   current_sound=0;

   current_context = alcGetCurrentContext();   
   current_device = alcGetContextsDevice(current_context);

/*                  ALUT Version                  */     

/*    int error = alGetError();
      if (error)
         printf("%s\n", alutGetErrorString(error)); */
}

SoundManager::~SoundManager(){
   alcMakeContextCurrent(NULL);

   alcDestroyContext(current_context);
   alcCloseDevice(current_device); 

   alDeleteSources(number_of_sounds, sound_sources);
   alDeleteBuffers(number_of_sounds, sound_buffers);
}

int SoundManager::load(char* sound_name){
   current_sound++;

/*                  ALUT Version                  */     

/* sound_buffers[current_sound] = alutCreateBufferFromFile(sound_name); */ 

   alGenSources(1, &sound_sources[current_sound]);
   alSourcei(sound_sources[current_sound], AL_BUFFER, 
             sound_buffers[current_sound]);

   ALenum error = alGetError();
   if(error != AL_NO_ERROR){ 
       printf("%s\n", alcGetString(current_device,error));
   }   

   return sound_sources[current_sound];
}

void SoundManager::play(ALuint sound){
   alSourcePlay(sound);
}
