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
#include "widgets/configwidget.h"
#include "widgets/profilewidget.h"
#include "widgets/stateoverlay.h"
#include "widgets/syncwidget.h"
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
        setupGUI(QSize(640, 480));

        m_view->setAlternatingRowColors(true);
        m_view->setIconSize(QSize(64, 64));
        m_view->setModel(m_model);
        m_view->setSelectionBehavior(QAbstractItemView::SelectItems);
        m_view->setSelectionMode(QAbstractItemView::SingleSelection);
        m_view->setSortingEnabled(true);
        connect(m_view->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(selectionChanged()));

        m_server = new org::syncevolution::Server("org.syncevolution",
                                                  "/org/syncevolution/Server",
                                                  QDBusConnection::sessionBus(),
                                                  this);
    }

    void MainWindow::addProfile()
    {
        kDebug();
        QStandardItem *item = new QStandardItem(QString("My Profile"));
        m_model->appendRow(item);
        m_view->setCurrentIndex(m_model->indexFromItem(item));
        configureProfile();
    }

    void MainWindow::removeProfile()
    {
        kDebug();

    }

    void MainWindow::configureProfile()
    {
        kDebug();
        ConfigWidget *configWidget = new ConfigWidget(this);

        KDialog *dialog = new KDialog(this);
        dialog->setCaption(i18n("Configure Profile"));
        dialog->setButtons(KDialog::Default | KDialog::Ok | KDialog::Cancel | KDialog::Apply);
        dialog->setMainWidget(configWidget);
        dialog->show();
    }

    void MainWindow::startSync()
    {
        kDebug();
    }

    void MainWindow::stopSync()
    {
        kDebug();
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

    void MainWindow::selectionChanged()
    {
        if (m_view->selectionModel()->hasSelection()) {
            slotStateChanged("has_selection");
        } else {
            slotStateChanged("has_no_selection");
        }
    }

    /*void MainWindow::getBackendConfigs()
    {

        QDBusPendingReply<QStringList> reply = m_server->GetConfigs(true);
        if (reply.isValid()) {
            kDebug() << "SyncEvolution supports these configs:" << reply.value();
            slotStateChanged("has_no_selection");
        } else {
            kDebug() << "SyncEvolution service error:" << reply.error();
            slotStateChanged("backend_not_running");
            m_stateOverlay->setState(StateOverlay::NotRunning);
            m_stateOverlay->setActive(true);
        }
    }*/

    void MainWindow::setupActions()
    {
        // File menu
        KStandardAction::quit(this, SLOT(close()), actionCollection());

        // Edit menu
        KAction *action = new KAction(KIcon(QLatin1String("list-add")), i18nc("@action", "&Add Profile..."), this);
        action->setShortcut(Qt::CTRL + Qt::Key_A);
        action->setToolTip(i18nc("@action", "Add Service or Device Profile"));
        actionCollection()->addAction("add_profile", action);
        connect(action, SIGNAL(triggered()), this, SLOT(addProfile()));

        action = new KAction(KIcon(QLatin1String("list-remove")), i18nc("@action", "&Remove Profile"), this);
        action->setShortcut(Qt::CTRL + Qt::Key_R);
        action->setToolTip(i18nc("@action", "Remove Service or Device Profile"));
        action->setEnabled(false);
        actionCollection()->addAction("remove_profile", action);
        connect(action, SIGNAL(triggered()), this, SLOT(removeProfile()));

        action = new KAction(KIcon(QLatin1String("configure")), i18nc("@action", "&Configure Profile..."), this);
        action->setShortcut(Qt::CTRL + Qt::Key_C);
        action->setToolTip(i18nc("@action", "Configure Selected Service or Device Profile..."));
        action->setEnabled(false);
        actionCollection()->addAction("configure_profile", action);
        connect(action, SIGNAL(triggered()), this, SLOT(configureProfile()));

        /*action = new KAction(KIcon(QLatin1String("media-playback-start")), i18nc("@action", "Start Sync"), this);
        action->setShortcut(Qt::CTRL + Qt::Key_S);
        action->setToolTip(i18nc("@action", "Sync With Current Service or Device"));
        action->setEnabled(false);
        actionCollection()->addAction("start_stop_sync", action);
        connect(action, SIGNAL(triggered()), this, SLOT(startStopSync()));*/

        // Settings menu
        KStandardAction::preferences(this, SLOT(showPreferences()), actionCollection());
    }

    void MainWindow::setupDockWidgets()
    {
        QWidget *syncWidget = new SyncWidget(m_view, this);
        syncWidget->setObjectName("sync_widget");
        connect(syncWidget, SIGNAL(startClicked()), this, SLOT(startSync()));
        connect(syncWidget, SIGNAL(stopClicked()), this, SLOT(stopSync()));

        QDockWidget *syncDock = new QDockWidget(i18nc("@title:window", "Sync"), this);
        syncDock->setObjectName("sync_dock");
        syncDock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
        syncDock->setFeatures(QDockWidget::DockWidgetMovable);
        syncDock->setWidget(syncWidget);
        syncDock->toggleViewAction()->setText(i18nc("@title:window", "&Sync Dock"));
        syncDock->toggleViewAction()->setShortcut(Qt::Key_P);
        actionCollection()->addAction("show_sync_dock", syncDock->toggleViewAction());
        addDockWidget(Qt::BottomDockWidgetArea, syncDock);
    }

} // End of namespace Synkevo

#include "moc_mainwindow.cpp"
