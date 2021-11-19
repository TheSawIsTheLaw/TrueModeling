#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("ЛР4, Моделирование, Якуба Дмитрий, ИУ7-73Б");
}

MainWindow::~MainWindow() { delete ui; }

QPair<double, double> MainWindow::simulateWithInverseConnectionDeltaTMethod()
{
    Processor processor(probabilityOfReturn, muParameter, sigmaParameter);
    RequestsGenerator generator(aParameter, bParameter);

    return Simulator(processor, generator).simulateUsingDeltaTMethod(numberOfRequests);
}

QPair<double, double> MainWindow::simulateWithoutInverseConnectionDeltaTMethod()
{
    Processor processor(0, muParameter, sigmaParameter);
    RequestsGenerator generator(aParameter, bParameter);

    return Simulator(processor, generator).simulateUsingDeltaTMethod(numberOfRequests);
}

QPair<double, double> MainWindow::simulateWithInverseConnectionEventMethod()
{
    Processor processor(probabilityOfReturn, muParameter, sigmaParameter);
    RequestsGenerator generator(aParameter, bParameter);

    return Simulator(processor, generator).simulateUsingEventMethod(numberOfRequests);
}

QPair<double, double> MainWindow::simulateWithoutInverseConnectionEventMethod()
{
    Processor processor(0, muParameter, sigmaParameter);
    RequestsGenerator generator(aParameter, bParameter);

    return Simulator(processor, generator).simulateUsingEventMethod(numberOfRequests);
}

#include <QDebug>
void MainWindow::on_makeModelingButton_clicked()
{
    aParameter = ui->aParameterSpinBox->text().toDouble();
    bParameter = ui->bParameterSpinBox->text().toDouble();
    muParameter = ui->muParameterSpinBox->text().toDouble();
    sigmaParameter = ui->sigmaParameterSpinBox->text().toDouble();

    numberOfRequests = ui->numberOfRequestsSpinBox->text().toULong();
    probabilityOfReturn = ui->returnProbabilitySpinBox->text().toDouble();

    qDebug() << simulateWithInverseConnectionDeltaTMethod();
}
