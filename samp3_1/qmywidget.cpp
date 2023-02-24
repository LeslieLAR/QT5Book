#include "qmywidget.h"
#include "ui_qmywidget.h"
#include<QObject>
QmyWidget::QmyWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::QmyWidget)
{
    ui->setupUi(this);

    ;
    boy = new QPerson("王小明");
    boy->setProperty("score", 95);
    boy->setProperty("age", 10);
    boy->setProperty("sex", "Boy"); //动态属性
    connect(boy, &QPerson::ageChanged, this, &QmyWidget::ageChanged);
    connect(ui->spinBoy, SIGNAL(valueChanged(int)), this, SLOT(spin_valueChanged(int)));
    ui->spinBoy -> setProperty("isBoy", true);//动态属性


    girl = new QPerson("张小丽");
    girl->setProperty("score", 81);
    girl->setProperty("age", 20);
    girl->setProperty("sex", "Girl"); //动态属性
    connect(girl, &QPerson::ageChanged, this, &QmyWidget::ageChanged);
    connect(ui->spinGirl, SIGNAL(valueChanged(int)), this, SLOT(spin_valueChanged(int)));
    ui->spinGirl -> setProperty("isBoy", false);//动态属性

    connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(btnClear_clicked()));
    connect(ui->btnClassInfo, SIGNAL(clicked()), this, SLOT(btnClassInfo_clicked()));
}

QmyWidget::~QmyWidget()
{
    delete ui;
}

void QmyWidget::ageChanged(int value)
{
    qDebug() << "ageChanged";
    //响应QPerson的ageChanged()信号
    Q_UNUSED(value);
    QPerson* aPerson = qobject_cast<QPerson*>(sender());  //类型投射
    QString hisName = aPerson->property("name").toString(); //姓名
    QString hisSex = aPerson->property("sex").toString(); //动态属性
    int hisAge = aPerson->property("age").toInt(); //通过属性获得年龄
    // int hisAge = aPerson->age(); //通过接口函数获取年龄

    ui->textEdit->appendPlainText(hisName + "," + hisSex + QString::asprintf(",年龄=%d", hisAge));

}

void QmyWidget::spin_valueChanged(int arg1)
{
    //响应界面上spinBox的valueChanged(int)信号
    qDebug() << "spin_valueChanged";
    Q_UNUSED(arg1);
    QSpinBox* spinBox = qobject_cast<QSpinBox*>(sender());

    if (spinBox->property("isBoy").toBool())
    {
        boy->setAge(spinBox->value());
    }
    else
    {
        girl->setAge(spinBox->value());
    }
}

void QmyWidget::btnClear_clicked()
{
    //"清空文本框"按钮
    qDebug() << "btnClear_clicked";
    ui->textEdit->clear();
}

void QmyWidget::btnBoyInc_clicked()
{
    //"boy长大一岁"按钮
    boy->incAge();
}

void QmyWidget::btnGirlInc_clicked()
{
    //"girl长大一岁"按钮
    girl->incAge();
}

void QmyWidget::btnClassInfo_clicked()
{
    qDebug() << "btnClassInfo_clicked";
    //"类的元对象信息"按钮
    const QMetaObject* meta = boy->metaObject();
    // const QMetaObject* meta = girl->metaObject();
    // const QMetaObject* meta = ui->spinBoy->metaObject();
    ui->textEdit->clear();

    ui->textEdit->appendPlainText("==元对象信息==\n");
    ui->textEdit->appendPlainText(QString("类名称：%1\n").arg(meta->className()));

    ui->textEdit->appendPlainText("property");
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); i++)
    {
        const char* propName = meta->property(i).name();
        ui->textEdit->appendPlainText(QString("属性名称=%1，属性值=%2").arg(propName).arg(boy->property(propName).toString()));
    }

    ui->textEdit->appendPlainText("");
    ui->textEdit->appendPlainText("classInfo");
    for (int i = meta->classInfoOffset(); i < meta->classInfoCount(); ++i)
    {
        QMetaClassInfo classInfo = meta->classInfo(i);
        ui->textEdit->appendPlainText(QString("Name=%1; Value=%2").arg(classInfo.name()).arg(classInfo.value()));
    }
}
