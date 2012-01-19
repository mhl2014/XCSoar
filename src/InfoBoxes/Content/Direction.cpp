/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000-2012 The XCSoar Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

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

#include "InfoBoxes/Content/Direction.hpp"
#include "InfoBoxes/Data.hpp"
#include "Interface.hpp"

#include "Simulator.hpp"
#include "DeviceBlackboard.hpp"
#include "Components.hpp"

#include <tchar.h>
#include <stdio.h>

void
InfoBoxContentTrack::Update(InfoBoxData &data)
{
  if (!XCSoarInterface::Basic().track_available) {
    data.SetInvalid();
    return;
  }
  data.SetValue(XCSoarInterface::Basic().track);
}

bool
InfoBoxContentTrack::HandleKey(const InfoBoxKeyCodes keycode)
{
  if (!is_simulator())
    return false;
  if (!XCSoarInterface::Basic().gps.simulator)
    return false;

  const Angle a5 = Angle::Degrees(fixed(5));
  switch (keycode) {
  case ibkUp:
  case ibkRight:
    device_blackboard->SetTrack(
        XCSoarInterface::Basic().track + a5);
    return true;

  case ibkDown:
  case ibkLeft:
    device_blackboard->SetTrack(
        XCSoarInterface::Basic().track - a5);
    return true;

  case ibkEnter:
    break;
  }

  return false;
}
