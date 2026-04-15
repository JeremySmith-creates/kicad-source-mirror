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

#include <collab/collab_transport_stub.h>

#include <utility>


bool COLLAB_TRANSPORT_STUB::Connect( const COLLAB_SESSION_SETTINGS& aSettings,
                                     const wxString& aAccessToken, wxString& aError )
{
    if( aSettings.hostUrl.IsEmpty() || aSettings.roomId.IsEmpty() )
    {
        aError = wxS( "Missing host URL or room ID" );
        return false;
    }

    if( aAccessToken.IsEmpty() )
    {
        aError = wxS( "Missing collaboration access token" );
        return false;
    }

    m_connected = true;
    return true;
}


void COLLAB_TRANSPORT_STUB::Disconnect()
{
    m_connected = false;
}


bool COLLAB_TRANSPORT_STUB::Send( const wxString& aPayload, wxString& aError )
{
    if( !m_connected )
    {
        aError = wxS( "Not connected" );
        return false;
    }

    if( aPayload.IsEmpty() )
    {
        aError = wxS( "Cannot send empty collaboration payload" );
        return false;
    }

    return true;
}


void COLLAB_TRANSPORT_STUB::SetMessageHandler( COLLAB_MESSAGE_HANDLER aHandler )
{
    m_handler = std::move( aHandler );
}
