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

    QMessageBox::information(this, ("Info"), fileName);

}


void MainWindow::on_pushButton_2_clicked()
{
    savePath = QFileDialog::getSaveFileName(this,
            tr("Set name of new BMP File"), "_GreyColor",
            tr("Bmp File (*.bmp)"));


    QMessageBox::information(this, ("Info"), savePath);
}

void MainWindow::on_pushButton_3_clicked()
{
    if(savePath == "")
    {
        on_pushButton_2_clicked();
    }
    FileManager filemanager;
    filemanager._ToGreyColour(fileName.toStdString(), savePath.toStdString());
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
