#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnToConversionMenu_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_btnOpenFile_clicked()
{
    fileName = QFileDialog::getOpenFileName(
                this, tr("Select your BMP File"),
                "",
                tr("BMP Files (*.bmp)"));
}

void MainWindow::on_btnSetPathFile_clicked()
{
    savePath = QFileDialog::getSaveFileName(this,
            tr("Set name of new BMP File"), "_GreyColor",
            tr("Bmp File (*.bmp)"));
}

void MainWindow::on_btnSingleThread_clicked()
{
    if(checkBeforeConversion() == 1)
    {
        filemanager._ToGreyColour(fileName.toStdString(), savePath.toStdString());
        std::string time = std::to_string(filemanager.timeToFinish);
        ui->lblTimeToFinish->setText("Time in conversion in NanoSeconds: " + QString::fromStdString(time));
    }
}

void MainWindow::on_btnConvertMultiThread_clicked()
{
    if(checkBeforeConversion() == 1)
    {
        filemanager._MultiThreadToGreyColour(fileName.toStdString(), savePath.toStdString());
        std::string time = std::to_string(filemanager.timeToFinish);
        ui->lblTimeToFinish->setText("Time in conversion in NanoSeconds: " + QString::fromStdString(time));
    }
}
int MainWindow::checkBeforeConversion()
{
    if (fileName == "" && savePath == "")
    {
        QMessageBox::information(this, ("Info"), "You must select first the BMP File!");
        on_btnOpenFile_clicked();
        QMessageBox::information(this, ("Info"), "You must select where you'll save the BMP File!");
        on_btnSetPathFile_clicked();
        if (fileName != "" && savePath != "")
        {
            return 1;
        }
    }
    else if (fileName == "")
    {
        QMessageBox::information(this, ("Info"), "You must select first the BMP File!");
        on_btnOpenFile_clicked();
    }
    else if (savePath == "") {
        QMessageBox::information(this, ("Info"), "You must select where you'll save the BMP File!");
        on_btnSetPathFile_clicked();
    } else {
        return 1;
    } // END If
    return 0;
}
