#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <integrator.h>
#include <sinus.h>
#include <earthsatellite.h>
#include <iostream>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    TIntegrator* Integrator = new TRungeKuttaIntegrator();
    Integrator->setPrecision(1e-6);

    TModel* testModel = new TEarthSatellite();

    Integrator->Run(testModel);

    QVector<double> t, x;
    ifstream file("result.txt");
    string s;
    if (file){ // вызов метода is_open()
        while(getline(file, s)){
            stringstream ss(s);
            long double tmp = 0;
            ss >> tmp;
            t.push_back(tmp);
            ss >> tmp;
            x.push_back(tmp);
        }
    }
    else
    {
        cout << "Файл не открыт!\n\n" << endl;
    }

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(t, x);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("t");
    ui->customPlot->yAxis->setLabel("x");
    ui->customPlot->xAxis->setRange(0, 50);
    ui->customPlot->replot();

    delete testModel;
    delete Integrator;
}
