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

#ifndef SYNKEVO_MAINWINDOW_H
#define SYNKEVO_MAINWINDOW_H

#include <KXmlGuiWindow>

class KAction;
class KToggleAction;
class QDockWidget;

namespace Synkevo {

    /**
     * @author Sascha Peilicke <sasch.pe@gmx.de>
     * @since 0.0.1
     */
    class MainWindow : public KXmlGuiWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);

    private slots:
        void showPreferences();

    private:
        void setupActions();
        void setupDockWindows();

    };

} // End of namespace Synkevo

#endif