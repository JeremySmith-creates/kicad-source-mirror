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

#ifndef COLLAB_PASSWORD_AUTH_PROVIDER_H
#define COLLAB_PASSWORD_AUTH_PROVIDER_H

#include <collab/collab_auth_provider.h>


class KICOMMON_API COLLAB_PASSWORD_AUTH_PROVIDER : public COLLAB_AUTH_PROVIDER
{
public:
    COLLAB_AUTH_RESULT Authenticate( const COLLAB_SESSION_SETTINGS& aSettings ) override;
};

#endif // COLLAB_PASSWORD_AUTH_PROVIDER_H
