/*
    Copyright 2008 Sascha Peilicke <sasch.pe@gmx.de>

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

#include "gui/mainwindow.h"

#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocale>
#include <KApplication>

namespace Synkevo { /* This is only a Doxygen stub */ }

int main(int argc, char *argv[])
{
    KAboutData aboutData("synkevo", 0, ki18n("Synckevo"), "0.0.1",
            ki18n("KDE SyncEvolution"), KAboutData::License_GPL_V3,
            ki18n("Copyright (c) 2010 Sascha Peilicke"));
    aboutData.addAuthor(ki18n("Sascha Peilicke (saschpe)"), ki18n("Original author"),
                        "sasch.pe@gmx.de", "http://saschpe.wordpress.com");
    KCmdLineArgs::init(argc, argv, &aboutData);

    KApplication app;
    //KGlobal::locale()->insertCatalog("foo");

    if (app.isSessionRestored()) {
        RESTORE(Synkevo::MainWindow)
    } else {
        Synkevo::MainWindow *mainWin = new Synkevo::MainWindow(NULL);
        mainWin->show();
    }
    return app.exec();
}
