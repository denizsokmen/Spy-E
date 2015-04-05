/*
 * Sound Manager
 *
 * Copyright (c) 2015 by Can Firat Gocmen 
 *
 */

/* Header file for Sound Manager class */

#ifndef SOUNDS_H
#define SOUNDS_H

#include <AL/al.h>
#include <AL/alc.h>

#include <vector>
#include <logic/System.h>

#define S_NAME_CHAR_LIM 200

class Sounds : public System {
   private:

      struct sound{
         char  name[S_NAME_CHAR_LIM];
         ALuint buffer;
         ALuint source;
      };

      //sound *sounds;
      std::vector<sound> sounds;

      /* ALuint *sound_buffers;
         ALuint *sound_sources; */

      ALCdevice *current_device;
      ALCcontext *current_context;

      int load(char* name, char* file_name);
      int find_source_by_name(char* sound_name);

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
   Sounds();

   ~Sounds();

      int  open(char* file_name);
      int  open(char* sound_name, char* file_name);
      void play(ALuint sound);
      void play(char* sound_name);
      void loop(ALuint sound, bool do_loop);
      void stop(ALuint sound);

   void init() { }

   void update(float dt) { }

   void draw() { }

   void draw2D() { }
};

#endif
