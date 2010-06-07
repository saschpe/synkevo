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

#include "syncwidget.h"

namespace Synkevo {

    SyncWidget::SyncWidget(QAbstractItemView *model, QWidget *parent)
        : QWidget(parent), m_view(model)
    {
        setupUi(this);

        startStopButton->setIcon(KIcon(QLatin1String("media-playback-start")));
        //TODO: react on model changes and enable/disable sync button
        //TODO: changes combos
        connect(m_view->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(selectionChanged()));
    }

    void SyncWidget::on_startStopButton_clicked()
    {
        if (startStopButton->text() == i18n("Start Sync")) {
            profileOneComboBox->setEnabled(false);
            profileTwoComboBox->setEnabled(false);

            startStopButton->setText(i18n("Stop Sync"));
            startStopButton->setIcon(KIcon(QLatin1String("media-playback-stop")));
            emit startClicked();
        } else {
            profileOneComboBox->setEnabled(true);
            profileTwoComboBox->setEnabled(true);

            startStopButton->setText(i18n("Start Sync"));
            startStopButton->setIcon(KIcon(QLatin1String("media-playback-start")));
            emit stopClicked();
        }
    }

    void SyncWidget::selectionChanged()
    {

    }

} // End of namespace Synkevo

#include "moc_syncwidget.cpp"
