#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytablemodel.h"
#include "plotwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_model = new MyTableModel();
    ui->tableView->setModel(m_model);

    m_plotWidget = new PlotWidget(m_model, this);
    m_plotWidget->move(410, 100);
    m_plotWidget->resize(390, 390);

    connect(m_model, SIGNAL(layoutChanged()),
            m_plotWidget, SLOT(repaint()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_model;
    delete m_plotWidget;
}

void MainWindow::on_actionInsert_row_triggered()
{
    m_model->insertRow();
}
