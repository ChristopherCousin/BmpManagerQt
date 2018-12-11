#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include "filemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int checkBeforeConversion();
private slots:

    void on_btnToConversionMenu_clicked();

    void on_btnOpenFile_clicked();

    void on_btnSetPathFile_clicked();

    void on_btnSingleThread_clicked();

    void on_btnConvertMultiThread_clicked();

private:
    Ui::MainWindow *ui;
    QString fileName;
    QString savePath;
    FileManager filemanager;
};

#endif // MAINWINDOW_H
