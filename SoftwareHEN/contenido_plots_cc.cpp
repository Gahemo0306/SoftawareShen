#include "contenido_plots_cc.h"
#include "ui_contenido_plots_cc.h"
#include "duvaloraction.h"
#include "graficos.h"
#include "valoraction.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

contenido_plots_cc::contenido_plots_cc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::contenido_plots_cc)
{
    ui->setupUi(this);
    ui->qcustomplot->setVisible(false);
    ui->qcustomplot->setEnabled(false);
}

contenido_plots_cc::~contenido_plots_cc()
{
    delete ui;
}

void contenido_plots_cc::on_radioButton_clicked()
{
    RADIOBUTTONS();
}


void contenido_plots_cc::on_radioButton_2_clicked()
{
    RADIOBUTTONS();
}

void contenido_plots_cc::RADIOBUTTONS()
{
    QFile F(WORKSPACE_FILENAME);
    if (!F.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,tr("Error"),tr("Nada no pasa nada"));
        return;
    }
    QDataStream in2(&F);
    in2.setVersion(QDataStream::Qt_5_4);
    QVector<QVector<double>> prueba;
    int filas = 10; // default
    int columnas = 10; //defalt
    prueba.resize(filas);
    for(int i = 0; i < filas; i++)
    {
        prueba[i].resize(columnas);
    }
    Workspace MATRIZ(prueba);
    in2>> MATRIZ;
    QVector<QVector<double>> Matriz = MATRIZ.getMatriz();
    QVector<double> TS(Matriz.size()),TE(Matriz.size());
    QVector<double> Wcp(Matriz.size()),h(Matriz.size());
    for(int i = 0; i < Matriz.size();i++){
        TS[i] = Matriz[i][0];
        TE[i] = Matriz[i][1];
        Wcp[i] = Matriz[i][2];
        h[i] = Matriz[i][3];
    }
    QFile FileUnidades(UNIDADES_FILENAME);
    if (!FileUnidades.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,tr("Error"),tr("Nada no pasa nada"));
        return;
    }
    QDataStream in3(&FileUnidades);
    in3.setVersion(QDataStream::Qt_5_4);
    Unidades units;
    in3 >> units;
    int UTemp = units.getUTemp();
    int UWcp = units.getUWcp();
    //int Uh = units.getUh();
    bool SI = units.getSI();
    bool SIS = units.getSIS();
    units.ConvertirUnidades(TS,TE,Wcp,SI,SIS,UTemp,UWcp);
    TS = units.getST();
    TE = units.getTT();
    Wcp = units.getCp();
    FileUnidades.flush();
    FileUnidades.close();
    ui->qcustomplot->setVisible(true);
    ui->qcustomplot->setEnabled(true);
    ui->qcustomplot->clearGraphs();
    bool uniforme = ui->radioButton->isChecked();
    bool diverso = ui->radioButton_2->isChecked();
    if(uniforme == true){
        Plot_curvascompuestas plot(TS,TE,Wcp);
        QVector<double> CCENTALPIA = plot.getCCENTALPIA();
        QVector<double> CCTEMPERATURAS = plot.getCCTEMPERATURAS();
        ui->qcustomplot->setVisible(true);
        ui->qcustomplot->setEnabled(true);
        ui->qcustomplot->addGraph();
        ui->qcustomplot->graph(0)->setPen(QPen(Qt::red));
        ui->qcustomplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
        ui->qcustomplot->graph(0)->setData(CCENTALPIA,CCTEMPERATURAS);
        ui->qcustomplot->xAxis->setLabel("ENTHALPY");
        ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
        ui->qcustomplot->replot();
        QVector<double> CFENTALPIA = plot.getCFENTALPIA();
        QVector<double> CFTEMPERATURAS = plot.getCFTEMPERATURAS();
        ui->qcustomplot->addGraph();
        ui->qcustomplot->graph(1)->setPen(QPen(Qt::blue));
        ui->qcustomplot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
        ui->qcustomplot->graph(1)->setData(CFENTALPIA,CFTEMPERATURAS);
        ui->qcustomplot->graph(0)->rescaleAxes();
        ui->qcustomplot->graph(1)->rescaleAxes(true);
        ui->qcustomplot->replot();
    }else if(diverso == true){

    }
}
