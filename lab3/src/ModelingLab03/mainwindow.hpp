#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTableWidget>

#include "handtestwindow.hpp"

#define NUMBER_OF_GENERATED_VALUES 1000

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_generateButton_clicked();

    void on_handTestingButton_clicked();

private:
    void fullTableWithValues(QTableWidget *table, QVector<long> oneDigitValues,
        QVector<long> twoDigitValues, QVector<long> threeDigitValues);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP
