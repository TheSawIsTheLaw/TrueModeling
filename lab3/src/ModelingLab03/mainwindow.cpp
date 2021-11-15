#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "frequencytest.hpp"
#include "linearcongruentrandomizer.hpp"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qDebug() << "Pval: " << FrequencyTest().getPValueOfSequence(
        LinearCongruentRandomizer().createRandomSequence(3, 5));
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }
