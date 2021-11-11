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

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
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
    resizeTableWidget(ui->resultTableWidget, currentStatesNumber, 3);

    ui->resultTableWidget->setHorizontalHeaderLabels(QStringList() << "Вероятность"
                                                                   << "t₀"
                                                                   << "tₙ");

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

    const auto nStates = ui->numberOfStatesSpinBox->value();

    QVector<double> p0_1(nStates);
    p0_1[0] = 1;
    QVector<double> p0_a(nStates, 1.0 / nStates);

    qDebug() << intensityMatrix;
    const auto result = solve(intensityMatrix);
    const auto time_result_1 = get_system_times(intensityMatrix, result, p0_1, 1e-3, 1e-3);
    const auto time_result_a = get_system_times(intensityMatrix, result, p0_a, 1e-3, 1e-3);

    resizeIntensityMatrix(nStates);
    for (int i = 0; i < nStates; ++i)
    {
        ui->resultTableWidget->item(i, 0)->setText(QString::number(result[i]));
        ui->resultTableWidget->item(i, 1)->setText(QString::number(time_result_1[i]));
        ui->resultTableWidget->item(i, 2)->setText(QString::number(time_result_a[i]));
    }
}
