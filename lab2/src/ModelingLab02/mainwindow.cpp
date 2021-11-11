#include "mainwindow.h"
#include "solvation.cpp"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Лабораторная работа 2, Якуба, ИУ7-73Б");

    on_numberOfStatesSpinBox_textChanged(QString());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::resizeIntensityMatrix(int size)
{
    intensityMatrix.resize(size);
    for (auto &row : intensityMatrix) { row.resize(size); }
}

void MainWindow::resizeTableWidget(QTableWidget *tableWidget, int rows, int cols)
{
    tableWidget->setRowCount(rows);
    tableWidget->setColumnCount(cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (!tableWidget->item(i, j))
            {
                tableWidget->setItem(i, j, new QTableWidgetItem);
            }
        }
    }
}

void MainWindow::on_numberOfStatesSpinBox_textChanged(const QString &arg1)
{
    int currentStatesNumber = ui->numberOfStatesSpinBox->value();

    resizeTableWidget(
        ui->intensityMatrixTableWidget, currentStatesNumber, currentStatesNumber);
    resizeTableWidget(ui->resultTableWidget, currentStatesNumber, 2);

    ui->resultTableWidget->setHorizontalHeaderLabels(QStringList() << "Вероятность"
                                                                   << "T");

    resizeIntensityMatrix(currentStatesNumber);
}

bool MainWindow::readToIntensityMatrix()
{
    int numberOfColumns = ui->intensityMatrixTableWidget->columnCount();
    int numberOfRows = ui->intensityMatrixTableWidget->rowCount();

    bool isValid = true;
    for (int i = 0; i < numberOfRows; i++)
    {
        for (int j = 0; j < numberOfColumns && isValid; j++)
        {
            QString curItem = ui->intensityMatrixTableWidget->item(i, j)->text();
            intensityMatrix[i][j] = curItem == "" ? 0 : curItem.toDouble(&isValid);
            if (curItem[0] == "-")
                isValid = false;
        }
    }

    return isValid;
}

void MainWindow::on_startButton_clicked()
{
    bool readIsValid = readToIntensityMatrix();
    if (!readIsValid)
    {
        QMessageBox::critical(this, "Ошибка чтения",
            "В качестве элементов матрицы должны быть предоставлены положительные "
            "вещественные числа");
        return;
    }

    const auto numberOfStates = ui->numberOfStatesSpinBox->value();

    QVector<double> probability(numberOfStates);
    probability[0] = 1;

    QVector<double> systemSolvation = solve(intensityMatrix);
    QVector<double> time_result_1 = get_system_times(intensityMatrix, systemSolvation, probability, 1e-3, 1e-3);

    for (int i = 0; i < numberOfStates; i++)
    {
        ui->resultTableWidget->item(i, 0)->setText(QString::number(systemSolvation[i]));
        ui->resultTableWidget->item(i, 1)->setText(QString::number(time_result_1[i]));
    }
}
