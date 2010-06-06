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

#include "stateoverlay.h"
#include "preferences.h"

#include <KDebug>
#include <KListWidget>
#include <KPushButton>

namespace Synkevo {

    StateOverlay::StateOverlay(QWidget *baseWidget, QWidget *parent)
        : QWidget(parent ? parent : baseWidget->window())
        , m_baseWidget(baseWidget)
        , m_isBaseEnabled(baseWidget->isEnabled()), m_isActive(false)
    {
        Q_ASSERT(baseWidget);

        setupUi(this);
        notRunningIcon->setPixmap(KIcon(QLatin1String("TODO")).pixmap(64));
        brokenIcon->setPixmap(KIcon(QLatin1String("dialog-error")).pixmap(64));
        progressIcon->setPixmap(KIcon(QLatin1String("TODO")).pixmap(32));

        connect(baseWidget, SIGNAL(destroyed()), this, SLOT(deleteLater()));

        // Set transparency
        QPalette p = palette();
        p.setColor(backgroundRole(), QColor(0, 0, 0, 128));
        p.setColor(foregroundRole(), Qt::white);
        setPalette(p);
        setAutoFillBackground(true);

        updateOverlay();
    }

    StateOverlay::~StateOverlay()
    {
        if (m_baseWidget) {
            m_baseWidget->setEnabled(m_isBaseEnabled);
        }
    }

    void StateOverlay::setState(State state)
    {
        switch (state) {
            case NotRunning:
                stackedWidget->setCurrentWidget(notRunningPage);
                break;
            case Broken:
                stackedWidget->setCurrentWidget(brokenPage);
                break;
            case Busy:
                stackedWidget->setCurrentWidget(progressPage);
                break;
        }
    }

    void StateOverlay::setActive(bool active)
    {
        m_isActive = active;
        updateOverlay();
    }

    bool StateOverlay::eventFilter(QObject *object, QEvent *event)
    {
        if (m_baseWidget && m_isActive &&
            (event->type() == QEvent::Move || event->type() == QEvent::Resize ||
             event->type() == QEvent::Show || event->type() == QEvent::Hide ||
             event->type() == QEvent::ParentChange)) {
            updateOverlay();
        }
        return QWidget::eventFilter(object, event);
    }

    void StateOverlay::updateOverlay()
    {
        if (!m_baseWidget) {
            return;
        }

        if (parentWidget() != m_baseWidget->window()) {
            setParent(m_baseWidget->window());
        }

        // Follow base widget visibility
        if (!m_baseWidget->isVisible()) {
            hide();
            return;
        }
        if (m_isActive) {
            show();
        }

        // Follow position changes
        const QPoint topLevelPos = m_baseWidget->mapTo(window(), QPoint(0, 0));
        const QPoint parentPos = parentWidget()->mapFrom(window(), topLevelPos);
        move(parentPos);

        // Folloe size changes
        resize(m_baseWidget->size());
    }

    void StateOverlay::on_startButton_clicked()
    {

    }

    void StateOverlay::on_detailsButton_clicked()
    {

    }

} // End of namespace Synkevo

#include "moc_stateoverlay.cpp"
