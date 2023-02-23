#ifndef QWDLGMANUAL_H
#define QWDLGMANUAL_H

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPushButton>
#include<QFont>

#include<QHBoxLayout>
#include<QVBoxLayout>
QT_BEGIN_NAMESPACE
namespace Ui
{
    class QWDlgManual;
}
QT_END_NAMESPACE

class QWDlgManual : public QDialog
{
    Q_OBJECT

public:
    QWDlgManual(QWidget* parent = nullptr);
    ~QWDlgManual();

private:
    Ui::QWDlgManual* ui;

    QCheckBox* chkBoxUnder;
    QCheckBox* chkBoxItalic;
    QCheckBox* chkBoxBold;

    QRadioButton* rBtnBlack;
    QRadioButton* rBtnRed;
    QRadioButton* rBtnBlue;

    QPlainTextEdit* txtEdit;

    QPushButton* btnOK;
    QPushButton* btnCannel;
    QPushButton* btnClose;

    void iniUI(); //UI创建与初始化
    void iniSignalSlot();//初始化信号与槽的连接

private slots:
    void on_chkBoxUnder(bool checked);
    void on_chkBoxItalic(bool checked);
    void on_chkBoxBold(bool checked);

    void setTextFontColor();
};
#endif // QWDLGMANUAL_H
