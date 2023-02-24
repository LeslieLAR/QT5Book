#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QListWidgetItem>
#include <QMenu>
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void setActionsForButton();
    void createSelectionPopMenu();



private slots:
    void on_actListIni_triggered();

    void on_actListClear_triggered();

    void on_actListDelete_triggered();

    void on_actSelALL_triggered();

    void on_actSelNone_triggered();

    void on_actSelInvs_triggered();

    void on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);

    void on_listWidget_customContextMenuRequested(const QPoint& pos);

    void on_actListAppend_triggered();

    void on_actListInsert_triggered();

    void on_chkBoxListEditable_clicked(bool checked);

    void on_toolBox_currentChanged(int index);

private:
    Ui::MainWindow* ui;

};
#endif // MAINWINDOW_H
