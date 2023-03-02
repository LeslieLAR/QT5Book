#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtGlobal>
#include<QTreeWidget>
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


private slots:
    void on_init_ListWidget_clicked();

    void on_insert_ListWidget_clicked();

    void on_add_ListWidget_clicked();

    void on_delete_ListWidget_clicked();

    void on_init_TableWidget_clicked();

    void on_insert_TableWidget_clicked();

    void on_add_TableWidget_clicked();

    void on_delete_TableWidget_clicked();

    void on_init_treeWidget_clicked();

    void on_insert_treeWidget_clicked();

    void on_delete_treeWidget_clicked();

private:
    Ui::MainWindow* ui;
    // treeWidget
    enum    treeItemType {itTopItem = 1000, itGroupItem, itImageItem};    //枚举类型，表示列号
    enum    treeColNum {colItem = 0, colItemType = 1}; //目录树列的编号定义

    //tableWidget
    enum    CellType {ctID = 1000, ctName, ctScore}; // 自定义单元格Type的类型，在创建单元格的Item时使用各单元格的类型
    enum    FieldColNum {colID = 0, colName, colScore};    //  各字段在表格中的列号

};
#endif // MAINWINDOW_H
