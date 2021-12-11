#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "Simulation.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Якуба, ИУ7-73Б, Лабораторная работа 5");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_goModelingButton_clicked()
{
    SimulationParameters parameters;
    parameters.client.amount = ui->NumberOfClientsSpinBox->value();
    parameters.client.timeOfCome = ui->nextClientIntervalSpinBox->value();
    parameters.client.timeDelta = ui->nextClientIntervalPluxMinusSpinBox->value();

    parameters.client.probForSendWindow = ui->probabilityForSendWindowSpinBox->value();
    parameters.client.probForGetWindow = ui->probabilityForGetWindowSpinBox->value();
    parameters.client.probForMoneytalksWindow = ui->probabilityOfMoneytalksSpinBox->value();

    parameters.terminal.timeOfService = ui->terminalServiceTimeSpinBox->value();
    parameters.terminal.timeDelta = ui->terminalServiceTimePlusMinusSpinBox->value();

    parameters.client.probabilityOfReturnToMainQueue = ui->probabilityOfReturnToQueueSpinBox->value();

    parameters.sendWindow.maxQueueSize = ui->maxNumberOfClientsSpinBox->value();
    parameters.getWindow.maxQueueSize = ui->maxNumberOfClientsSpinBox->value();
    parameters.moneytalksWindow.maxQueueSize = ui->maxNumberOfClientsSpinBox->value();

    parameters.sendWindow.timeOfService = ui->sendServiceTimeSpinBox->value();
    parameters.sendWindow.timeDelta = ui->sendServiceTimePlusMinusSpinBox->value();

    parameters.getWindow.timeOfService = ui->getServiceTimeSpinBox->value();
    parameters.getWindow.timeDelta = ui->getServiceTimePlusMinusSpinBox->value();

    parameters.moneytalksWindow.timeOfService = ui->moneytalksServiceTimeSpinBox->value();
    parameters.moneytalksWindow.timeDelta = ui->moneytalksServiceTimePlusMinusSpinBox->value();

    Results resultOfSimulation = doSimulate(parameters);

    ui->denialOfServiceSendWindowResultLabel->setText(QString::number(resultOfSimulation.sendWindow.numberOfDenials));
    ui->ProbabilityOfDenialOfServiceSendWindowResultLabel->setText(QString::number(resultOfSimulation.sendWindow.probabilityOfDenial));
    ui->denialOfServiceGetWindowResultLabel->setText(QString::number(resultOfSimulation.getWindow.numberOfDenials));
    ui->ProbabilityOfDenialOfServiceGetWindowResultLabel->setText(QString::number(resultOfSimulation.getWindow.probabilityOfDenial));
    ui->denialOfServiceMoneytalksWindowResultLabel->setText(QString::number(resultOfSimulation.moneytalksWindow.numberOfDenials));
    ui->ProbabilityOfDenialOfServiceMoneytalksWindowResultLabel->setText(QString::number(resultOfSimulation.moneytalksWindow.probabilityOfDenial));

}
