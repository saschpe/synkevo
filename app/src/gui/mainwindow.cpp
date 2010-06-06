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

#include "mainwindow.h"
#include "config/generalconfig.h"
#include "widgets/profilewidget.h"
#include "widgets/stateoverlay.h"
#include "preferences.h"

#include <KAction>
#include <KActionCollection>
#include <KConfigDialog>
#include <KDebug>

#include <QDockWidget>
#include <QStandardItemModel>
#include <QTableView>

namespace Synkevo {

    MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
        : KXmlGuiWindow(parent, flags)
        , m_model(new QStandardItemModel(this)), m_view(new QTableView(this))
        , m_stateOverlay(new StateOverlay(m_view, this))
    {
        setCentralWidget(m_view);

        setupActions();
        setupDockWidgets();
        setupGUI();

        initBackend();
    }

    void MainWindow::showPreferences()
    {
        if (KConfigDialog::showDialog("settings")) {
            return;
        }

        KConfigDialog *dialog = new KConfigDialog(this, "settings", Preferences::self());
        dialog->addPage(new GeneralConfig(), i18n("General"), "preferences-other");
        dialog->setHelp(QString(), "Synkevo");
        dialog->show();
    }

    void MainWindow::initBackend()
    {
        m_server = new org::syncevolution::Server("org.syncevolution",
                                                  "/org/syncevolution/Server",
                                                  QDBusConnection::sessionBus(),
                                                  this);
        m_stateOverlay->setActive(!m_server);
        m_stateOverlay->setState(StateOverlay::NotRunning);
    }

    void MainWindow::setupActions()
    {
        // File menu
        KStandardAction::quit(this, SLOT(close()), actionCollection());

        // Edit menu
        m_addProfileAction = new KAction(KIcon(QLatin1String("list-add")), i18nc("@action", "&Add Profile..."), this);
        m_addProfileAction->setShortcut(Qt::CTRL + Qt::Key_A);
        m_addProfileAction->setToolTip(i18nc("@action", "Add Sync Partner Profile"));
        actionCollection()->addAction("add_profile", m_addProfileAction);

        m_removeProfileAction = new KAction(KIcon(QLatin1String("list-remove")), i18nc("@action", "&Remove Profile"), this);
        m_removeProfileAction->setShortcut(Qt::CTRL + Qt::Key_R);
        m_removeProfileAction->setToolTip(i18nc("@action", "Remove Sync Partner Profile"));
        m_removeProfileAction->setEnabled(false);
        actionCollection()->addAction("remove_profile", m_removeProfileAction);

        m_configureProfileAction = new KAction(KIcon(QLatin1String("configure")), i18nc("@action", "&Configure Profile..."), this);
        m_configureProfileAction->setShortcut(Qt::CTRL + Qt::Key_C);
        m_configureProfileAction->setToolTip(i18nc("@action", "Configure Selected Profile..."));
        m_configureProfileAction->setEnabled(false);
        actionCollection()->addAction("configure_profile", m_configureProfileAction);

        m_startStopSyncAction = new KAction(KIcon(QLatin1String("media-playback-start")), i18nc("@action", "Start Sync"), this);
        m_startStopSyncAction->setShortcut(Qt::CTRL + Qt::Key_S);
        m_startStopSyncAction->setToolTip(i18nc("@action", "Start Sync With Current Partner"));
        m_startStopSyncAction->setEnabled(false);
        actionCollection()->addAction("start_stop_sync", m_startStopSyncAction);

        // Settings menu
        KStandardAction::preferences(this, SLOT(showPreferences()), actionCollection());
    }

    void MainWindow::setupDockWidgets()
    {
        // Setup profile dock
        QDockWidget *profileDock = new QDockWidget(i18nc("@title:window", "Profiles"), this);
        profileDock->setObjectName("profileDock");
        QWidget *profileWidget = new ProfileWidget(m_view, this);
        profileDock->setWidget(profileWidget);
        //TODO: Connect signals/slots
        /*connect(profileWidget, SIGNAL(addClicked()), this, SLOT(startGame()));*/
        profileDock->toggleViewAction()->setText(i18nc("@title:window", "&Profile Dock"));
        profileDock->toggleViewAction()->setShortcut(Qt::Key_P);
        actionCollection()->addAction("show_profile_dock", profileDock->toggleViewAction());
        addDockWidget(Qt::RightDockWidgetArea, profileDock);
    }

} // End of namespace Synkevo

#include "moc_mainwindow.cpp"
