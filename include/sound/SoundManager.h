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

#include <vector>

#define S_NAME_CHAR_LIM 200

class SoundManager{
   private:

      struct sound{
         char  name[200];
         ALuint buffer;
         ALuint source;
      };

      //sound *sounds;
      std::vector<sound> sounds;

      /* ALuint *sound_buffers;
         ALuint *sound_sources; */

      int number_of_sounds;
      int current_sound;

      ALCdevice *current_device;
      ALCcontext *current_context;

      int load(const char* name, const char* file_name);
      int find_source_by_name(const char* sound_name);

#pragma pack(push,1)

      struct RIFF_Wave_file{
         char RIFF_t[4];            // 'RIFF'
         unsigned int size;     
         char WAVE_t[4];            // 'WAVE'
         char fmt_t[4];             // 'fmt ' 
         unsigned int chunk_size; 
         short format_type;
         short channels; 
         unsigned int sample_rate;
         unsigned int average_bytes_per_second; 
         short bytes_per_sample;
         short bits_per_sample; 
         char data_t[4];            // 'data'   
         unsigned int data_size; 
      };

#pragma pack(pop)

   public:   
      SoundManager();
      ~SoundManager();

      int  open(const char* file_name);
      int  open(const char* sound_name, const char* file_name);
      void play(ALuint sound);
      void play(const char* sound_name);
      void loop(ALuint sound, bool do_loop);
      void stop(ALuint sound);
};

#endif
