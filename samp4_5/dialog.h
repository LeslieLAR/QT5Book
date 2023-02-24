#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget* parent = nullptr);
    ~Dialog();

private slots:
    void on_btnGetTime_clicked();

    void on_btnSetTime_clicked();

    void on_btnSetDate_clicked();

    void on_btnSetDateTime_clicked();

    void on_btnSetIntv_clicked();

    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_timer_timeout(); //定时器中断处理槽函数,手工定义

    void on_calendarWidget_selectionChanged();

private:
    Ui::Dialog* ui;
    QTimer* fTimer;  //定时器

    QTime fTimeCounter;//计时器
};
#endif // DIALOG_H
