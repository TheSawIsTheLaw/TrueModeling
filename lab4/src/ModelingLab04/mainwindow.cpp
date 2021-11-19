#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("ЛР4, Моделирование, Якуба Дмитрий, ИУ7-73Б");
}

MainWindow::~MainWindow()
{
    delete ui;
}

