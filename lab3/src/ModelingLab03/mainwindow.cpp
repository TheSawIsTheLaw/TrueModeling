#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "frequencytest.hpp"
#include "linearcongruentrandomizer.hpp"
#include "tablerandomizer.hpp"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("ЛР3, Якуба Дмитрий, ИУ7-73Б");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::fullTableWithValues(QTableWidget *table, QVector<long> oneDigitValues,
    QVector<long> twoDigitValues, QVector<long> threeDigitValues)
{
    table->setRowCount(oneDigitValues.size());
    table->setColumnCount(3);

    for (int i = 0; i < table->rowCount(); i++)
    {
        table->setItem(i, 0, new QTableWidgetItem(QString::number(oneDigitValues[i])));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(twoDigitValues[i])));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(threeDigitValues[i])));
    }
}

void MainWindow::on_generateButton_clicked()
{
    LinearCongruentRandomizer lcRandomizer;
    QVector<long> generatedByLCROneDigit =
        lcRandomizer.createRandomSequence(1, NUMBER_OF_GENERATED_VALUES);
    QVector<long> generatedByLCRTwoDigit =
        lcRandomizer.createRandomSequence(2, NUMBER_OF_GENERATED_VALUES);
    QVector<long> generatedByLCRThreeDigit =
        lcRandomizer.createRandomSequence(3, NUMBER_OF_GENERATED_VALUES);

    TableRandomizer tRandomizer;
    QVector<long> generatedByTROneDigit =
        tRandomizer.getRandomSequence(1, NUMBER_OF_GENERATED_VALUES);
    QVector<long> generatedByTRTwoDigit =
        tRandomizer.getRandomSequence(2, NUMBER_OF_GENERATED_VALUES);
    QVector<long> generatedByTRThreeDigit =
        tRandomizer.getRandomSequence(3, NUMBER_OF_GENERATED_VALUES);

    ui->algResultTableWidget->setHorizontalHeaderLabels(QStringList() << "1"
                                                                      << "2"
                                                                      << "3");
    ui->tableResultTableWidget->setHorizontalHeaderLabels(QStringList() << "1"
                                                                        << "2"
                                                                        << "3");

    fullTableWithValues(ui->algResultTableWidget, generatedByLCROneDigit,
        generatedByLCRTwoDigit, generatedByLCRThreeDigit);

    fullTableWithValues(ui->tableResultTableWidget, generatedByTROneDigit,
                        generatedByTRTwoDigit, generatedByTRThreeDigit);

    FrequencyTest tester;
    ui->algPValOneDigit->setText(QString::number(tester.getPValueOfSequence(generatedByLCROneDigit)));
    ui->algPValTwoDigit->setText(QString::number(tester.getPValueOfSequence(generatedByLCRTwoDigit)));
    ui->algPValThreeDigit->setText(QString::number(tester.getPValueOfSequence(generatedByLCRThreeDigit)));


    ui->tablePValOneDigit->setText(QString::number(tester.getPValueOfSequence(generatedByTROneDigit)));
    ui->tablePValTwoDigit->setText(QString::number(tester.getPValueOfSequence(generatedByTRTwoDigit)));
    ui->tablePValThreeDigit->setText(QString::number(tester.getPValueOfSequence(generatedByTRThreeDigit)));
}
