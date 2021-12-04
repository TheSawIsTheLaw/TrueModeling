#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Якуба, ИУ7-73Б, Лабораторная работа 5");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_goModelingButton_clicked()
{

}

