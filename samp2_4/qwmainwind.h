#ifndef QWMAINWIND_H
#define QWMAINWIND_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QFontDialog>
#include <QCoreApplication>
#include <QTextCharFormat>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class QWMainWind;
}
QT_END_NAMESPACE

class QWMainWind : public QMainWindow
{
    Q_OBJECT
private:
    QString fCurFileName;       //当前文件名
    QLabel* fLabCurFile;        //状态栏里显示当前文件的Label
    QProgressBar* progressBar1; //状态栏上的进度条

    QSpinBox* spinFontSize;     //字体大写
    QFontComboBox* comboFont;   //字体名称

    void iniUI();                   //程序设计的UI初始化
    void iniSignalSlots();          //手工关联信号与槽
    void updateCurFile(QString aFile);


public slots:
    void actFontBold_triggered(bool checked);    // 粗体Action
    void actFontItalic_triggered(bool checked);  // 斜体Action
    void actFontUnder_triggered(bool checked);   // 下划线Action

    void actNew_triggered();//新建文件
    void actOpen_triggered();//打开文件
    void actSavetriggered();//打开文件

    void spinBoxFontSize_valueChanged(int aFontSize);//改变字体大小的SpinBox的响应
    void comboFont_currentIndexChanged(const QString arg1);//FontCombobox的响应，选择字体名称

public:
    QWMainWind(QWidget* parent = nullptr);
    ~QWMainWind();
private:
    Ui::QWMainWind* ui;
};
#endif // QWMAINWIND_H
