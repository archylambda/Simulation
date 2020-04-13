#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_modelCB_currentIndexChanged(const QString &arg1);

    void on_integratCB_currentIndexChanged(const QString &arg1);

    void on_startSim_clicked();

private:
    Ui::MainWindow *ui;

    QVector<QVector<double>> readResultsByColumns(std::string filename_, int colCount = 4);
    QVector<QVector<double>> getResiduals(std::string filename_,
                                        std::string std_sat_filename_);

    void plot(const QVector<QVector<double>> &data);
    void plotResiduals(const QVector<QVector<double>> &residuals);
    void plotSinus(const QVector<QVector<double>> &data);
};
#endif // MAINWINDOW_H
