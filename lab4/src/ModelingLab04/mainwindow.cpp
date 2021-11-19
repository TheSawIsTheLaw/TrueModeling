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

void MainWindow::on_makeModelingButton_clicked()
{
    aParameter = ui->aParameterSpinBox->value();
    bParameter = ui->bParameterSpinBox->value();
    muParameter = ui->muParameterSpinBox->value();
    sigmaParameter = ui->sigmaParameterSpinBox->value();

    numberOfRequests = ui->numberOfRequestsSpinBox->value();
    probabilityOfReturn = ui->returnProbabilitySpinBox->value();

    QPair<double, double> withoutInverseDeltaT = simulateWithoutInverseConnectionDeltaTMethod();
    QPair<double, double> withInverseDeltaT = simulateWithInverseConnectionDeltaTMethod();

    QPair<double, double> withoutInverseEvent = simulateWithoutInverseConnectionEventMethod();
    QPair<double, double> withInverseEvent = simulateWithInverseConnectionEventMethod();

    ui->withoutInverseConnectionDeltaTAnswerLabel->setText(QString::number(withoutInverseDeltaT.second));

    ui->inverseConnectionDeltaTReturnedRequestsAnswerLabel->setText(QString::number(withInverseDeltaT.first));
    ui->inverseConnectionDeltaTMaxQueueAnswerLabel->setText(QString::number(withInverseDeltaT.second));

    ui->withoutInverseConnectionEventMaxQueueAnswerLabel->setText(QString::number(withoutInverseEvent.second));

    ui->inverseConnectionEventReturnedAnswerLabel->setText(QString::number(withInverseEvent.first));
    ui->inverseConnectionEventMaxQueueAnswerLabel->setText(QString::number(withInverseEvent.second));
}
