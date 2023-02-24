#ifndef QMYWIDGET_H
#define QMYWIDGET_H

#include <QWidget>
#include <QMetaProperty>
#include <QDebug>
#include "qperson.h"
namespace Ui
{
    class QmyWidget;
}

class QmyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QmyWidget(QWidget* parent = nullptr);
    ~QmyWidget();

private:
    Ui::QmyWidget* ui;
    QPerson* boy;
    QPerson* girl;
private slots:
//自定义槽函数
    void   ageChanged(int  value);
    void   spin_valueChanged(int arg1);

//界面按钮的槽函数
    void btnClear_clicked();
    void btnBoyInc_clicked();
    void btnGirlInc_clicked();
    void btnClassInfo_clicked();
};

#endif // QMYWIDGET_H
