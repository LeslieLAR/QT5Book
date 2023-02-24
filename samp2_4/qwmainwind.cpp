#include "qwmainwind.h"
#include "ui_qwmainwind.h"



QWMainWind::QWMainWind(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::QWMainWind)
{
    ui->setupUi(this);
//    this->setMinimumSize(1200, 500);
//    this->setMaximumSize(1200, 500);
    this->setFixedSize(1200, 500);

    iniUI(); //程序设计的UI初始化
    updateCurFile("未命名");
    iniSignalSlots();
}

QWMainWind::~QWMainWind()
{
    delete ui;
}


void QWMainWind::iniUI()
{
    //状态栏添加组件
    fLabCurFile = new QLabel;
    fLabCurFile->setMinimumWidth(250);
    fLabCurFile->setText("当前文件:");
    ui->statusbar->addWidget(fLabCurFile); //左下键有文字：当前文件

    progressBar1 = new QProgressBar;
    progressBar1->setMaximumWidth(200);
    progressBar1->setMinimum(5);
    progressBar1->setMaximum(50);
    progressBar1->setValue(ui->textEdit->font().pointSize());
    ui->statusbar->addWidget(progressBar1);

    //*******************

    //工具栏添加组件
    spinFontSize = new QSpinBox;// 工具栏上的文字大小 SpinBox
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    spinFontSize->setValue(ui->textEdit->font().pointSize());//初始值
    spinFontSize->setMinimumWidth(50);//设置组件最小宽度

    ui->mainToolBar->addWidget(new QLabel("字体大小 ")); //不引用的Label无需定义变量
    ui->mainToolBar->addWidget(spinFontSize); //SpinBox添加到工具栏

    ui->mainToolBar->addSeparator(); //工具栏上增加分隔条
    ui->mainToolBar->addWidget(new QLabel(" 字体 "));
    comboFont = new QFontComboBox;//字体名称ComboBox
    comboFont->setMinimumWidth(150); //设置组件最小宽度
    ui->mainToolBar->addWidget(comboFont);//添加到工具栏

    // ui->mainToolBar->addAction(ui->actionClear);

    setCentralWidget(ui->textEdit); //将txtEdit设置为中心组件，自动填充整个工作区



}

void QWMainWind::iniSignalSlots()
{
    // 粗体、斜体、下划线的函数
    connect(ui->actionFontBold, SIGNAL(triggered(bool)), this, SLOT(actFontBold_triggered(bool)));
    connect(ui->actionFontItalic, SIGNAL(triggered(bool)), this, SLOT(actFontItalic_triggered(bool)));
    connect(ui->actionFontUnder, SIGNAL(triggered(bool)), this, SLOT(actFontUnder_triggered(bool)));

    // 打开、新建、保存的槽函数
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(actOpen_triggered()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(actNew_triggered()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(actSavetriggered()));



    connect(spinFontSize, SIGNAL(valueChanged(int)), this, SLOT(spinBoxFontSize_valueChanged(int)));
    connect(comboFont, SIGNAL(currentIndexChanged(const QString)), this, SLOT(comboFont_currentIndexChanged(const QString)));

}


void QWMainWind::actFontBold_triggered(bool checked)
{
    // qDebug() << "on_actFontBold_triggered";
    QTextCharFormat fmt;

    if(checked)
        fmt.setFontWeight(QFont::Bold);
    else
        fmt.setFontWeight(QFont::Normal);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::actFontItalic_triggered(bool checked)
{
    // qDebug() << "on_actFontItalic_triggered";
    QTextCharFormat fmt;
    fmt.setFontItalic(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::actFontUnder_triggered(bool checked)
{
    // qDebug() << "on_actFontUnder_triggered";
    QTextCharFormat fmt;
    fmt.setFontUnderline(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void QWMainWind::updateCurFile(QString aFile)
{
    //更新当前文件名，并更新状态栏提示
    fCurFileName = aFile;
    fLabCurFile->setText("当前文件：" + fCurFileName);
}


void QWMainWind::actNew_triggered()
{
    // qDebug() << "on_actNew_triggered";
    ui->textEdit->clear();
    updateCurFile("新建文本文件");
}

void QWMainWind::actOpen_triggered()
{
    qDebug() << "on_actOpen_triggered";
    QString curPath, aFileName;
    curPath = QCoreApplication::applicationDirPath(); //获取应用程序的路径

    //调用打开文件对话框打开一个文件
    aFileName = QFileDialog::getOpenFileName(this, tr("打开一个文件"), curPath,
                "C++程序文件(*.cpp);;H头文件(*.h);;文本文件(*.txt);;所有文件(*.*)");

    if (!aFileName.isEmpty())
    {
        QFile aFile(aFileName);  //以文件方式读出
        if (aFile.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream aStream(&aFile); //用文本流读取文件
            while (!aStream.atEnd())
                ui->textEdit->append(aStream.readLine()); //读取一个文本行
            updateCurFile(aFileName); //更新状态栏显示
        }
        aFile.close();
    }
}

void QWMainWind::actSavetriggered()
{

    QString aFileName = QFileDialog::getSaveFileName(this, "另存为",
                        QCoreApplication::applicationFilePath());
    if (!aFileName.isEmpty())
    {
        QFile file(aFileName);
        file.open(QIODevice::WriteOnly);
        QByteArray ba;
        ba.append(ui->textEdit->toPlainText());
        file.write(ba);
        file.close();
        ui->textEdit->clear();

    }
}

void QWMainWind::spinBoxFontSize_valueChanged(int aFontSize)
{
    //改变字体大小的SpinBox的响应
    QTextCharFormat fmt;
    fmt.setFontPointSize(aFontSize); //设置字体大小
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progressBar1->setValue(aFontSize);
}

void QWMainWind::comboFont_currentIndexChanged(const QString arg1)
{
    //FontCombobox的响应，选择字体名称
    QTextCharFormat fmt;
    fmt.setFontFamily(arg1);//设置字体名称
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

