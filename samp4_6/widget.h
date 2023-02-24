#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTextBlock>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private slots:
    void on_btnIniItems_clicked();

    void on_btnIni2_clicked();

    void on_comboBox_currentIndexChanged(const QString& arg1);

    void on_comboBox2_currentIndexChanged(const QString& arg1);

    void on_btnClearItems_clicked();

    void on_btnToComboBox_clicked();

    void on_btnClearText_clicked();

    void on_chkBoxReadonly_clicked(bool checked);

private:
    Ui::Widget* ui;
};
#endif // WIDGET_H
