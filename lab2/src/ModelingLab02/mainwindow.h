#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QStringList>

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
    void on_numberOfStatesSpinBox_textChanged(const QString &arg1);

  private:
    Ui::MainWindow *ui;

    QVector<QVector<double>> intensityMatrix;

    void resizeIntensityMatrix(int size);
    void resizeTableWidget(QTableWidget *tableWidget, int rows, int cols);
    void resizeIntensityMatrixTableWidget(int size);
    void resizeResultTableWidget(int size);
};
#endif // MAINWINDOW_H
