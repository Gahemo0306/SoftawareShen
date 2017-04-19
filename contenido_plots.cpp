#include "duvaloraction.h"
#include "valoraction.h"
#include "graficos.h"
#include "contenido_plots.h"
#include "ui_contenido_plots.h"
#include "qcustomplot.h"

Contenido_PLOTS::Contenido_PLOTS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contenido_PLOTS)
{
    ui->setupUi(this);
    ui->qcustomplot->setVisible(false);
    ui->qcustomplot->setEnabled(false);
    ui->Utext1->setVisible(false);
    ui->Utext2->setVisible(false);
    ui->Utext3->setVisible(false);
    ui->Utext4->setVisible(false);
    ui->Minimun->setVisible(false);
    ui->Maximun->setVisible(false);
    ui->Increment->setVisible(false);
    ui->k->setVisible(false);
    ui->plot_push->setVisible(false);
    ui->holdon_push->setVisible(false);
    ui->export_push->setVisible(false);
}

Contenido_PLOTS::~Contenido_PLOTS()
{
    delete ui;
}

void Contenido_PLOTS::on_Uniforme_clicked()
{
    RADIOBUTTONS();
}

void Contenido_PLOTS::on_Diverso_clicked()
{
    RADIOBUTTONS();
}

void Contenido_PLOTS::on_StaticradioButton_clicked()
{
    RADIOBUTTONS();
}

void Contenido_PLOTS::on_IncrementradioButton_clicked()
{
    RADIOBUTTONS();
}

void Contenido_PLOTS::RADIOBUTTONS()
{
    ui->Utext1->setVisible(false);
    ui->Utext2->setVisible(false);
    ui->Utext3->setVisible(false);
    ui->Utext4->setVisible(false);
    ui->Minimun->setVisible(false);
    ui->Maximun->setVisible(false);
    ui->Increment->setVisible(false);
    ui->k->setVisible(false);
    ui->plot_push->setVisible(false);
    ui->holdon_push->setVisible(false);
    ui->export_push->setVisible(false);
    bool uniforme = ui->Uniforme->isChecked();
    bool diverso = ui->Diverso->isChecked();
    bool estatico = ui->StaticradioButton->isChecked();
    bool incremento = ui->IncrementradioButton->isChecked();
    if(uniforme == true && estatico == true){
        ui->Utext1->setVisible(true);  //value o maximo
        ui->Utext2->setVisible(false); //minimo
        ui->Utext3->setVisible(false); //incremento
        ui->Utext4->setVisible(false); //k
        ui->Utext1->setText("Value:");
        ui->Minimun->setVisible(true);
        ui->Maximun->setVisible(false);
        ui->Increment->setVisible(false);
        ui->k->setVisible(false);
        ui->plot_push->setVisible(true);
        ui->holdon_push->setVisible(true);
        ui->export_push->setVisible(true);
    }else if(uniforme == true && incremento == true){
        ui->Utext1->setVisible(true);  //value o maximo
        ui->Utext2->setVisible(true); //minimo
        ui->Utext3->setVisible(true); //incremento
        ui->Utext4->setVisible(false); //k
        ui->Utext1->setText("Minimun value:");
        ui->Minimun->setVisible(true);
        ui->Maximun->setVisible(true);
        ui->Increment->setVisible(true);
        ui->k->setVisible(false);
        ui->plot_push->setVisible(true);
        ui->holdon_push->setVisible(true);
        ui->export_push->setVisible(true);
    }else if(diverso == true && estatico == true){
        ui->Utext1->setVisible(true);  //value o maximo
        ui->Utext2->setVisible(false); //minimo
        ui->Utext3->setVisible(false); //incremento
        ui->Utext4->setVisible(true); //k
        ui->Utext1->setText("Value:");
        //ui->Utext2->setText("");
        ui->Minimun->setVisible(true);
        ui->Maximun->setVisible(false);
        ui->Increment->setVisible(false);
        ui->k->setVisible(true);
        ui->plot_push->setVisible(true);
        ui->holdon_push->setVisible(true);
        ui->export_push->setVisible(true);
    }else if(diverso == true && incremento == true){
        ui->Utext1->setVisible(true);
        ui->Utext2->setVisible(true);
        ui->Utext3->setVisible(true);
        ui->Utext4->setVisible(true);
        ui->Utext1->setText("Minimun value:");
        ui->Minimun->setVisible(true);
        ui->Maximun->setVisible(true);
        ui->Increment->setVisible(true);
        ui->k->setVisible(true);
        ui->plot_push->setVisible(true);
        ui->holdon_push->setVisible(true);
        ui->export_push->setVisible(true);
    }else if(uniforme == false || diverso == false){
        ui->Utext1->setVisible(false);
        ui->Utext2->setVisible(false);
        ui->Utext3->setVisible(false);
        ui->Utext4->setVisible(false);
        ui->Minimun->setVisible(false);
        ui->Maximun->setVisible(false);
        ui->Increment->setVisible(false);
        ui->k->setVisible(false);
        ui->plot_push->setVisible(false);
        ui->holdon_push->setVisible(false);
        ui->export_push->setVisible(false);
    }
}

void Contenido_PLOTS::on_plot_push_clicked()
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
    QFile Fil(TABPLOT_FILENAME);
    if (!Fil.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,tr("Error"),tr("Nada no pasa nada"));
        return;
    }
    QDataStream in4(&Fil);
    in4.setVersion(QDataStream::Qt_5_4);
    Tabplot tabvalue;
    in4 >> tabvalue;
    int ventanaplot = tabvalue.gettabvalue();
    Fil.flush();
    Fil.close();
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
    if(ventanaplot == 0){ // es la de curvas compuestas
        Plot_curvascompuestas plot(TS,TE,Wcp);
        QVector<double> CCENTALPIA = plot.getCCENTALPIA();
        QVector<double> CCTEMPERATURAS = plot.getCCTEMPERATURAS();
        ui->qcustomplot->setVisible(true);
        ui->qcustomplot->setEnabled(true);
        ui->qcustomplot->addGraph();
        ui->qcustomplot->graph(0)->setData(CCENTALPIA,CCTEMPERATURAS);
        ui->qcustomplot->xAxis->setLabel("ENTHALPY");
        ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
        ui->qcustomplot->replot();
        QVector<double> CFENTALPIA = plot.getCFENTALPIA();
        QVector<double> CFTEMPERATURAS = plot.getCFTEMPERATURAS();
        ui->qcustomplot->addGraph();
        ui->qcustomplot->graph(1)->setData(CFENTALPIA,CFTEMPERATURAS);
        ui->qcustomplot->graph(0)->rescaleAxes();
        ui->qcustomplot->graph(1)->rescaleAxes(true);
        ui->qcustomplot->replot();
    }else if(ventanaplot == 1){ // es la de las curvas compuestas ajustadas
        double DTmin = ui->Minimun->value();
        Plot_curvascompuestasajustadas plot(TS,TE,Wcp,DTmin);
        QVector<double> CCENTALPIA = plot.getCCENTALPIA();
        QVector<double> CCTEMPERATURAS = plot.getCCTEMPERATURAS();
        ui->qcustomplot->setVisible(true);
        ui->qcustomplot->setEnabled(true);
        ui->qcustomplot->addGraph();
        ui->qcustomplot->graph(0)->setData(CCENTALPIA,CCTEMPERATURAS);
        ui->qcustomplot->xAxis->setLabel("ENTHALPY");
        ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
        ui->qcustomplot->replot();
        QVector<double> CFENTALPIAAJUSTADAS = plot.getCFENTALPIAAJUSTADAS();
        QVector<double> CFTEMPERATURASAJUSTADAS = plot.getCFTEMPERATURASAJUSTADAS();
        ui->qcustomplot->addGraph();
        ui->qcustomplot->graph(1)->setData(CFENTALPIAAJUSTADAS,CFTEMPERATURASAJUSTADAS);
        ui->qcustomplot->graph(0)->rescaleAxes();
        ui->qcustomplot->graph(1)->rescaleAxes(true);
        ui->qcustomplot->replot();
    }

}
