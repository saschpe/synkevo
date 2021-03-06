/*
    Copyright 2010 Sascha Peilicke <sasch.pe@gmx.de>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License or (at your option) version 3 or any later version
    accepted by the membership of KDE e.V. (or its successor approved
    by the membership of KDE e.V.), which shall act as a proxy
    defined in Section 14 of version 3 of the license.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "configwidget.h"

#include <KDebug>

namespace Synkevo {

    ConfigWidget::ConfigWidget(org::syncevolution::Server *server, QWidget *parent)
        : QWidget(parent), m_server(server)
    {
        Q_ASSERT(server);

        setupUi(this);

        // Query SyncEvolution service for available configs
        QDBusPendingReply<QStringList> reply = m_server->GetConfigs(true);
        if (reply.isValid()) {
            kDebug() << "SyncEvolution supports these configs:" << reply.value();
            serviceType->addItems(reply.value());
        } else {
            kDebug() << "SyncEvolution service error:" << reply.error();
            //TODO: Show error/ disable widget
        }

        //TODO: a lot
    }

} // End of namespace Synkevo

#include "moc_configwidget.cpp"

