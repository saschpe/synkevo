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

#include "profilewidget.h"

namespace Synkevo {

    ProfileWidget::ProfileWidget(QAbstractItemView *view, QWidget *parent)
        : QWidget(parent), m_view(view)
    {
        setupUi(this);

        addButton->setIcon(KIcon(QLatin1String("list-add")));
        removeButton->setIcon(KIcon(QLatin1String("list-remove")));
        configureButton->setIcon(KIcon(QLatin1String("configure")));
        startStopButton->setIcon(KIcon(QLatin1String("media-playback-start")));
    }

    void ProfileWidget::on_addButton_clicked()
    {
        emit addClicked();
    }

    void ProfileWidget::on_removeButton_clicked()
    {
        emit removeClicked();
    }

    void ProfileWidget::on_configureButton_clicked()
    {
        emit configureClicked();
    }

    void ProfileWidget::on_startStopButton_clicked()
    {
        if (startStopButton->text() == i18n("Start Sync")) {
            addButton->setEnabled(false);
            removeButton->setEnabled(false);
            configureButton->setEnabled(false);

            startStopButton->setText(i18n("Stop Sync"));
            startStopButton->setIcon(KIcon(QLatin1String("media-playback-stop")));
            emit startClicked();
        } else {
            addButton->setEnabled(true);
            //TODO: Check what to enable here
            removeButton->setEnabled(true);
            configureButton->setEnabled(true);

            startStopButton->setText(i18n("Start Sync"));
            startStopButton->setIcon(KIcon(QLatin1String("media-playback-start")));
            emit stopClicked();
        }
    }

} // End of namespace Synkevo

#include "moc_profilewidget.cpp"
