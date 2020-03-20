#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <integrator.h>
#include <sinus.h>
#include <earth.h>
#include <earthsatellite.h>
#include <iostream>
#include <sstream>
#include <moon.h>
#include <moondecorator.h>
#include <sundecorator.h>
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

    TModel* sat = new TEarthSatellite();

    TModel* wrapped_by_Moon = new TMoonDecorator(sat);
    TModel* wrapped_by_Sun = new TSunDecorator(wrapped_by_Moon);

    Integrator->Run(wrapped_by_Sun);

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
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    ui->customPlot->graph(0)->setData(t, x);
    ui->customPlot->graph(0)->rescaleAxes(true);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("X");
    ui->customPlot->yAxis->setLabel("Y");
    ui->customPlot->replot();

    delete wrapped_by_Sun;
    delete wrapped_by_Moon;
    delete sat;
    delete Integrator;
}
