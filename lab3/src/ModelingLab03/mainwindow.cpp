#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "frequencytest.hpp"
#include "linearcongruentrandomizer.hpp"
#include "tablerandomizer.hpp"
#include <QDebug>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    setWindowTitle("ЛР3, Якуба Дмитрий, ИУ7-73Б");
    qDebug() << "Pval: " << FrequencyTest().getPValueOfSequence(
        LinearCongruentRandomizer().createRandomSequence(3, 5));
    char tmp[256];
    getcwd(tmp, 256);
    qDebug() << tmp;
    qDebug() << "Table: " << TableRandomizer().getRandomSequence(3, 5);
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }
