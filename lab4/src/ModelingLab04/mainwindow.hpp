#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "simulator.hpp"
#include <QMainWindow>

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
    void on_makeModelingButton_clicked();

private:
    QPair<double, double> simulateWithInverseConnectionDeltaTMethod();
    QPair<double, double> simulateWithoutInverseConnectionDeltaTMethod();
    QPair<double, double> simulateWithInverseConnectionEventMethod();
    QPair<double, double> simulateWithoutInverseConnectionEventMethod();

    double aParameter;
    double bParameter;
    double muParameter;
    double sigmaParameter;
    size_t numberOfRequests;
    double probabilityOfReturn;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP
