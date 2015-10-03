#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytablemodel.h"
#include "plotwidget.h"
#include <algorithm>
#include "aboutdialog.h"
#include "documentstate.h"

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

    m_docState = new DocumentState();

    connect(m_model, SIGNAL(layoutChanged()),
            m_docState, SLOT(modified()));

    connect(m_docState, SIGNAL(loadData(QString)),
            m_model, SLOT(loadData(QString)));

    connect(m_docState, SIGNAL(saveData(QString)),
            m_model, SLOT(saveData(QString)));

    connect(m_docState, SIGNAL(canSaveChanged(bool)),
            this, SLOT(setCanSave(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_model;
    delete m_plotWidget;
    delete m_docState;
}

void MainWindow::setCanSave(bool canSave)
{
    ui->actionSave->setEnabled(canSave);
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

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog about;
    about.setModal(true);
    about.exec();
}

void MainWindow::on_actionNew_triggered()
{
    m_docState->newFile();
}

void MainWindow::on_actionOpen_triggered()
{
    m_docState->open();
}

void MainWindow::on_actionSave_triggered()
{
    m_docState->save();
}

void MainWindow::on_actionSave_as_triggered()
{
    m_docState->saveAs();
}
