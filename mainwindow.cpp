#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    qRegisterMetaType<QList<int>>("QList<int>");
    ui->setupUi(this);
    this->centralWidget()->setContentsMargins(0,0,0,0);
    setWindowTitle("DEMONSTRATION OF SORTING ALGORITHMS");
    ui->labelExecTime->setText("Execut_Time: 00 milli_sec   ");
    sThread=new SortingThread(this);
    ui->lyPainter->addWidget(&paintwidget);
    ui->comboAlgos->addItems(sThread->getAlgos());
    sThread->setAlg(ui->comboAlgos->currentText());
    paintwidget.setSizePolicy(QSizePolicy::Policy::Expanding,QSizePolicy::Policy::Expanding);
    paintwidget.setPenWidth(6);
    paintwidget.update();
    connect(sThread,SIGNAL(NumbersChanged(QList<int>, QList<int>)),this,SLOT(onNumbersChanged(QList<int>, QList<int>)));
    connect(sThread,SIGNAL(SortingFinished()),this,SLOT(onSortingFinished()));
    connect(ui->comboAlgos,SIGNAL(currentTextChanged(QString)),this,SLOT(onChangeAlgo(QString)));
    sThread->GenerateNumbers();
}

void MainWindow::onNumberSizeChange(int newSize)
{
    paintwidget.setPenWidth(this->width()/newSize);
    paintwidget.update();
}

MainWindow::~MainWindow()
{
    sThread->quit();
    delete ui;
}
void MainWindow::onNumbersChanged(QList<int> nums, QList<int> ind)
{
    paintwidget.SetPaintData(nums,ind);
    paintwidget.update();
}

void MainWindow::onSortingFinished()
{
    ui->labelExecTime->setText("Execut_Time:"+QString::number(execTimer.elapsed())+"milli_sec");
    paintwidget.setAnim(false);
    paintwidget.update();
    isRunning=false;
    ui->buttonShuffle->setDisabled(false);
    ui->buttonStart->setText("Start");
}

void MainWindow::onChangeAlgo(QString algName)
{
    sThread->setAlg(algName);
}

void MainWindow::on_buttonStart_pressed()
{
    if (!isRunning)
    {
        isRunning=true;
        ui->buttonStart->setText("Stop");
        ui->buttonShuffle->setDisabled(true);
        paintwidget.setAnim(true);
        paintwidget.resetColor();
        execTimer.start();
        sThread->start();
    }
    else
    {
        isRunning=false;
        paintwidget.setAnim(false);
        ui->buttonShuffle->setDisabled(false);
        paintwidget.resetColor();
        ui->buttonStart->setText("Start");
        sThread->terminate();
    }
}

void MainWindow::on_buttonShuffle_pressed()
{
    paintwidget.resetColor();
    sThread->GenerateNumbers();
}
