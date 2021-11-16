#ifndef HANDTESTWINDOW_HPP
#define HANDTESTWINDOW_HPP

#include <QDialog>
#include "frequencytest.hpp"

namespace Ui {
class handTestWindow;
}

class handTestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit handTestWindow(QWidget *parent = nullptr);
    ~handTestWindow();

private slots:
    void on_doTestButton_clicked();

private:
    QVector<long> getValuesFromTable();
    void prepareTableWidget();
    Ui::handTestWindow *ui;
};

#endif // HANDTESTWINDOW_HPP
