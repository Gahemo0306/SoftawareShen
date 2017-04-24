#include <algorithm>
#include <numeric>
#include "duvaloraction.h"
#include "valoraction.h"
#include "graficos.h"
#include "qcustomplot.h"
#include "contenido_plots_area.h"
#include "ui_contenido_plots_area.h"

contenido_plots_area::contenido_plots_area(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::contenido_plots_area)
{
    ui->setupUi(this);
    ui->qcustomplot->setVisible(false);
    ui->qcustomplot->setEnabled(false);
    ui->groupBox_3->setVisible(false);
    ui->groupBox_4->setVisible(false);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->comboBoxF->setVisible(false);
    ui->comboBoxT->setVisible(false);
    ui->labelK->setVisible(false);
    ui->labelMin->setVisible(false);
    ui->labelMax->setVisible(false);
    ui->labelInc->setVisible(false);
    ui->SBk->setVisible(false);
    ui->SBmin->setVisible(false);
    ui->SBmax->setVisible(false);
    ui->SBinc->setVisible(false);
    ui->labelType->setVisible(false);
    ui->TypeDesign->setVisible(false);
    ui->labelAux->setVisible(false);
    ui->Services->setVisible(false);
    ui->Plot->setVisible(false);
    ui->Holdon->setVisible(false);
    ui->Export->setVisible(false);
}

contenido_plots_area::~contenido_plots_area()
{
    delete ui;
}

void contenido_plots_area::on_Uniform_clicked()
{
    RADIOBUTTONS();
}

void contenido_plots_area::on_Diverse_clicked()
{
    RADIOBUTTONS();
}

void contenido_plots_area::on_Static_clicked()
{
    RADIOBUTTONS();
}

void contenido_plots_area::on_Increment_clicked()
{
    RADIOBUTTONS();
}

void contenido_plots_area::on_Plot_clicked()
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
    int ncols;
    ncols = ui->Services->columnCount();
    QVector<double> Enfriamento,Calentamiento;
    Enfriamento.resize(ncols);
    Calentamiento.resize(ncols);
    for (int j = 0; j < ncols ; j++){
        Calentamiento[j] = ui->Services->item(0,j)->text().toDouble();
        Enfriamento[j] = ui->Services->item(1,j)->text().toDouble();
    }
    bool uniforme = ui->Uniform->isChecked();
    bool diverso = ui->Diverse->isChecked();
    bool estatico = ui->Static->isChecked();
    bool incremento = ui->Increment->isChecked();
    int CTo,CCo;
    if (ui->TypeDesign->currentIndex() == 1){
        CTo = 1;
        CCo = 0;
    }else if(ui->TypeDesign->currentIndex() == 2){
        CTo = 0;
        CCo = 1;
    }
    Plot(ventanaplot,uniforme,diverso,estatico,incremento,TS,TE,Wcp,h,Enfriamento,Calentamiento,CTo,CCo);
}

void contenido_plots_area::RADIOBUTTONS()
{
    QFile FileUnidades(UNIDADES_FILENAME);
    if (!FileUnidades.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,tr("Error"),tr("Nada no pasa nada"));
        return;
    }
    QDataStream in3(&FileUnidades);
    in3.setVersion(QDataStream::Qt_5_4);
    Unidades units;
    in3 >> units;
    bool SI = units.getSI();
    bool SIS = units.getSIS();
    FileUnidades.flush();
    FileUnidades.close();
    ui->groupBox_3->setVisible(false);
    ui->groupBox_4->setVisible(false);
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->comboBoxF->setVisible(false);
    ui->comboBoxT->setVisible(false);
    ui->labelK->setVisible(false);
    ui->labelMin->setVisible(false);
    ui->labelMax->setVisible(false);
    ui->labelInc->setVisible(false);
    ui->SBk->setVisible(false);
    ui->SBmin->setVisible(false);
    ui->SBmax->setVisible(false);
    ui->SBinc->setVisible(false);
    ui->labelType->setVisible(false);
    ui->TypeDesign->setVisible(false);
    ui->labelAux->setVisible(false);
    ui->Services->setVisible(false);
    ui->Plot->setVisible(false);
    ui->Holdon->setVisible(false);
    ui->Export->setVisible(false);
    bool uniforme = ui->Uniform->isChecked();
    bool diverso = ui->Diverse->isChecked();
    bool estatico = ui->Static->isChecked();
    bool incremento = ui->Increment->isChecked();
    if(uniforme == true && estatico == true){
        ui->groupBox_3->setVisible(true);
        ui->groupBox_4->setVisible(true);
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->comboBoxF->setVisible(true);
        ui->comboBoxT->setVisible(true);
        ui->labelK->setVisible(false);
        ui->labelMin->setVisible(true);
        ui->labelMax->setVisible(false);
        ui->labelInc->setVisible(false);
        ui->labelMin->setText("Value:");
        ui->SBk->setVisible(false);
        ui->SBmin->setVisible(true);
        ui->SBmax->setVisible(false);
        ui->SBinc->setVisible(false);
        ui->Plot->setVisible(true);
        ui->Holdon->setVisible(true);
        ui->Export->setVisible(true);
        ui->labelType->setVisible(true);
        ui->TypeDesign->setVisible(true);
        ui->labelAux->setVisible(true);
        ui->Services->setVisible(true);
        if(SI == true){
            QStringList Lista1,Lista2;
            ui->comboBoxT->clear();
            ui->comboBoxF->clear();
            Lista1 << "Select one..." << "Kelvin (°K)" << "Farenheit (°F)" << "Celsius (°C)" << "Ranking (°R)";
            Lista2 << "Select one..." << "Btu/hr ft^2 °F" << "CHU/hr ft^2 °F";
            ui->comboBoxT->addItems(Lista1);
            ui->comboBoxF->addItems(Lista2);
        }else if(SIS == true){
            QStringList Lista1,Lista2;
            ui->comboBoxT->clear();
            ui->comboBoxF->clear();
            Lista1 << "Select one..." << "Kelvin (°K)" << "Farenheit (°F)" << "Celsius (°C)" << "Ranking (°R)";
            Lista2 << "Select one..." << "W/m^2 °K" << "W/m^2 °C";
            ui->comboBoxT->addItems(Lista1);
            ui->comboBoxF->addItems(Lista2);
        }
    }else if(uniforme == true && incremento == true){
        ui->groupBox_3->setVisible(true);
        ui->groupBox_4->setVisible(true);
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->comboBoxF->setVisible(true);
        ui->comboBoxT->setVisible(true);
        ui->labelK->setVisible(false);
        ui->labelMin->setVisible(true);
        ui->labelMax->setVisible(true);
        ui->labelInc->setVisible(true);
        ui->labelMin->setText("Minimun value:");
        ui->SBk->setVisible(false);
        ui->SBmin->setVisible(true);
        ui->SBmax->setVisible(true);
        ui->SBinc->setVisible(true);
        ui->Plot->setVisible(true);
        ui->Holdon->setVisible(true);
        ui->Export->setVisible(true);
        ui->labelType->setVisible(true);
        ui->TypeDesign->setVisible(true);
        ui->labelAux->setVisible(true);
        ui->Services->setVisible(true);
        if(SI == true){
            QStringList Lista1,Lista2;
            ui->comboBoxT->clear();
            ui->comboBoxF->clear();
            Lista1 << "Select one..." << "Kelvin (°K)" << "Farenheit (°F)" << "Celsius (°C)" << "Ranking (°R)";
            Lista2 << "Select one..." << "Btu/hr ft^2 °F" << "CHU/hr ft^2 °F";
            ui->comboBoxT->addItems(Lista1);
            ui->comboBoxF->addItems(Lista2);
        }else if(SIS == true){
            QStringList Lista1,Lista2;
            ui->comboBoxT->clear();
            ui->comboBoxF->clear();
            Lista1 << "Select one..." << "Kelvin (°K)" << "Farenheit (°F)" << "Celsius (°C)" << "Ranking (°R)";
            Lista2 << "Select one..." << "W/m^2 °K" << "W/m^2 °C";
            ui->comboBoxT->addItems(Lista1);
            ui->comboBoxF->addItems(Lista2);
        }
    }else if(diverso == true && estatico == true){
        ui->groupBox_3->setVisible(true);
        ui->groupBox_4->setVisible(true);
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->comboBoxF->setVisible(true);
        ui->comboBoxT->setVisible(true);
        ui->labelK->setVisible(true);
        ui->labelMin->setVisible(true);
        ui->labelMax->setVisible(false);
        ui->labelInc->setVisible(false);
        ui->labelMin->setText("Value:");
        ui->SBk->setVisible(true);
        ui->SBmin->setVisible(true);
        ui->SBmax->setVisible(false);
        ui->SBinc->setVisible(false);
        ui->Plot->setVisible(true);
        ui->Holdon->setVisible(true);
        ui->Export->setVisible(true);
        ui->labelType->setVisible(true);
        ui->TypeDesign->setVisible(true);
        ui->labelAux->setVisible(true);
        ui->Services->setVisible(true);
        if(SI == true){
            QStringList Lista1,Lista2;
            ui->comboBoxT->clear();
            ui->comboBoxF->clear();
            Lista1 << "Select one..." << "Kelvin (°K)" << "Farenheit (°F)" << "Celsius (°C)" << "Ranking (°R)";
            Lista2 << "Select one..." << "Btu/hr ft^2 °F" << "CHU/hr ft^2 °F";
            ui->comboBoxT->addItems(Lista1);
            ui->comboBoxF->addItems(Lista2);
        }else if(SIS == true){
            QStringList Lista1,Lista2;
            ui->comboBoxT->clear();
            ui->comboBoxF->clear();
            Lista1 << "Select one..." << "Kelvin (°K)" << "Farenheit (°F)" << "Celsius (°C)" << "Ranking (°R)";
            Lista2 << "Select one..." << "W/m^2 °K" << "W/m^2 °C";
            ui->comboBoxT->addItems(Lista1);
            ui->comboBoxF->addItems(Lista2);
        }
    }else if(diverso == true && incremento == true){
        ui->groupBox_3->setVisible(true);
        ui->groupBox_4->setVisible(true);
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->comboBoxF->setVisible(true);
        ui->comboBoxT->setVisible(true);
        ui->labelK->setVisible(true);
        ui->labelMin->setVisible(true);
        ui->labelMax->setVisible(true);
        ui->labelInc->setVisible(true);
        ui->labelMin->setText("Minimun value:");
        ui->SBk->setVisible(true);
        ui->SBmin->setVisible(true);
        ui->SBmax->setVisible(true);
        ui->SBinc->setVisible(true);
        ui->Plot->setVisible(true);
        ui->Holdon->setVisible(true);
        ui->Export->setVisible(true);
        ui->labelType->setVisible(true);
        ui->TypeDesign->setVisible(true);
        ui->labelAux->setVisible(true);
        ui->Services->setVisible(true);
        if(SI == true){
            QStringList Lista1,Lista2;
            ui->comboBoxT->clear();
            ui->comboBoxF->clear();
            Lista1 << "Select one..." << "Kelvin (°K)" << "Farenheit (°F)" << "Celsius (°C)" << "Ranking (°R)";
            Lista2 << "Select one..." << "Btu/hr ft^2 °F" << "CHU/hr ft^2 °F";
            ui->comboBoxT->addItems(Lista1);
            ui->comboBoxF->addItems(Lista2);
        }else if(SIS == true){
            QStringList Lista1,Lista2;
            ui->comboBoxT->clear();
            ui->comboBoxF->clear();
            Lista1 << "Select one..." << "Kelvin (°K)" << "Farenheit (°F)" << "Celsius (°C)" << "Ranking (°R)";
            Lista2 << "Select one..." << "W/m^2 °K" << "W/m^2 °C";
            ui->comboBoxT->addItems(Lista1);
            ui->comboBoxF->addItems(Lista2);
        }
    }else if(uniforme == false || diverso == false){
        ui->labelK->setVisible(false);
        ui->labelMin->setVisible(false);
        ui->labelMax->setVisible(false);
        ui->labelInc->setVisible(false);
        ui->SBk->setVisible(false);
        ui->SBmin->setVisible(false);
        ui->SBmax->setVisible(false);
        ui->SBinc->setVisible(false);
        ui->Plot->setVisible(false);
        ui->Holdon->setVisible(false);
        ui->Export->setVisible(false);
    }
}

void contenido_plots_area::Plot(int ventanaplot, bool uniforme, bool diverso, bool estatico, bool incremento,
                                QVector<double> TS, QVector<double> TE, QVector<double> Wcp , QVector<double> h,
                                QVector<double> Enfriamento,QVector<double> Calentamiento,int CTo,int CCo)
{
    ui->qcustomplot->setVisible(true);
    ui->qcustomplot->setEnabled(true);
    ui->qcustomplot->clearGraphs();
    if(ventanaplot == 3){ // AREAS
        if(uniforme == true && estatico == true){
            double DTmin = ui->SBmin->value();
            Plot_Dtmin_vs_Areas plot(TS,TE,Wcp,h,Calentamiento,Enfriamento,DTmin,CTo,CCo);
            double Area = plot.getAREAS();
            qDebug() << Area << DTmin;
            QVector<double> AreasTotales;
            QVector<double> DTminTotal;
            AreasTotales.resize(1);
            DTminTotal.resize(1);
            AreasTotales[0] = Area;
            DTminTotal[0] = DTmin;
            ui->qcustomplot->addGraph();
            ui->qcustomplot->graph(0)->setData(DTminTotal,AreasTotales);
            ui->qcustomplot->xAxis->setLabel("DTmin");
            ui->qcustomplot->yAxis->setLabel("Areas");
            ui->qcustomplot->graph(0)->rescaleAxes();
            ui->qcustomplot->graph(0)->rescaleAxes(true);
            ui->qcustomplot->replot();
        }else if(uniforme == true && incremento == true){
            double Maximo = ui->SBmax->value();
            double Minimo = ui ->SBmin->value();
            double Incremento = ui->SBinc->value();
            double Iteraciones =(Maximo-Minimo)/Incremento;
            QVector<double> AreasTotales, DTminTotal;
            DTminTotal.resize(Iteraciones+1);
            AreasTotales.resize(Iteraciones+1);
            double DTmin = Minimo;
            for(int i = 0; i <= Iteraciones ; i++){
                 Plot_Dtmin_vs_Areas plot(TS,TE,Wcp,h,Calentamiento,Enfriamento,DTmin,CTo,CCo);
                 double Area = plot.getAREAS();
                 AreasTotales[i] = Area;
                 DTminTotal[i] = DTmin;
                 DTmin = DTmin + Incremento;
            }
            ui->qcustomplot->addGraph();
            ui->qcustomplot->graph(0)->setData(DTminTotal,AreasTotales);
            ui->qcustomplot->xAxis->setLabel("DTmin");
            ui->qcustomplot->yAxis->setLabel("Areas");
            double minX = *std::min_element(DTminTotal.begin(),DTminTotal.end());
            double maxX = *std::max_element(DTminTotal.begin(),DTminTotal.end());
            double minY = *std::min_element(AreasTotales.begin(),AreasTotales.end());
            double maxY = *std::max_element(AreasTotales.begin(),AreasTotales.end());
            ui->qcustomplot->xAxis->setRange(minX-5,maxX+5);
            ui->qcustomplot->yAxis->setRange(minY-5,maxY+5);
//            ui->qcustomplot->graph(0)->rescaleAxes();
//            ui->qcustomplot->graph(0)->rescaleAxes(true);
            ui->qcustomplot->replot();
        }else if(diverso == true && estatico == true){
        }else if(diverso == true && incremento == true){
        }else if(uniforme == false || diverso == false){
        }
    }
}
