#include "mainwindow.h"
#include "collatzcounter.h"
#include "ui_mainwindow.h"
#include <Qthread>
#include <QMessageBox>
#include <thread>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    connect( ui->threadSlider,SIGNAL(valueChanged(int)),ui->threadNumSlider,SLOT(setValue(int)),Qt::ConnectionType::DirectConnection);


    int maxThreads = std::thread::hardware_concurrency();
    ui->threadSlider->setMinimum(1);
    ui->threadSlider->setMaximum(maxThreads);
    ui->threadNumSlider->setMinimum(1);
    ui->threadNumSlider->setMaximum(maxThreads);

    ui->StopButton->setEnabled(false);

    connect(ui->StartButton,&QPushButton::clicked,this,&MainWindow::StartButtonClicked,Qt::ConnectionType::DirectConnection);
    connect(ui->StopButton,&QPushButton::clicked,this,&MainWindow::StopButtonClicked,Qt::ConnectionType::DirectConnection);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartButtonClicked()
{
    ui->textOutput->setText(QString("Calculation is started by user"));
    qDebug() << "Start button clicked";
    long long n = ui->spinBox->value();
    int numThreads = ui->threadSlider->value();

    ui->textOutput->clear();

    ui->StartButton->setEnabled(false);
    ui->StopButton->setEnabled(true);
    CollatzCounter* collatzCounter = new CollatzCounter(n,numThreads);
    QThread* threadUI = new QThread();

    connect(threadUI, &QThread::started, collatzCounter, &CollatzCounter::StartCalc,Qt::ConnectionType::DirectConnection);
    connect(collatzCounter,&CollatzCounter::calcFinished,this,&MainWindow::finishedCalculation);
    connect(collatzCounter, &CollatzCounter::calcFinished, threadUI, &QThread::quit,Qt::ConnectionType::DirectConnection);
    connect(threadUI, &QThread::finished, threadUI, &QObject::deleteLater,Qt::ConnectionType::DirectConnection);
    connect(threadUI, &QThread::finished, collatzCounter, &QObject::deleteLater,Qt::ConnectionType::DirectConnection);

    connect(this,&MainWindow::stopSignal,collatzCounter,&CollatzCounter::StopCalc,Qt::ConnectionType::DirectConnection);
    collatzCounter->moveToThread(threadUI);

    threadUI->start();
}

void MainWindow::StopButtonClicked()
{
    qDebug() << "Stop button clicked";
    emit stopSignal();
    ui->textOutput->setText(QString("Calculation is stopped by user"));
    ui->StartButton->setEnabled(true);
    ui->StopButton->setEnabled(false);
}

void MainWindow::finishedCalculation(long long maxNum, long long maxSteps,int time)
{

    if(maxNum == -1 && maxSteps == -1 && time == - 1)
    {
        QMessageBox::critical(this,"Error","Memory...");
        return;
    }


    ui->textOutput->setText(QString("Number with max steps: %1\nCount of steps: %2\nTime: %3 ms")
                                .arg(maxNum)
                                .arg(maxSteps)
                                .arg(time));

    ui->StartButton->setEnabled(true);
    ui->StopButton->setEnabled(false);
}
