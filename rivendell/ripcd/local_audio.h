// local_audio.h
//
// A Rivendell switcher driver for local audio cards.
//
//   (C) Copyright 2002-2018 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public
//   License along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifndef LOCAL_AUDIO_H
#define LOCAL_AUDIO_H

#include <vector>

#include <qtimer.h>

#include <rd.h>
#include <rdmatrix.h>
#include <rdmacro.h>
#include <rdoneshot.h>
#include <rdtty.h>

#ifdef HPI
#include <asihpi/hpi.h>
#endif  // HPI

#include "switcher.h"

#define LOCALAUDIO_POLL_INTERVAL 100

class LocalAudio : public Switcher
{
 Q_OBJECT
 public:
  LocalAudio(RDMatrix *matrix,QObject *parent=0);
  ~LocalAudio();
  RDMatrix::Type type();
  unsigned gpiQuantity();
  unsigned gpoQuantity();
  bool primaryTtyActive();
  bool secondaryTtyActive();
  void processCommand(RDMacro *cmd);

 private slots:
  void pollData();
  void gpoOneshotData(int value);

 private:
  void InitializeHpi(RDMatrix *matrix);
  void SetGpo(int line,bool state);
  void UpdateDb(RDMatrix *matrix) const;
#ifdef HPI
  hpi_err_t LogHpi(hpi_err_t err,int lineno);
  hpi_handle_t bt_mixer;
  hpi_handle_t bt_gpis_param;
  hpi_handle_t bt_gpos_param;
  std::vector<uint8_t> bt_gpi_states;
#endif  // HPI
  RDOneShot *bt_gpo_oneshot;
  uint8_t *bt_gpi_values;
  uint8_t *bt_gpo_values;
  QTimer *bt_poll_timer;
  int bt_inputs;
  int bt_outputs;
  int bt_gpis;
  int bt_gpos;
  int bt_card;
};


#endif  // LOCAL_AUDIO_H
