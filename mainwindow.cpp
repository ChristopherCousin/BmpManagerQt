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

void MainWindow::on_pushButton_clicked()
{

    fileName = QFileDialog::getOpenFileName(
                this, tr("Select your BMP File"),
                "",
                tr("BMP Files (*.bmp)"));

}


void MainWindow::on_pushButton_2_clicked()
{
    savePath = QFileDialog::getSaveFileName(this,
            tr("Set name of new BMP File"), "_GreyColor",
            tr("Bmp File (*.bmp)"));

}

void MainWindow::on_pushButton_3_clicked()
{
    if (fileName == "" && savePath == "")
    {
        QMessageBox::information(this, ("Info"), "You must select first the BMP File!");
        on_pushButton_clicked();
        QMessageBox::information(this, ("Info"), "You must select where you'll save the BMP File!");
        on_pushButton_2_clicked();
        if (fileName != "" && savePath != "")
        {
            filemanager._ToGreyColour(fileName.toStdString(), savePath.toStdString());
            std::string time = std::to_string(filemanager.timeToFinish);
            ui->lblTimeToFinish->setText("Time in conversion in NanoSeconds: " + QString::fromStdString(time));
        }
    }
    else if (fileName == "")
    {
        QMessageBox::information(this, ("Info"), "You must select first the BMP File!");
        on_pushButton_clicked();
    }
    else if (savePath == "") {
        QMessageBox::information(this, ("Info"), "You must select where you'll save the BMP File!");
        on_pushButton_2_clicked();
    } else {
        filemanager._ToGreyColour(fileName.toStdString(), savePath.toStdString());
        std::string time = std::to_string(filemanager.timeToFinish);
        ui->lblTimeToFinish->setText("Time in conversion in NanoSeconds: " + QString::fromStdString(time));
    }
}

void MainWindow::on_GreyScale_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_GreyScale_2_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_6_clicked()
{
    on_pushButton_clicked();
}

void MainWindow::on_pushButton_5_clicked()
{

    on_pushButton_2_clicked();

}

void MainWindow::on_pushButton_4_clicked()
{
    if (fileName == "" && savePath == "")
    {
        QMessageBox::information(this, ("Info"), "You must select first the BMP File!");
        on_pushButton_clicked();
        QMessageBox::information(this, ("Info"), "You must select where you'll save the BMP File!");
        on_pushButton_2_clicked();
        if (fileName != "" && savePath != "")
        {
            filemanager._MultiThreadToGreyColour(fileName.toStdString(), savePath.toStdString());
        }
    }
    else if (fileName == "")
    {
        QMessageBox::information(this, ("Info"), "You must select first the BMP File!");
        on_pushButton_clicked();
    }
    else if (savePath == "") {
        QMessageBox::information(this, ("Info"), "You must select where you'll save the BMP File!");
        on_pushButton_2_clicked();
    } else {
        filemanager._MultiThreadToGreyColour(fileName.toStdString(), savePath.toStdString());
    }

}
