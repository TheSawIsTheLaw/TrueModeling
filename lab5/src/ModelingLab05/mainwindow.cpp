#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Якуба Дмитрий, ИУ7-73Б, Лабораторная работа 5");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_goModelingButton_clicked()
{
    SimulationParameters parameters;
    parameters.client.amountOfProccessedNeeded = ui->NumberOfClientsSpinBox->value();
    parameters.client.timeOfCome = ui->nextClientIntervalSpinBox->value();
    parameters.client.timeDelta = ui->nextClientIntervalPluxMinusSpinBox->value();

    parameters.operator1.timeOfService = ui->operator1ServiceTimeSpinBox->value();
    parameters.operator1.timeDelta = ui->operator1ServiceTimePlusMinusSpinBox->value();
    parameters.operator2.timeOfService = ui->operator2ServiceTimeSpinBox->value();
    parameters.operator2.timeDelta = ui->operator2ServiceTimePlusMinusSpinBox->value();
    parameters.operator3.timeOfService = ui->operator3ServiceTimeSpinBox->value();
    parameters.operator3.timeDelta = ui->operator3ServiceTimePlusMinusSpinBox->value();

    parameters.computer1.timeOfService = ui->computer1ServiceTimeSpinBox->value();
    parameters.computer2.timeOfService = ui->computer2ServiceTimeSpinBox->value();

    Results resultOfSimulation = doSimulate(parameters);

    ui->denialOfServiceResultLabel->setText(
        QString::number(resultOfSimulation.numberOfDenials));
    ui->ProbabilityOfDenialOfServiceResultLabel->setText(
        QString::number(resultOfSimulation.probabilityOfDenial));
}
