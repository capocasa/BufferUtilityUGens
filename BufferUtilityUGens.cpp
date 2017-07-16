/*
    BufferUtilityUGens
    Copyright (c) 2016-2017 Carlo Capocasa. All rights reserved.
    https://capocasa.net

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
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include "SC_PlugIn.hpp"

static InterfaceTable *ft;

struct SetBufferRate : public Unit
{
  float m_fbufnum;
  SndBuf *m_buf;
  float m_prevtrig;
};

static void SetBufferRate_next_k(SetBufferRate* unit, int inNumSamples);
static void SetBufferRate_Ctor(SetBufferRate* unit);

void SetBufferRate_Ctor(SetBufferRate* unit)
{
  SETCALC(SetBufferRate_next_k);
  unit->m_fbufnum = -1e9f;
  SetBufferRate_next_k(unit, 1);
}
void SetBufferRate_next_k(SetBufferRate *unit, int inNumSamples)
{
  float trig = IN0(1);

  if (trig > 0.f && unit->m_prevtrig <= 0.f) {
    SIMPLE_GET_BUF
    float samplerate = IN0(2);
    SndBuf* buf2 = unit->mWorld->mSndBufsNonRealTimeMirror + (int)unit->m_fbufnum;
    unit->m_buf->samplerate = samplerate;
    buf2->samplerate = samplerate;
    //printf("SR %f %f\n", unit->m_buf->samplerate, buf2->samplerate);
  }

  unit->m_prevtrig = trig;
}

PluginLoad(BufferUtility)
{
  DefineSimpleUnit(SetBufferRate);
}

