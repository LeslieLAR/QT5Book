#ifndef QWDIALOG_H
#define QWDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class QWDialog;
}
QT_END_NAMESPACE

class QWDialog : public QDialog
{
    Q_OBJECT

public:
    QWDialog(QWidget* parent = nullptr);
    ~QWDialog();

private slots:
    void on_chkBoxUnder_clicked(bool checked);

    void on_chkBoxItalic_clicked(bool checked);

    void on_chkBoxBold_clicked(bool checked);

    void setTextFontColor();

private:
    Ui::QWDialog* ui;
};
#endif // QWDIALOG_H
