#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LabFileName = new QLabel("LabFileName");
    ui->statusBar->addWidget(LabFileName);
    this->setCentralWidget(ui->scrollArea); //设置中心布局组件
    iniTree();//初始化目录树

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniTree()
{
    qDebug() << __FUNCTION__;
    //初始化Tree
    QString    dataStr = ""; // Item的Data 存储的string

    ui->treeFiles->clear();//清除目录树所有节点
    qDebug() << ui->treeFiles;
    QIcon   icon;
    icon.addFile(":/images/icons/15.ico"); //设置ICON的图标

    QTreeWidgetItem*  item = new QTreeWidgetItem(MainWindow::itTopItem); //新建节点时设定类型为 itTopItem 1001 也是数字 没有实际意义

    item->setIcon(MainWindow::colItem, icon); //设置第1列的图标

    item->setText(MainWindow::colItem, "图片文件"); //设置第1列的文字
    item->setText(MainWindow::colItemType, "type=itTopItem"); //设置第2列的文字

    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked); //设置为选中

    item->setData(MainWindow::colItem, Qt::UserRole, QVariant(dataStr)); //设置节点第1列的Qt::UserRole的Data

    ui->treeFiles->addTopLevelItem(item);//添加顶层节点
}

void MainWindow::addFolderItem(QTreeWidgetItem* parItem, QString dirName)
{
    qDebug() << __FUNCTION__;
    //添加一个目录节点
    QIcon   icon(":/images/icons/open3.bmp");
    QString NodeText = getFinalFolderName(dirName); //从一个完整目录名称里，获得最后的文件夹名称

    QTreeWidgetItem* item; //节点
    item = new QTreeWidgetItem(MainWindow::itGroupItem); //新建节点, 设定type为 itGroupItem
    item->setIcon(colItem, icon); //设置图标
    item->setText(colItem, NodeText); //最后的文件夹名称，第1列
    item->setText(colItemType, "type=itGroupItem"); //完整目录名称，第2列
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate); //设置节点选项
    item->setCheckState(colItem, Qt::Checked); //节点选中
    item->setData(colItem, Qt::UserRole, QVariant(dirName)); //设置角色为Qt::UserRole的Data,存储完整目录名称

    parItem->addChild(item); //在父节点下面添加子节点

}

void MainWindow::addImageItem(QTreeWidgetItem* parItem, QString aFilename)
{
    qDebug() << __FUNCTION__;
    //添加一个图片文件节点
    QIcon   icon(":/images/icons/31.ico");//ICON的图标
    QString NodeText = getFinalFolderName(aFilename); //获得最后的文件名称

    QTreeWidgetItem* item; //节点
    item = new QTreeWidgetItem(MainWindow::itImageItem); //新建节点时设定类型为 itImageItem
    item->setIcon(colItem, icon); //设置图标
    item->setText(colItem, NodeText); //最后的文件夹名称
    item->setText(colItemType, "type=itImageItem"); //完整目录名称
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate); //设置节点选项
    item->setCheckState(colItem, Qt::Checked); //节点选中
    item->setData(colItem, Qt::UserRole, QVariant(aFilename)); //设置节点Qt::UserRole的Data,存储完整文件名称

    parItem->addChild(item); //在父节点下面添加子节点
}

QString MainWindow::getFinalFolderName(const QString& fullPathName)
{
    qDebug() << __FUNCTION__;
    //从一个完整目录名称里，获得最后的文件夹名称
    int cnt = fullPathName.length(); //字符串长度
    int i = fullPathName.lastIndexOf("/"); //  最后一次出现的位置
    QString str = fullPathName.right(cnt - i - 1); //获得最后的文件夹的名称
    return str;

}

void MainWindow::on_actAddFolder_triggered()
{
    qDebug() << __FUNCTION__;
    // 选择一个文件夹,作为当前节点的子节点加入
    QString dir = QFileDialog::getExistingDirectory(); //选择目录
    if (!dir.isEmpty()) //选择目录名称不为空
    {
        QTreeWidgetItem* parItem = ui->treeFiles->currentItem(); //当前节点
        addFolderItem(parItem, dir); //在父节点下面添加一个组节点
    }
}


void MainWindow::on_actAddFiles_triggered()
{
    qDebug() << __FUNCTION__;
    //添加图片文件节点
    QStringList files = QFileDialog::getOpenFileNames(this, "选择一个或多个文件", "", "Images(*.jpg)"); //多选文件
    if (files.isEmpty()) //如果一个文件都没选
        return;

    QTreeWidgetItem* parItem, *item; //节点
    item = ui->treeFiles->currentItem(); //当前节点

    if (item->type() == itImageItem) //若当前节点是图片节点，取其父节点作为父节点
        parItem = item->parent();
    else //否则取当前节点为父节点
        parItem = item;

    for (int i = 0; i < files.size(); ++i)
    {
        QString aFilename = files.at(i); //得到StringList里的一行，也就是一个文件名
        addImageItem(parItem, aFilename); //添加一个图片节点
    }
}

