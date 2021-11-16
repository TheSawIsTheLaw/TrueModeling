#include "handtestwindow.hpp"
#include "ui_handtestwindow.h"

void handTestWindow::prepareTableWidget()
{
    ui->randomValuesTableWidget->setRowCount(10);
    ui->randomValuesTableWidget->setColumnCount(1);

    for (int i = 0; i < 10; i++)
    { ui->randomValuesTableWidget->setItem(i, 0, new QTableWidgetItem()); }
}

handTestWindow::handTestWindow(QWidget *parent)
: QDialog(parent), ui(new Ui::handTestWindow)
{
    ui->setupUi(this);

    setWindowTitle("Ручное тестирование");
    prepareTableWidget();
}

handTestWindow::~handTestWindow() { delete ui; }

QVector<long> handTestWindow::getValuesFromTable()
{
    QVector<long> values;

    for (int i = 0; i < ui->randomValuesTableWidget->rowCount(); i++)
    { values.append(ui->randomValuesTableWidget->item(i, 0)->text().toLong()); }

    return values;
}

#include <QDebug>
void handTestWindow::on_doTestButton_clicked()
{
    ui->answerLabel->setText(QString(
        "P-value: " +
        QString::number(FrequencyTest().getPValueOfSequence(getValuesFromTable()))));
}
