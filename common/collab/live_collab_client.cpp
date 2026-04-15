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

#include <collab/live_collab_client.h>

#include <utility>


LIVE_COLLAB_CLIENT::LIVE_COLLAB_CLIENT() = default;


void LIVE_COLLAB_CLIENT::Configure( const LIVE_COLLAB_CONNECTION_CONFIG& aConfig )
{
    m_config = aConfig;
}


bool LIVE_COLLAB_CLIENT::StartHosting( wxString& aError )
{
    setState( LIVE_COLLAB_SESSION_STATE::HOSTING, wxString() );

    aError = wxS( "Live collaboration transport is not wired yet (M1 scaffolding)." );
    setState( LIVE_COLLAB_SESSION_STATE::DEGRADED, aError );
    return false;
}


bool LIVE_COLLAB_CLIENT::JoinRoom( wxString& aError )
{
    setState( LIVE_COLLAB_SESSION_STATE::JOINING, wxString() );

    aError = wxS( "Live collaboration transport is not wired yet (M1 scaffolding)." );
    setState( LIVE_COLLAB_SESSION_STATE::DEGRADED, aError );
    return false;
}


void LIVE_COLLAB_CLIENT::Disconnect()
{
    setState( LIVE_COLLAB_SESSION_STATE::IDLE, wxString() );
}


void LIVE_COLLAB_CLIENT::SetStateCallback( LIVE_COLLAB_STATE_CALLBACK aCallback )
{
    m_stateCallback = std::move( aCallback );
}


LIVE_COLLAB_SESSION_STATE LIVE_COLLAB_CLIENT::GetState() const
{
    return m_state;
}


const LIVE_COLLAB_CONNECTION_CONFIG& LIVE_COLLAB_CLIENT::GetConfig() const
{
    return m_config;
}


void LIVE_COLLAB_CLIENT::setState( LIVE_COLLAB_SESSION_STATE aState, const wxString& aReason )
{
    m_state = aState;

    if( m_stateCallback )
        m_stateCallback( aState, aReason );
}
