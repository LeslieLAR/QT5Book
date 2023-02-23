#include "qwdlgmanual.h"
#include "ui_qwdlgmanual.h"

QWDlgManual::QWDlgManual(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::QWDlgManual)
{
    ui->setupUi(this);
    this->setMaximumSize(270, 230);

    iniUI(); //界面创建与布局
    iniSignalSlot();//信号与槽的关联

    setWindowTitle("From cerated mannually");

}

QWDlgManual::~QWDlgManual()
{
    delete ui;
}

void QWDlgManual::iniUI()
{
    //创建CheckBox，并水平布局
    chkBoxUnder = new QCheckBox("下划线");
    chkBoxItalic = new QCheckBox("加粗");
    chkBoxBold = new QCheckBox("黑体");
    QHBoxLayout* HLay1 = new QHBoxLayout;
    HLay1->addWidget(chkBoxUnder);
    HLay1->addWidget(chkBoxItalic);
    HLay1->addWidget(chkBoxBold);

    //创建RadioButton，并水平布局
    rBtnBlack = new QRadioButton("黑");
    rBtnBlack->setChecked(true);
    rBtnRed = new QRadioButton("红");
    rBtnBlue = new QRadioButton("蓝");
    QHBoxLayout* HLay2 = new QHBoxLayout;
    HLay2->addWidget(rBtnBlack);
    HLay2->addWidget(rBtnRed);
    HLay2->addWidget(rBtnBlue);

    //创建PushButton，并水平布局
    btnOK = new QPushButton("确定");
    btnCannel = new QPushButton("取消");
    btnClose = new QPushButton("退出");
    QHBoxLayout* HLay3 = new QHBoxLayout;
    HLay3->addWidget(btnOK);
    HLay3->addWidget(btnCannel);
    HLay3->addWidget(btnClose);

    //创建文本并初始化字体
    txtEdit = new QPlainTextEdit;
    txtEdit->setPlainText("It is  my demo.");
    QFont font = txtEdit->font(); //获取字体
    font.setPointSize(20);//设置字体大小
    txtEdit->setFont(font);//设置字体

    //创建垂直布局
    QVBoxLayout* VLay = new QVBoxLayout;
    VLay->addLayout(HLay1);
    VLay->addLayout(HLay2);
    VLay->addWidget(txtEdit);
    VLay->addLayout(HLay3);

    this->setLayout(VLay); //设置窗口主布局
}

void QWDlgManual::iniSignalSlot()
{
    //颜色
    connect(rBtnBlue, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(rBtnRed, SIGNAL(clicked()), this, SLOT(setTextFontColor()));
    connect(rBtnBlack, SIGNAL(clicked()), this, SLOT(setTextFontColor()));

    //字体
    connect(chkBoxUnder, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxUnder(bool)));
    connect(chkBoxItalic, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxItalic(bool)));
    connect(chkBoxBold, SIGNAL(clicked(bool)), this, SLOT(on_chkBoxBold(bool)));

    //按钮
    connect(btnOK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnCannel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(close()));
}

void QWDlgManual::on_chkBoxUnder(bool checked)
{
    QFont font = txtEdit->font();
    font.setUnderline(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::on_chkBoxItalic(bool checked)
{
    QFont font = txtEdit->font();
    font.setItalic(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::on_chkBoxBold(bool checked)
{
    QFont font = txtEdit->font();
    font.setBold(checked);
    txtEdit->setFont(font);
}

void QWDlgManual::setTextFontColor()
{
    QPalette plet = txtEdit->palette();
    if(rBtnBlue->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::blue);
    }
    else if(rBtnRed->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::red);
    }
    else if(rBtnBlack->isChecked())
    {
        plet.setColor(QPalette::Text, Qt::black);
    }
    else
    {
        plet.setColor(QPalette::Text, Qt::black);
    }

    txtEdit->setPalette(plet);
}

