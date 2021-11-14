#include "mainwindow.hpp"
#include "ui_mainwindow.h"


#include "linearcongruentrandomizer.hpp"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    LinearCongruentRandomizer randomizer;
    qDebug() << randomizer.createRandomSubsequence(5, 20);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

