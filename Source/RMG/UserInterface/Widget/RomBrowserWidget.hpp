/*
 * Rosalie's Mupen GUI - https://github.com/Rosalie241/RMG
 *  Copyright (C) 2020 Rosalie Wanders <rosalie@mailbox.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3.
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef ROMBROWSERWIDGET_HPP
#define ROMBROWSERWIDGET_HPP

#include "../../Globals.hpp"
#include "../../Thread/RomSearcherThread.hpp"
#include "../NoFocusDelegate.hpp"

#include <QHeaderView>
#include <QList>
#include <QStandardItemModel>
#include <QString>
#include <QTableView>
#include <QMenu>
#include <QAction>

#define MAX_ROM_INFO 50

namespace UserInterface
{
namespace Widget
{
class RomBrowserWidget : public QTableView
{
    Q_OBJECT

  public:
    RomBrowserWidget(QWidget *);
    ~RomBrowserWidget(void);

    void RefreshRomList(void);

    void SetDirectory(QString);

  private:
    QString directory;

    QMenu* contextMenu;
    QAction* action_PlayGame;
    QAction* action_PlayGameWithDisk;
    QAction* action_RefreshRomList;
    QAction* action_ChooseRomDirectory;
    QAction* action_RomInformation;
    QAction* action_EditGameSettings;
    QAction* action_EditCheats;

    void contextMenu_Init(void);
    void contextMenu_Setup(void);

    void contextMenu_Actions_Init(void);
    void contextMenu_Actions_Setup(void);
    void contextMenu_Actions_Connect(void);

    QStandardItemModel *model_Model;
    QStringList model_LabelList;
    void model_Init(void);
    void model_Setup(void);
    void model_LabelList_Setup(void);

    NoFocusDelegate *widget_Delegate;
    void widget_Init(void);

    Thread::RomSearcherThread *rom_Searcher_Thread;
    bool rom_Searcher_Recursive;
    bool rom_Searcher_MaxItems;
    bool rom_Searcher_Running;

    void rom_Searcher_Init(void);

    QList<M64P::Wrapper::RomInfo_t> rom_List;
    int rom_List_Index;

    bool rom_List_Recursive;
    bool rom_List_Fill_Thread_Running = false;
    void rom_List_Init();
    void rom_List_Fill(QString);

    void column_SetSize();

  protected:
    void dragMoveEvent(QDragMoveEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);

  private slots:
    void customContextMenuRequested(QPoint);

    void on_Action_PlayGame(void);
    void on_Action_PlayGameWithDisk(void);
    void on_Action_RefreshRomList(void);
    void on_Action_ChooseRomDirectory(void);
    void on_Action_RomInformation(void);
    void on_Action_EditGameSettings(void);
    void on_Action_EditCheats(void);

  public slots:
    void on_Row_DoubleClicked(const QModelIndex &);
    void on_RomBrowserThread_Received(M64P::Wrapper::RomInfo_t info);
    void on_RomBrowserThread_Finished(void);

  signals:
    void on_RomBrowser_Select(QString);
    void on_RomBrowser_FileDropped(QDropEvent *);
};
} // namespace Widget
} // namespace UserInterface

#endif // ROMBROWSERWIDGET_HPP
