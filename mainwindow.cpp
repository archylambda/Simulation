#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "integrator.h"
#include "sinus.h"
#include "earth.h"
#include "earthsatellite.h"
#include <iostream>
#include <sstream>
#include "moon.h"
#include "const.h"
#include "moondecorator.h"
#include "sundecorator.h"

//debug includes
#include <time.h>
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
        ui->moonDecoratorCB->setCheckState(Qt::Unchecked);
        ui->sunDecoratorCB->setCheckState(Qt::Unchecked);
        ui->resudialCB->setCheckState(Qt::Unchecked);
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

QVector<QVector<double>> MainWindow::readResultsByColumns(std::string filename_, int colCount){
    QVector<QVector<double>> res;

    for (int i = 0; i < colCount; ++i){
        QVector<double> col;
        res.push_back(col);
    }

    ifstream file(filename_);
    string s;
    if (file){ // вызов метода is_open()
        while(getline(file, s)){
            stringstream ss(s);
            for(QVector<double> &vec: res){
                long double tmp;
                ss >> tmp;
                vec.push_back(tmp);
            }
        }
    }
    else {
        cout << "Файл не открыт!\n\n" << endl;
    }

    return res;
}

QVector<QVector<double>> MainWindow::getResiduals(std::string filename_,
                                      std::string std_sat_filename_){

    QVector<QVector<double>> curVecs = readResultsByColumns(filename_);
    QVector<QVector<double>> stdVecs = readResultsByColumns(std_sat_filename_);

    // возвращает вектор векторов :
    // {{вектор времени}, {невязки по x}, {невязки по y}, {невязки по z} }
    QVector<QVector<double>> res;
    res.push_back(curVecs[0]);

    unsigned int size = curVecs[1].size();
    QVector<double> diffX(size), diffY(size), diffZ(size);

    for(unsigned int i = 0; i < size; i++){
        diffX[i] = abs(curVecs[1][i] - stdVecs[1][i]);
        diffY[i] = abs(curVecs[2][i] - stdVecs[2][i]);
        diffZ[i] = abs(curVecs[3][i] - stdVecs[3][i]);
    }

    res.push_back(diffX);
    res.push_back(diffY);
    res.push_back(diffZ);

    return res;
}

void MainWindow::plotResiduals(const QVector<QVector<double>> &residuals){

    ui->customPlot->plotLayout()->clear();

    QCPAxisRect *firstAxisRect = new QCPAxisRect(ui->customPlot);
    QCPAxisRect *secondAxisRect = new QCPAxisRect(ui->customPlot);
    QCPAxisRect *thirdAxisRect = new QCPAxisRect(ui->customPlot);

    ui->customPlot->plotLayout()->addElement(0, 0, firstAxisRect);
    ui->customPlot->plotLayout()->addElement(1, 0, secondAxisRect);
    ui->customPlot->plotLayout()->addElement(2, 0, thirdAxisRect);

    QList<QCPAxis*> allAxes;

    allAxes << firstAxisRect->axes() << secondAxisRect->axes() << thirdAxisRect->axes();
    foreach (QCPAxis *axis, allAxes)
    {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
    }

    QCPGraph *firstGraph = ui->customPlot->addGraph(firstAxisRect->axis(QCPAxis::atBottom), firstAxisRect->axis(QCPAxis::atLeft));
    // create graph and assign data to it:
    firstGraph->setLineStyle(QCPGraph::lsNone);
    firstGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    firstAxisRect->axis(QCPAxis::atLeft)->setLabel("X, km");
    firstGraph->setData(residuals[0], residuals[1]);
    firstGraph->rescaleAxes(true);


    QCPGraph *secondGraph = ui->customPlot->addGraph(secondAxisRect->axis(QCPAxis::atBottom), secondAxisRect->axis(QCPAxis::atLeft));
    // create graph and assign data to it:
    secondGraph->setLineStyle(QCPGraph::lsNone);
    secondGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    secondAxisRect->axis(QCPAxis::atLeft)->setLabel("Y, km");
    secondGraph->setData(residuals[0], residuals[2]);
    secondGraph->rescaleAxes(true);


    QCPGraph *thirdGraph = ui->customPlot->addGraph(thirdAxisRect->axis(QCPAxis::atBottom), thirdAxisRect->axis(QCPAxis::atLeft));
    // create graph and assign data to it:
    thirdGraph->setLineStyle(QCPGraph::lsNone);
    thirdGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    thirdAxisRect->axis(QCPAxis::atLeft)->setLabel("Z, km");
    thirdAxisRect->axis(QCPAxis::atBottom)->setLabel("t, sec");
    thirdGraph->setData(residuals[0], residuals[3]);
    thirdGraph->rescaleAxes(true);



    ui->customPlot->replot();
}

void MainWindow::plotSinus(const QVector<QVector<double>> &data){

//    ui->customPlot->plotLayout()->clear();
//    // create graph and assign data to it:
//    ui->customPlot->addGraph();
//    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
//    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
//    ui->customPlot->graph(0)->setData(data[0], data[1]);
//    ui->customPlot->graph(0)->rescaleAxes(true);
//    // give the axes some labels:
//    ui->customPlot->xAxis->setLabel("t, c");
//    ui->customPlot->yAxis->setLabel("X");
//    ui->customPlot->replot();

    ui->customPlot->plotLayout()->clear();

    QCPAxisRect *firstAxisRect = new QCPAxisRect(ui->customPlot);

    ui->customPlot->plotLayout()->addElement(0, 0, firstAxisRect);

    QList<QCPAxis*> allAxes;

    allAxes << firstAxisRect->axes();
    foreach (QCPAxis *axis, allAxes)
    {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
    }

    QCPGraph *firstGraph = ui->customPlot->addGraph(firstAxisRect->axis(QCPAxis::atBottom), firstAxisRect->axis(QCPAxis::atLeft));
    // create graph and assign data to it:
    firstGraph->setLineStyle(QCPGraph::lsNone);
    firstGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    firstAxisRect->axis(QCPAxis::atBottom)->setLabel("t, sec");
    firstAxisRect->axis(QCPAxis::atLeft)->setLabel("X");
    firstGraph->setData(data[0], data[1]);
    firstGraph->rescaleAxes(true);

    ui->customPlot->replot();

}

void MainWindow::plot(const QVector<QVector<double>> &data){

    ui->customPlot->plotLayout()->clear();

    QCPAxisRect *firstAxisRect = new QCPAxisRect(ui->customPlot);
    QCPAxisRect *secondAxisRect = new QCPAxisRect(ui->customPlot);
    QCPAxisRect *thirdAxisRect = new QCPAxisRect(ui->customPlot);

    ui->customPlot->plotLayout()->addElement(0, 0, firstAxisRect);
    ui->customPlot->plotLayout()->addElement(1, 0, secondAxisRect);
    ui->customPlot->plotLayout()->addElement(2, 0, thirdAxisRect);

    QList<QCPAxis*> allAxes;

    allAxes << firstAxisRect->axes() << secondAxisRect->axes() << thirdAxisRect->axes();
    foreach (QCPAxis *axis, allAxes)
    {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
    }

    QCPGraph *firstGraph = ui->customPlot->addGraph(firstAxisRect->axis(QCPAxis::atBottom), firstAxisRect->axis(QCPAxis::atLeft));
    // create graph and assign data to it:
    firstGraph->setLineStyle(QCPGraph::lsNone);
    firstGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    firstAxisRect->axis(QCPAxis::atBottom)->setLabel("X, km");
    firstAxisRect->axis(QCPAxis::atLeft)->setLabel("Y, km");
    firstGraph->setData(data[1], data[2]);
    firstGraph->rescaleAxes(true);


    QCPGraph *secondGraph = ui->customPlot->addGraph(secondAxisRect->axis(QCPAxis::atBottom), secondAxisRect->axis(QCPAxis::atLeft));
    // create graph and assign data to it:
    secondGraph->setLineStyle(QCPGraph::lsNone);
    secondGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    secondAxisRect->axis(QCPAxis::atBottom)->setLabel("X, km");
    secondAxisRect->axis(QCPAxis::atLeft)->setLabel("Z, km");
    secondGraph->setData(data[1], data[3]);
    secondGraph->rescaleAxes(true);


    QCPGraph *thirdGraph = ui->customPlot->addGraph(thirdAxisRect->axis(QCPAxis::atBottom), thirdAxisRect->axis(QCPAxis::atLeft));
    // create graph and assign data to it:
    thirdGraph->setLineStyle(QCPGraph::lsNone);
    thirdGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    thirdAxisRect->axis(QCPAxis::atBottom)->setLabel("Y, km");
    thirdAxisRect->axis(QCPAxis::atLeft)->setLabel("Z, km");
    thirdGraph->setData(data[2], data[3]);
    thirdGraph->rescaleAxes(true);



    ui->customPlot->replot();
}


void MainWindow::on_startSim_clicked()
{

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

        bool RESUD_FLAG = ui->resudialCB->isChecked();

        TModel* model;
        long double step = ui->stepEdit->text().toDouble(),
                    endTime = ui->timeEdit->text().toDouble();
        switch(ui->modelCB->currentIndex())
        {
        case 0: // Sinus
            {
                model = new TSinus(filename, step, endTime);
                break;
            }
        case 1: //Satellite
            {
                TVector keplerParams(6);
                keplerParams[0] = ui->aEdit->text().toDouble();
                keplerParams[1] = ui->eEdit->text().toDouble();
                keplerParams[2] = ui->OmegaEdit->text().toDouble();
                keplerParams[3] = ui->iEdit->text().toDouble();
                keplerParams[4] = ui->omegaEdit->text().toDouble();
                keplerParams[5] = ui->nuEdit->text().toDouble();

                model = new TEarthSatellite(filename, step, endTime, keplerParams);
                if (ui->moonDecoratorCB->isChecked()){
                    model = new TMoonDecorator(model);
                }
                if (ui->sunDecoratorCB->isChecked()){
                    model = new TSunDecorator(model);
                }

                if (RESUD_FLAG){
                    TModel* standSat = new TEarthSatellite(fstandSat, step, endTime, keplerParams);

                    integrator->Run(standSat);
                    standSat->clearResult();

                    delete standSat;
                }

                break;
            }
        case 2: //Earth
            {
                model = new TEarth(filename, step, endTime);
                break;
            }
        }


        integrator->Run(model);
        model->clearResult();

        if (RESUD_FLAG){
          QVector<QVector<double>> residuals = getResiduals(filename, fstandSat);
          plotResiduals(residuals);
        }
        else if (ui->modelCB->currentIndex() == 0){
            QVector<QVector<double>> data = readResultsByColumns(filename, 2);
            plotSinus(data);
        }
        else {
            QVector<QVector<double>> data = readResultsByColumns(filename);
            plot(data);
        }
        delete integrator;
        delete model;
}

