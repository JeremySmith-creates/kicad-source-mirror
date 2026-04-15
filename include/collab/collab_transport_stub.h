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

#ifndef COLLAB_TRANSPORT_STUB_H
#define COLLAB_TRANSPORT_STUB_H

#include <collab/collab_transport.h>


class KICOMMON_API COLLAB_TRANSPORT_STUB : public COLLAB_TRANSPORT
{
public:
    bool Connect( const COLLAB_SESSION_SETTINGS& aSettings, const wxString& aAccessToken,
                  wxString& aError ) override;

    void Disconnect() override;

    bool Send( const wxString& aPayload, wxString& aError ) override;

    void SetMessageHandler( COLLAB_MESSAGE_HANDLER aHandler ) override;

private:
    bool                   m_connected = false;
    COLLAB_MESSAGE_HANDLER m_handler;
};

#endif // COLLAB_TRANSPORT_STUB_H
