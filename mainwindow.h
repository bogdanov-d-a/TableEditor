#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class MyTableModel;
class PlotWidget;
class DocumentState;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setCanSave(bool canSave);

private slots:
    void on_actionInsert_row_triggered();
    void on_actionAbout_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();

private:
    Ui::MainWindow *ui;
    MyTableModel *m_model;
    PlotWidget *m_plotWidget;
    DocumentState *m_docState;

protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // MAINWINDOW_H
