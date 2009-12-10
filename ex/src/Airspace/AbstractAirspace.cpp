/* Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009

	M Roberts (original release)
	Robin Birch <robinb@ruffnready.co.uk>
	Samuel Gisiger <samuel.gisiger@triadis.ch>
	Jeff Goodenough <jeff@enborne.f2s.com>
	Alastair Harrison <aharrison@magic.force9.co.uk>
	Scott Penrose <scottp@dd.com.au>
	John Wharington <jwharington@gmail.com>
	Lars H <lars_hn@hotmail.com>
	Rob Dunning <rob@raspberryridgesheepfarm.com>
	Russell King <rmk@arm.linux.org.uk>
	Paolo Ventafridda <coolwind@email.it>
	Tobias Lohner <tobias@lohner-net.de>
	Mirek Jezek <mjezek@ipplc.cz>
	Max Kellermann <max@duempel.org>
	Tobias Bieniek <tobias.bieniek@gmx.de>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/
#include "AbstractAirspace.hpp"

void 
AbstractAirspace::set_ground_level(const fixed alt) 
{
  m_base.set_ground_level(alt);
  m_top.set_ground_level(alt);
}


void 
AbstractAirspace::set_flight_level(const AtmosphericPressure &press) 
{
  m_base.set_flight_level(press);
  m_top.set_flight_level(press);
}


bool 
AbstractAirspace::intercept_vertical(const AIRCRAFT_STATE &state,
                                     const GEOPOINT& loc,
                                     const AirspaceAircraftPerformance& perf,
                                     fixed &time_to_intercept,
                                     fixed &intercept_height) const
{
  const fixed distance = state.Location.distance(loc);
  const fixed t_this = perf.solution_vertical(distance, state.Altitude,
                                              m_base.Altitude, m_top.Altitude,
                                              intercept_height);
  
  if (!negative(t_this) && (t_this<=time_to_intercept)) {
    time_to_intercept = t_this;
    return true;
  }
  return false;
}


/*
  NewCircle->Ack.AcknowledgedToday = false;
  NewCircle->Ack.AcknowledgementTime = 0;
  NewCircle->_NewWarnAckNoBrush = false;
*/
