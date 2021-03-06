#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class MyTableModel;
class PlotWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionInsert_row_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    MyTableModel *m_model;
    PlotWidget *m_plotWidget;

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // MAINWINDOW_H
