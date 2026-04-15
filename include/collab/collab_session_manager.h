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

#ifndef COLLAB_SESSION_MANAGER_H
#define COLLAB_SESSION_MANAGER_H

#include <memory>

#include <collab/collab_auth_provider.h>
#include <collab/collab_transport.h>


class KICOMMON_API COLLAB_SESSION_MANAGER
{
public:
    COLLAB_SESSION_MANAGER( std::unique_ptr<COLLAB_AUTH_PROVIDER> aAuth,
                            std::unique_ptr<COLLAB_TRANSPORT> aTransport );

    bool Connect( const COLLAB_SESSION_SETTINGS& aSettings, wxString& aError );
    void Disconnect();

    COLLAB_CONNECTION_STATE GetConnectionState() const;

private:
    std::unique_ptr<COLLAB_AUTH_PROVIDER> m_auth;
    std::unique_ptr<COLLAB_TRANSPORT>     m_transport;
    COLLAB_CONNECTION_STATE               m_state;
};

#endif // COLLAB_SESSION_MANAGER_H
