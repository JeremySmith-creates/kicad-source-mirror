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

#include <collab/collab_session_manager.h>

#include <utility>


COLLAB_SESSION_MANAGER::COLLAB_SESSION_MANAGER( std::unique_ptr<COLLAB_AUTH_PROVIDER> aAuth,
                                                std::unique_ptr<COLLAB_TRANSPORT> aTransport ) :
        m_auth( std::move( aAuth ) ),
        m_transport( std::move( aTransport ) ),
        m_state( COLLAB_CONNECTION_STATE::IDLE )
{
}


bool COLLAB_SESSION_MANAGER::Connect( const COLLAB_SESSION_SETTINGS& aSettings, wxString& aError )
{
    if( !m_auth || !m_transport )
    {
        aError = wxS( "Collaboration stack is not initialized" );
        m_state = COLLAB_CONNECTION_STATE::ERROR;
        return false;
    }

    m_state = COLLAB_CONNECTION_STATE::JOINING;

    COLLAB_AUTH_RESULT auth = m_auth->Authenticate( aSettings );

    if( !auth.ok )
    {
        aError = auth.error;
        m_state = COLLAB_CONNECTION_STATE::ERROR;
        return false;
    }

    if( !m_transport->Connect( aSettings, auth.accessToken, aError ) )
    {
        m_state = COLLAB_CONNECTION_STATE::ERROR;
        return false;
    }

    m_state = COLLAB_CONNECTION_STATE::CONNECTED;
    return true;
}


void COLLAB_SESSION_MANAGER::Disconnect()
{
    if( m_transport )
        m_transport->Disconnect();

    m_state = COLLAB_CONNECTION_STATE::IDLE;
}


COLLAB_CONNECTION_STATE COLLAB_SESSION_MANAGER::GetConnectionState() const
{
    return m_state;
}
