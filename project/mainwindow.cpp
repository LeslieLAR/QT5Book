#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand((unsigned)time(NULL));
}

MainWindow::~MainWindow()
{

}
//初始化
void MainWindow::on_init_ListWidget_clicked()
{
    ui->listWidget->clear(); //清除项

    QListWidgetItem* aItem; //每一行是一个QListWidgetItem

    for (int i = 0; i < 10; i++)
    {
        QString str = QString::asprintf("Item %d", i + 1);
        aItem = new QListWidgetItem(); //新建一个项
        aItem->setText(str); //设置文字标签
        // aItem->setCheckState(Qt::Unchecked); //设置为选中状态
        ui->listWidget->addItem(aItem); //增加一个项
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    }
    delete aItem;
}

//插入
void MainWindow::on_insert_ListWidget_clicked()
{
    QListWidgetItem* aItem = new QListWidgetItem("New Inserted Item"); //创建一个项
    aItem->setCheckState(Qt::Checked); //设置为checked
    aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    ui->listWidget->insertItem(ui->listWidget->currentRow(), aItem); //在当前行的上方插入一个项
}

//添加
void MainWindow::on_add_ListWidget_clicked()
{
    QListWidgetItem* aItem = new QListWidgetItem("New Added Item"); //创建一个Item
    aItem->setCheckState(Qt::Checked); //设置为checked
    aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    ui->listWidget->addItem(aItem);//增加一个项
}

//删除
void MainWindow::on_delete_ListWidget_clicked()
{
    int row = ui->listWidget->currentRow(); //当前行
    QListWidgetItem* aItem = ui->listWidget->takeItem(row); //移除指定行的项，但不delete
    delete aItem; //需要手工删除对象
}

//初始化
void MainWindow::on_init_TableWidget_clicked()
{
    ui->tableWidget->clear();

    QStringList headerText;
    headerText << "I D" << "姓 名" << "分 数" ;

    ui->tableWidget->setColumnCount(headerText.count());//列数设置为与 headerText的行数相等
#if 0
    ui->tableWidget->setHorizontalHeaderLabels(headerText);
#endif
    QTableWidgetItem*    headerItem;
    for (int i = 0; i < ui->tableWidget->columnCount(); i++) //列编号从0开始
    {
        headerItem = new QTableWidgetItem(headerText.at(i)); //新建一个QTableWidgetItem， headerText.at(i)获取headerText的i行字符串
        QFont font = headerItem->font(); //获取原有字体设置
        font.setBold(true);//设置为粗体
        font.setPointSize(12);//字体大小
        headerItem->setTextColor(Qt::red);//字体颜色
        headerItem->setFont(font);//设置字体
        ui->tableWidget->setHorizontalHeaderItem(i, headerItem); //设置表头单元格的Item
    }

    for (int i = 0; i < 10 ; i++ )
    {
        int curRow = ui->tableWidget->rowCount(); //当前行号
        ui->tableWidget->insertRow(curRow);//在表格尾部添加一行

        QTableWidgetItem*    item;
        QString strID, strName, strScore;

        strID = QString::asprintf("#%d", i + 1); //学生ID
        item = new  QTableWidgetItem(strID, ctID);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
        ui->tableWidget->setItem(i, colID, item); //为单元格设置Item

        strName = QString::asprintf("学生%d", i + 1); //学生姓名
        item = new  QTableWidgetItem(strName, ctName);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
        ui->tableWidget->setItem(i, colName, item); //为单元格设置Item


        strScore = QString::asprintf("%d", qrand() % 10 + 90);
        item = new  QTableWidgetItem(strScore, ctScore);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
        ui->tableWidget->setItem(i, colScore, item); //为单元格设置Item
        // qDebug() << strID << strName << strScore;
    }
}

//插入
void MainWindow::on_insert_TableWidget_clicked()
{
    int curRow = ui->tableWidget->currentRow(); //当前行号
    ui->tableWidget->insertRow(curRow); //插入一行，但不会自动为单元格创建item

    QTableWidgetItem*    item;
    QString strID, strName, strScore;

    strID = QString::asprintf("#%d", curRow + 1); //学生ID
    item = new  QTableWidgetItem(strID, ctID);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
    ui->tableWidget->setItem(curRow, colID, item); //为单元格设置Item

    strName = QString::asprintf("学生%d", curRow + 1); //学生姓名
    item = new  QTableWidgetItem(strName, ctName);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
    ui->tableWidget->setItem(curRow, colName, item); //为单元格设置Item


    strScore = QString::asprintf("%d", qrand() % 10 + 90);
    item = new  QTableWidgetItem(strScore, ctScore);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
    ui->tableWidget->setItem(curRow, colScore, item); //为单元格设置Item

}

//添加
void MainWindow::on_add_TableWidget_clicked()
{
    int curRow = ui->tableWidget->rowCount(); //当前行号
    ui->tableWidget->insertRow(curRow);//在表格尾部添加一行

    QTableWidgetItem*    item;
    QString strID, strName, strScore;

    strID = QString::asprintf("#%d", curRow + 1); //学生ID
    item = new  QTableWidgetItem(strID, ctID);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
    ui->tableWidget->setItem(curRow, colID, item); //为单元格设置Item

    strName = QString::asprintf("学生%d", curRow + 1); //学生姓名
    item = new  QTableWidgetItem(strName, ctName);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
    ui->tableWidget->setItem(curRow, colName, item); //为单元格设置Item


    strScore = QString::asprintf("%d", qrand() % 10 + 90);
    item = new  QTableWidgetItem(strScore, ctScore);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
    ui->tableWidget->setItem(curRow, colScore, item); //为单元格设置Item
}

//删除
void MainWindow::on_delete_TableWidget_clicked()
{
    int curRow = ui->tableWidget->currentRow(); //当前行号
    ui->tableWidget->removeRow(curRow); //删除当前行及其items
}

//初始化
void MainWindow::on_init_treeWidget_clicked()
{
    ui->treeWidget->clear();//清除目录树所有节点
    QTreeWidgetItem*  topitem = new QTreeWidgetItem(MainWindow::itTopItem); //新建节点时设定类型为 itTopItem 1001 也是数字 没有实际意义

    topitem = new QTreeWidgetItem(MainWindow::itTopItem);
    topitem->setText(MainWindow::colItem, "同事"); //设置第1列的文字
    topitem->setText(MainWindow::colItemType, "type=itTopItem"); //设置第2列的文字
    topitem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    topitem->setCheckState(colItem, Qt::Checked); //设置为选中

    ui->treeWidget->addTopLevelItem(topitem);//添加顶层节点
}

//插入
void MainWindow::on_insert_treeWidget_clicked()
{
    QTreeWidgetItem* parItem = ui->treeWidget->currentItem(); //当前节点
    QTreeWidgetItem* item; //节点
    item = new QTreeWidgetItem(MainWindow::itGroupItem); //新建节点, 设定type为 itGroupItem

    item->setText(colItem, "on_insert_treeWidget_clicked"); //最后的文件夹名称，第1列
    item->setText(colItemType, "type=itGroupItem"); //完整目录名称，第2列
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate); //设置节点选项
    item->setCheckState(colItem, Qt::Checked); //节点选中

    parItem->addChild(item); //在父节点下面添加子节点
}

//删除
void MainWindow::on_delete_treeWidget_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem(); //当前节点
    QTreeWidgetItem* parItem = item->parent(); //父节点
    parItem->removeChild(item);//The removed item will not be deleted
}

