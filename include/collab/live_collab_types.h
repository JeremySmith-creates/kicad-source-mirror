/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright The KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIVE_COLLAB_TYPES_H
#define LIVE_COLLAB_TYPES_H

#include <kicommon.h>
#include <wx/string.h>


enum class LIVE_COLLAB_SESSION_STATE
{
    IDLE,
    HOSTING,
    JOINING,
    CONNECTED,
    DEGRADED
};


struct KICOMMON_API LIVE_COLLAB_CONNECTION_CONFIG
{
    wxString host_url;
    wxString room_id;
    wxString display_name;
    wxString password;
};


struct KICOMMON_API LIVE_COLLAB_PARTICIPANT
{
    wxString participant_id;
    wxString display_name;
    bool     is_host = false;
};

#endif // LIVE_COLLAB_TYPES_H
