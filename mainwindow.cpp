#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytablemodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_model = new MyTableModel();
    ui->tableView->setModel(m_model);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_model;
}

void MainWindow::on_actionInsert_row_triggered()
{
    m_model->insertRow();
}
