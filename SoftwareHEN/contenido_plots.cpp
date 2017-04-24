#include "duvaloraction.h"
#include "valoraction.h"
#include "graficos.h"
#include "qcustomplot.h"
#include "contenido_plots.h"
#include "ui_contenido_plots.h"

Contenido_PLOTS::Contenido_PLOTS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contenido_PLOTS)
{
    ui->setupUi(this);
    ui->groupBox_3->setVisible(false);
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
    ui->groupBox_3->setVisible(false);
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
        ui->groupBox_3->setVisible(true);
        ui->Utext4->setVisible(false); //k
        ui->Utext1->setVisible(true);  //minimo
        ui->Utext2->setVisible(false); //maximo
        ui->Utext3->setVisible(false); //incremento
        ui->Utext1->setText("Value:");
        ui->Minimun->setVisible(true);
        ui->Maximun->setVisible(false);
        ui->Increment->setVisible(false);
        ui->k->setVisible(false);
        ui->plot_push->setVisible(true);
        ui->holdon_push->setVisible(true);
        ui->export_push->setVisible(true);
    }else if(uniforme == true && incremento == true){
        ui->groupBox_3->setVisible(true);
        ui->Utext1->setVisible(true);  //minmo
        ui->Utext2->setVisible(true); //maximo
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
        ui->groupBox_3->setVisible(true);
        ui->Utext1->setVisible(true);  //minimo
        ui->Utext2->setVisible(false); //maximo
        ui->Utext3->setVisible(false); //incremento
        ui->Utext4->setVisible(true); //k
        ui->Utext1->setText("Value:");
        ui->Minimun->setVisible(true);
        ui->Maximun->setVisible(false);
        ui->Increment->setVisible(false);
        ui->k->setVisible(true);
        ui->plot_push->setVisible(true);
        ui->holdon_push->setVisible(true);
        ui->export_push->setVisible(true);
    }else if(diverso == true && incremento == true){
        ui->groupBox_3->setVisible(true);
        ui->Utext1->setVisible(true);//minimo
        ui->Utext2->setVisible(true);//maximo
        ui->Utext3->setVisible(true);//incremento
        ui->Utext4->setVisible(true);//k
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
    bool uniforme = ui->Uniforme->isChecked();
    bool diverso = ui->Diverso->isChecked();
    bool estatico = ui->StaticradioButton->isChecked();
    bool incremento = ui->IncrementradioButton->isChecked();
    plot(ventanaplot,uniforme,diverso,estatico,incremento,TS,TE,Wcp);
}

void Contenido_PLOTS::plot(int ventanaplot,bool uniforme,bool diverso,bool estatico,bool incremento,
                           QVector<double> TS, QVector<double> TE, QVector<double> Wcp)
{
    if(ventanaplot == 1){ // es la de las curvas compuestas ajustadas
        ui->qcustomplot->setVisible(true);
        ui->qcustomplot->setEnabled(true);
        ui->qcustomplot->clearGraphs();
        if(uniforme == true && estatico == true){
            double DTmin = ui->Minimun->value();
            Plot_curvascompuestasajustadas plot(TS,TE,Wcp,DTmin);
            QVector<double> CCENTALPIA = plot.getCCENTALPIA();
            QVector<double> CCTEMPERATURAS = plot.getCCTEMPERATURAS();
            ui->qcustomplot->addGraph();
            ui->qcustomplot->graph(0)->setPen(QPen(Qt::red));
            ui->qcustomplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
            ui->qcustomplot->graph(0)->setData(CCENTALPIA,CCTEMPERATURAS);
            ui->qcustomplot->xAxis->setLabel("ENTHALPY");
            ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
            ui->qcustomplot->replot();
            QVector<double> CFENTALPIAAJUSTADAS = plot.getCFENTALPIAAJUSTADAS();
            QVector<double> CFTEMPERATURASAJUSTADAS = plot.getCFTEMPERATURASAJUSTADAS();
            ui->qcustomplot->addGraph();
            ui->qcustomplot->graph(1)->setPen(QPen(Qt::blue));
            ui->qcustomplot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
            ui->qcustomplot->graph(1)->setData(CFENTALPIAAJUSTADAS,CFTEMPERATURASAJUSTADAS);
            ui->qcustomplot->graph(0)->rescaleAxes();
            ui->qcustomplot->graph(1)->rescaleAxes(true);
            ui->qcustomplot->replot();
        }else if(uniforme == true && incremento == true){
            double Minimo = ui->Minimun->value();
            double Maximo = ui->Maximun->value();
            double Incremento = ui->Increment->value();
            double Iteraciones =(Maximo-Minimo)/Incremento;
            double DTmin = Minimo;
            int j=0;
            Plot_curvascompuestasajustadas plot(TS,TE,Wcp,DTmin);
            QVector<double> CCENTALPIA = plot.getCCENTALPIA();
            QVector<double> CCTEMPERATURAS = plot.getCCTEMPERATURAS();
            ui->qcustomplot->addGraph();
            ui->qcustomplot->graph(j)->setPen(QPen(Qt::red));
            ui->qcustomplot->graph(j)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
            ui->qcustomplot->graph(j)->setData(CCENTALPIA,CCTEMPERATURAS);
            ui->qcustomplot->graph(j)->rescaleAxes();
            for(int i = 0; i <= Iteraciones ; i++){
                j++;
                Plot_curvascompuestasajustadas plot(TS,TE,Wcp,DTmin);
                QVector<double> CFENTALPIAAJUSTADAS = plot.getCFENTALPIAAJUSTADAS();
                QVector<double> CFTEMPERATURASAJUSTADAS = plot.getCFTEMPERATURASAJUSTADAS();
                ui->qcustomplot->addGraph();
                ui->qcustomplot->graph(j)->setPen(QPen(Qt::blue));
                ui->qcustomplot->graph(j)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
                ui->qcustomplot->graph(j)->setData(CFENTALPIAAJUSTADAS,CFTEMPERATURASAJUSTADAS);
                ui->qcustomplot->graph(j)->rescaleAxes(true);
                DTmin = DTmin + Incremento;
            }
            ui->qcustomplot->xAxis->setLabel("ENTHALPY");
            ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
            ui->qcustomplot->replot();
        }else if(diverso == true && estatico == true){
        }else if(diverso == true && incremento == true){
        }
    }else if(ventanaplot == 2){ // GRAN CURVA COMPUESTA
        ui->qcustomplot->setVisible(true);
        ui->qcustomplot->setEnabled(true);
        ui->qcustomplot->clearGraphs();
        if(uniforme == true && estatico == true){
            double DTmin = ui->Minimun->value();
            Plot_grancurvacompuesta plot(TS,TE,Wcp,DTmin);
            QVector<double> GCENTALPIA = plot.getGCENTALPIA();
            QVector<double> GCTEMPERATURAS = plot.getGCTEMPERATURAS();
            ui->qcustomplot->addGraph();
            ui->qcustomplot->graph(0)->setPen(QPen(Qt::blue));
            ui->qcustomplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
            ui->qcustomplot->graph(0)->setLineStyle(QCPGraph::lsLine);
            ui->qcustomplot->graph(0)->setData(GCENTALPIA,GCTEMPERATURAS);
//            ui->qcustomplot->xAxis->setLabel("ENTHALPY");
//            ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
            double minX = *std::min_element(GCENTALPIA.begin(),GCENTALPIA.end());
            double maxX = *std::max_element(GCENTALPIA.begin(),GCENTALPIA.end());
            double minY = *std::min_element(GCTEMPERATURAS.begin(),GCTEMPERATURAS.end());
            double maxY = *std::max_element(GCTEMPERATURAS.begin(),GCTEMPERATURAS.end());
            ui->qcustomplot->xAxis->setRange(minX-5,maxX+5);
            ui->qcustomplot->yAxis->setRange(minY-5,maxY+5);
            ui->qcustomplot->replot();
        }else if(uniforme == true && incremento == true){
            double Minimo = ui->Minimun->value();
            double Maximo = ui->Maximun->value();
            double Incremento = ui->Increment->value();
            double Iteraciones =(Maximo-Minimo)/Incremento;
            double DTmin = Minimo;
            for(int i = 0; i <= Iteraciones ; i++){
                 Plot_grancurvacompuesta plot(TS,TE,Wcp,DTmin);
                 QVector<double> GCENTALPIA = plot.getGCENTALPIA();
                 QVector<double> GCTEMPERATURAS = plot.getGCTEMPERATURAS();
                 ui->qcustomplot->addGraph();
                 ui->qcustomplot->graph(i)->setPen(QPen(Qt::blue));
                 ui->qcustomplot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
                 ui->qcustomplot->graph(i)->setLineStyle(QCPGraph::lsLine);
                 ui->qcustomplot->graph(i)->setData(GCTEMPERATURAS,GCENTALPIA);
                 ui->qcustomplot->graph(i)->rescaleAxes();
                 ui->qcustomplot->graph(i)->rescaleAxes(true);
                 DTmin = DTmin + Incremento;
            }
            ui->qcustomplot->replot();
        }else if(diverso == true && estatico == true){
        }else if(diverso == true && incremento == true){
        }
    }
}
