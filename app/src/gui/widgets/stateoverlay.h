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

#ifndef SYNKEVO_STATEOVERLAY_H
#define SYNKEVO_STATEOVERLAY_H

#include "ui_stateoverlay.h"

#include <QPointer>
#include <QWidget>

namespace Synkevo {

    /**
     * State overlay inspired by the Akonadi config error overlay.
     */
    class StateOverlay : public QWidget, private Ui::StateOverlay
    {
        Q_OBJECT

    public:
        enum State {
            NotRunning = 1,
            Broken,
            Busy
        };

        explicit StateOverlay(QWidget *baseWidget, QWidget *parent = 0);
        ~StateOverlay();

        State state() const { return m_state; }
        bool isActive() const { return m_isActive; }

    public slots:
        void setState(State);
        void setActive(bool);

    protected:
        bool eventFilter(QObject *object, QEvent *event);

    private slots:
        void updateOverlay();
        void on_startButton_clicked();
        void on_detailsButton_clicked();

    private:
        QPointer<QWidget> m_baseWidget;
        State m_state;
        bool m_isBaseEnabled;
        bool m_isActive;
    };

} // End of namespace Synkevo

#endif
