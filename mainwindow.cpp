#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytablemodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(new MyTableModel());
}

MainWindow::~MainWindow()
{
    delete ui;
}
