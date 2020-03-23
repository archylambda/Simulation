#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <integrator.h>
#include <sinus.h>
#include <earth.h>
#include <earthsatellite.h>
#include <iostream>
#include <sstream>
#include <moon.h>
#include <const.h>
#include <moondecorator.h>
#include <sundecorator.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QStringList models = { "Sinus", "Satellite", "Earth"};
    QStringList integrators = { "Eiler", "Runge-Kutta", "Dormand-Prince"};
    ui->modelCB->addItems(models);
    ui->modelCB->setCurrentIndex(0);
    ui->integratCB->addItems(integrators);
    ui->integratCB->setCurrentIndex(0);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_modelCB_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Satellite"){
        ui->satGB->setEnabled(true);
    } else {
        ui->satGB->setEnabled(false);
    }
}

void MainWindow::on_integratCB_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Dormand-Prince"){
        ui->epsLB->setEnabled(true);
        ui->epsEdit->setEnabled(true);
        ui->stepLB->setText("Sampling increment");
    } else {
        ui->epsLB->setEnabled(false);
        ui->epsEdit->setEnabled(false);
        ui->stepLB->setText("Step");
    }
}

void MainWindow::on_startSim_clicked()
{

    //    TIntegrator* Integrator = new TRungeKuttaIntegrator();

    //    TModel* sat = new TEarthSatellite();

    //    TModel* wrapped_by_Moon = new TMoonDecorator(sat);
    //    TModel* wrapped_by_Sun = new TSunDecorator(wrapped_by_Moon);

    //    Integrator->Run(wrapped_by_Sun);
        TIntegrator* integrator;

        switch (ui->integratCB->currentIndex())
        {
        case 0: // Eiler
            integrator = new TEilerIntegrator();
            break;
        case 1: // Runge-Kutta
            integrator = new TRungeKuttaIntegrator();
            break;
        case 2: // Dorman-Prince
            integrator = new TDormandPrinceIntegrator();
            integrator->setPrecision(ui->epsEdit->text().toDouble());
            break;
        default: // na vsyakyi
            integrator = new TRungeKuttaIntegrator();
            break;
        }

        TModel* model;
        switch(ui->modelCB->currentIndex())
        {
        case 0: // Sinus
            {
                model = new TSinus();
                model->setSamplingIncrement(ui->stepEdit->text().toDouble());
                model->setEndTime(ui->timeEdit->text().toDouble());
                break;
            }
        case 1: //
            {
                TVector keplerParams(6);
                keplerParams[0] = ui->aEdit->text().toDouble();
                keplerParams[1] = ui->eEdit->text().toDouble();
                keplerParams[2] = ui->OmegaEdit->text().toDouble();
                keplerParams[3] = ui->iEdit->text().toDouble();
                keplerParams[4] = ui->omegaEdit->text().toDouble();
                keplerParams[5] = ui->nuEdit->text().toDouble();

                model = new TEarthSatellite(keplerParams);
                model->setSamplingIncrement(ui->stepEdit->text().toDouble());
                model->setEndTime(ui->timeEdit->text().toDouble());
                break;
            }
        case 2:
            {
                model = new TEarth();
                model->setSamplingIncrement(ui->stepEdit->text().toDouble());
                model->setEndTime(ui->timeEdit->text().toDouble());
                break;
            }
        }

        integrator->Run(model);

        QVector<double> t, x;
        ifstream file(filename);
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

    //    delete wrapped_by_Sun;
    //    delete wrapped_by_Moon;
    //    delete sat;
        file.close();
        delete model;
        delete integrator;
}
