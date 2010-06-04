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
#include "widgets/profilelistwidget.h"
#include "preferences.h"

#include <KAction>
#include <KActionCollection>
#include <KConfigDialog>
#include <KStandardDirs>

namespace Synkevo {

    MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
        : KXmlGuiWindow(parent, flags)
        , m_profileListWidget(new ProfileListWidget(this))
    {
        setCentralWidget(m_profileListWidget);

        setupActions();
        setupDockWindows();
        setupGUI(QSize(640, 480), KXmlGuiWindow::ToolBar | KXmlGuiWindow::Keys |
                                  KXmlGuiWindow::Save | KXmlGuiWindow::Create);
    }

    void MainWindow::showPreferences()
    {
        if (KConfigDialog::showDialog("settings"))
            return;

        KConfigDialog *dialog = new KConfigDialog(this, "settings", Preferences::self());
        dialog->addPage(new GeneralConfig(), i18n("General"), "preferences-other");
        dialog->setHelp(QString(), "Synkevo");
        dialog->show();
    }

    void MainWindow::setupActions()
    {
        // File menu
        KStandardAction::quit(this, SLOT(close()), actionCollection());

        // Edit menu


        // Settings menu
        KStandardAction::preferences(this, SLOT(showPreferences()), actionCollection());
    }

    void MainWindow::setupDockWindows()
    {
    }

} // End of namespace Synkevo

#include "moc_mainwindow.cpp"
