#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytablemodel.h"
#include "plotwidget.h"
#include <algorithm>

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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    int elemWidth = (size().width() - 30) / 2;
    int elemHeight = size().height() - 40;
    int plotDimension = std::min(elemWidth, elemHeight);

    ui->tableView->resize(elemWidth, elemHeight - 30);

    m_plotWidget->move(20 + elemWidth, (size().height() - plotDimension) / 2);
    m_plotWidget->resize(plotDimension, plotDimension);
}
