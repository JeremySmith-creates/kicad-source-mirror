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

#ifndef LIVE_COLLAB_CLIENT_H
#define LIVE_COLLAB_CLIENT_H

#include <functional>
#include <vector>

#include <collab/live_collab_types.h>


using LIVE_COLLAB_STATE_CALLBACK = std::function<void( LIVE_COLLAB_SESSION_STATE, const wxString& )>;


class KICOMMON_API LIVE_COLLAB_CLIENT
{
public:
    LIVE_COLLAB_CLIENT();

    void Configure( const LIVE_COLLAB_CONNECTION_CONFIG& aConfig );

    bool StartHosting( wxString& aError );
    bool JoinRoom( wxString& aError );
    void Disconnect();

    void SetStateCallback( LIVE_COLLAB_STATE_CALLBACK aCallback );

    LIVE_COLLAB_SESSION_STATE GetState() const;
    const LIVE_COLLAB_CONNECTION_CONFIG& GetConfig() const;

private:
    void setState( LIVE_COLLAB_SESSION_STATE aState, const wxString& aReason );

private:
    LIVE_COLLAB_CONNECTION_CONFIG m_config;
    LIVE_COLLAB_SESSION_STATE     m_state = LIVE_COLLAB_SESSION_STATE::IDLE;
    LIVE_COLLAB_STATE_CALLBACK    m_stateCallback;
};

#endif // LIVE_COLLAB_CLIENT_H
