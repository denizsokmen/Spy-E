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

class Sounds : public System {
   private:

      struct sound{
         std::string name;
         ALuint buffer;
         ALuint source;
      };

      //sound *sounds;
      std::vector<sound> sounds;

      /* ALuint *sound_buffers;
         ALuint *sound_sources; */

      ALCdevice *current_device;
      ALCcontext *current_context;

      int load(const std::string name, const std::string file_name);
      int find_source_by_name(const std::string sound_name);

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

      int  open(const std::string file_name);
      int  open(const std::string sound_name, const std::string file_name);
      void play(ALuint sound);
      void play(const std::string sound_name);
      void loop(ALuint sound, bool do_loop);
      void stop(ALuint sound);
      //system.h
      void init(){}
      void update(float dt){}
      void draw(){}
      void draw2D(){}
};

#endif
