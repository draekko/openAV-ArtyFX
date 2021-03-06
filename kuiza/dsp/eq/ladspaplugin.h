/*
    Copyright (C) 2003 Fons Adriaensen
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/


#ifndef __LADSPAPLUGIN_H
#define __LADSPAPLUGIN_H


#include "ladspa.h" // use local version



class LadspaPlugin
{
public:

  LadspaPlugin (unsigned long fsam) : _gain (1.0), _fsam (fsam) {}

  virtual void setport (unsigned long port, LADSPA_Data *data) = 0;  
  virtual void active  (bool act) = 0;  
  virtual void runproc (unsigned long len, bool add) = 0;  
  virtual ~LadspaPlugin (void) {}

  void setgain (LADSPA_Data gain) { _gain = gain; }

protected:

  float _gain;
  float _fsam;
};



#endif
