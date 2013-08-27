
#include "masha.hxx"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dsp_masher.hxx"

class Masha
{
  public:
    Masha(int rate);
    ~Masha(){}
    static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                                  double samplerate,
                                  const char* bundle_path,
                                  const LV2_Feature* const* features);
    static void activate(LV2_Handle instance);
    static void deactivate(LV2_Handle instance);
    static void connect_port(LV2_Handle instance, uint32_t port, void *data);
    static void run(LV2_Handle instance, uint32_t n_samples);
    static void cleanup(LV2_Handle instance);
    static const void* extension_data(const char* uri);
    
    /// audio buffers
    float* audioInputL;
    float* audioInputR;
    float* audioOutputL;
    float* audioOutputR;
    
    /// control signals
    float* controlTime;
    float* controlDamping;
    float* controlDryWet;
    
  private:
    Masher dspMasher;
};


static const LV2_Descriptor descriptor =
{
  MASHA_URI,
  Masha::instantiate,
  Masha::connect_port,
  Masha::activate,
  Masha::run,
  Masha::deactivate,
  Masha::cleanup,
  Masha::extension_data
};


LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
  if (index == 0) return &descriptor;
  else return NULL;
}


LV2_Handle Masha::instantiate(const LV2_Descriptor* descriptor,
                              double samplerate,
                              const char* bundle_path,
                              const LV2_Feature* const* features)
{
  return (LV2_Handle) new Masha( samplerate );
}

Masha::Masha(int rate) :
  dspMasher( rate )
{
}


void Masha::activate(LV2_Handle instance)
{
}

void Masha::deactivate(LV2_Handle instance)
{
}

void Masha::connect_port(LV2_Handle instance, uint32_t port, void *data)
{
  Masha* self = (Masha*) instance;
  
  switch (port)
  {
      case MASHA_INPUT_L:
          self->audioInputL    = (float*)data;
          break;
      case MASHA_INPUT_R:
          self->audioInputR    = (float*)data;
          break;
          break;
      case MASHA_OUTPUT_L:
          self->audioOutputL   = (float*)data;
          break;
      case MASHA_OUTPUT_R:
          self->audioOutputR   = (float*)data;
          break;
      
      case MASHA_TIME:
          self->controlTime    = (float*)data;
          break;
      case MASHA_DAMPING:
          self->controlDamping = (float*)data;
          break;
      
      case MASHA_DRY_WET:
          self->controlDryWet  = (float*)data;
          break;
  }
}

void Masha::run(LV2_Handle instance, uint32_t n_samples)
{
  Masha* self = (Masha*) instance;
  
  /// audio inputs
  float* inL  = self->audioInputL;
  float* inR  = self->audioInputR;
  float* outL = self->audioOutputL;
  float* outR = self->audioOutputR;
  
  float* buf[4] = {
    inL, inR,
    outL, outR
  };
  
  /// control inputs
  float time    = *self->controlTime;
  float damping = *self->controlDamping;
  float dryWet  = *self->controlDryWet;
  
  /*
  self->dspMasher.rt60    ( time    );
  self->dspMasher.damping ( damping );
  self->dspMasher.dryWet  ( dryWet  );
  
  self->dspMasher.process( n_samples, &buf[0], &buf[2] );
  */
}

void Masha::cleanup(LV2_Handle instance)
{
  delete ((Masha*) instance);
}

const void* Masha::extension_data(const char* uri)
{
    return NULL;
}