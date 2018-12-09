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
                "/home",
                tr("BMP Files (*.bmp)"));

    QMessageBox::information(this, ("Info"), fileName);

}


void MainWindow::on_pushButton_2_clicked()
{
    savePath = QFileDialog::getSaveFileName(this,
            tr("Set name of new BMP File"), "",
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
