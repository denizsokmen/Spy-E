/*
 * Sound Manager
 *
 * Copyright (c) 2015 by Can Firat Gocmen 
 *
 */

/* Header file for Sound Manager class */

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <AL/al.h>
#include <AL/alc.h>

class SoundManager{
   private:
      ALuint *sound_buffers;
      ALuint *sound_sources;

      int number_of_sounds;
      int current_sound;

      ALCdevice *current_device;
      ALCcontext *current_context; 

   public:   
      SoundManager(int number_of_sounds);
      ~SoundManager();

      int load(char* sound_name);
      void play(ALuint sound);
};

#endif
