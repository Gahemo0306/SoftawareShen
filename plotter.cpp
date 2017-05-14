#include "plotter.h"
#include "ui_plotter.h"
#include "duvaloraction.h"
#include "valoraction.h"
#include "graficos.h"
#include "QDebug"

plotter::plotter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plotter)
{
    ui->setupUi(this);
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
    if(ventanaplot == 0){
        QFile FileVec(VECPLOTCURVASCOMPUESTAS_FILENAME);
        if (!FileVec.open(QIODevice::ReadOnly)){
            QMessageBox::warning(this,tr("Error"),tr("Nada no pasa nada"));
            return;
        }
        QDataStream in6(&FileVec);
        bool Divers = false;
        bool Uniform = false;
        bool Estatic = false;
        bool Increment = false;
        double Mi = 0;
        double Ma = 0;
        double In = 0;
        double K = 0;
        QVector<double> Ts,Te,WCp,h;
        Ts.resize(10);
        Te.resize(10);
        WCp.resize(10);
        h.resize(10);
        in6.setVersion(QDataStream::Qt_5_4);
        VecPlot_CurvasCompuestas Vec(Uniform,Divers,Estatic,Increment,Ts,Te,WCp,h,Mi,Ma,In,K);
        in6 >> Vec;
        bool Diverso = Vec.getDiverso();
        bool Uniforme = Vec.getUniforme();
        bool Estatico = Vec.getEstatico();
        bool Incremento = Vec.getIncremmento();
        double Min = Vec.getMin();
        double Max = Vec.getMax();
        double Inc = Vec.getInc();
        double K1 = Vec.getK();
        QVector<double> TS = Vec.getTS();
        QVector<double> TE = Vec.getTE();
        QVector<double> WCP = Vec.getWCP();
        QVector<double> H = Vec.geth();
        plot(ventanaplot,Uniforme,Diverso,Estatico,Incremento,TS,TE,WCP,H,Min,Max,Inc,K1);
        FileVec.flush();
        FileVec.close();
    }else if(ventanaplot==1){ // CURVAS COMPUESTAS AJSUTADAS OK
        QFile FileBools(VECPLOTCURVASCOMPUESTASAJUSTADAS_BOOL_FILENAME);
        if (!FileBools.open(QIODevice::ReadOnly)){
            QMessageBox::warning(this,tr("Error"),tr("Error"));
            return;
        }
        QDataStream in9(&FileBools);
        in9.setVersion(QDataStream::Qt_5_4);
        bool uniforme = false;
        bool diverso = false;
        bool estatico = false;
        bool incremento = false;
        VecPlot_CurvasCompuestasAjustadasbool VecC(uniforme,diverso,estatico,incremento);
        in9 >> VecC;
        bool uni = VecC.getUniforme();
        bool div = VecC.getDiverso();
        bool est = VecC.getEstatico();
        bool inc = VecC.getIncremmento();
        if(uni == true && est == true){
            QFile FileVec(VECPLOTCURVASCOMPUESTASAJUSTADASESTATICO_FILENAME);
            if (!FileVec.open(QIODevice::ReadOnly)){
                QMessageBox::warning(this,tr("Error"),tr("Nada no pasa nada"));
                return;
            }
            QDataStream in7(&FileVec);
            bool Divers = false;
            bool Uniform = false;
            bool Estatic = false;
            bool Increment = false;
            double Dtmin = 0;
            QVector<double> Ts,Te,WCp,h1;
            Ts.resize(10);
            Te.resize(10);
            WCp.resize(10);
            h1.resize(10);
            in7.setVersion(QDataStream::Qt_5_4);
            VecPlot_CurvasCompuestasAjustadasEstatico VecCC(Uniform,Divers,Estatic,Increment,Ts,Te,WCp,Dtmin);
            in7 >> VecCC;
            bool Diverso1 =  VecCC.getDiverso();
            bool Uniforme1 =  VecCC.getUniforme();
            bool Estatico1 =  VecCC.getEstatico();
            bool Incremento1 =  VecCC.getIncremmento();
            double Min1 =  VecCC.getDTmin();
            double Max1 = 0;
            double Inc1 = 0;
            double K1 = 0;
            QVector<double> TS1 =  VecCC.getTS();
            QVector<double> TE1 = VecCC.getTE();
            QVector<double> WCP1 =  VecCC.getWCP();
            plot(ventanaplot,Uniforme1,Diverso1,Estatico1,Incremento1,TS1,TE1,WCP1,h1,Min1,Max1,Inc1,K1);
            FileVec.flush();
            FileVec.close();
        }else if(uni == true && inc == true){
            QFile FileVec(VECPLOTCURVASCOMPUESTASAJUSTADASDINAMICO_FILENAME);
            if (!FileVec.open(QIODevice::ReadOnly)){
                QMessageBox::warning(this,tr("Error"),tr("Nada no pasa nada"));
                return;
            }
            QDataStream in8(&FileVec);
            bool Divers = false;
            bool Uniform = false;
            bool Estatic = false;
            bool Increment = false;
            double Min1 = 0;
            double Max1 = 0;
            double Inc1 = 0;
            QVector<double> Ts,Te,WCp,h1;
            Ts.resize(10);
            Te.resize(10);
            WCp.resize(10);
            h1.resize(10);
            in8.setVersion(QDataStream::Qt_5_4);
            VecPlot_CurvasCompuestasAjustadasIncremento VecCCAI(Uniform,Divers,Estatic,Increment,Ts,Te,WCp,Min1,Max1,Inc1);
            in8 >> VecCCAI;
            bool Diverso = VecCCAI.getDiverso();
            bool Uniforme = VecCCAI.getUniforme();
            bool Estatico = VecCCAI.getEstatico();
            bool Incremento = VecCCAI.getIncremmento();
            double Min = VecCCAI.getMin();
            double Max = VecCCAI.getMax();
            double Inc = VecCCAI.getInc();
            double K1 = 0;
            QVector<double> TS = VecCCAI.getTS();
            QVector<double> TE = VecCCAI.getTE();
            QVector<double> WCP = VecCCAI.getWCP();
            plot(ventanaplot,Uniforme,Diverso,Estatico,Incremento,TS,TE,WCP,h1,Min,Max,Inc,K1);
            FileVec.flush();
            FileVec.close();
        }else if(div == true && est == true ){
            QFile FileVec(VECPLOTCCAESTATICO_DIVERSO_FILENAME);
            if (!FileVec.open(QIODevice::ReadOnly)){
                QMessageBox::warning(this,tr("Error"),tr("Nada no pasa nada"));
                return;
            }
            QDataStream in13(&FileVec);
            bool Divers = false;
            bool Uniform = false;
            bool Estatic = false;
            bool Increment = false;
            double Dtmin = 0;
            double K = 0;
            QVector<double> Ts,Te,WCp,h;
            Ts.resize(10);
            Te.resize(10);
            WCp.resize(10);
            h.resize(10);
            in13.setVersion(QDataStream::Qt_5_4);
            VecPlot_CCAjustadasEst_Diversa VecCCAED(Uniform,Divers,Estatic,Increment,Ts,Te,WCp,h,Dtmin,K);
            in13 >> VecCCAED;
            bool Diverso1 =  VecCCAED.getDiverso();
            bool Uniforme1 =  VecCCAED.getUniforme();
            bool Estatico1 =  VecCCAED.getEstatico();
            bool Incremento1 =  VecCCAED.getIncremmento();
            double Min1 =  VecCCAED.getDTmin();
            double Max1 = 0;
            double Inc1 = 0;
            double K1 = VecCCAED.getK();
            QVector<double> TS1 =  VecCCAED.getTS();
            QVector<double> TE1 = VecCCAED.getTE();
            QVector<double> WCP1 =  VecCCAED.getWCP();
            QVector<double> h1 = VecCCAED.geth();
            plot(ventanaplot,Uniforme1,Diverso1,Estatico1,Incremento1,TS1,TE1,WCP1,h1,Min1,Max1,Inc1,K1);
            FileVec.flush();
            FileVec.close();
        }else if(div == true && inc == true ){
            QFile FileVec(VECPLOTCCADINAMICO_DIVERSO_FILENAME);
            if (!FileVec.open(QIODevice::ReadOnly)){
                QMessageBox::warning(this,tr("Error"),tr("Nada no pasa nada"));
                return;
            }
            QDataStream in14(&FileVec);
            bool Divers = false;
            bool Uniform = false;
            bool Estatic = false;
            bool Increment = false;
            double Min = 0;
            double Max = 0;
            double Inc = 0;
            double K = 0;
            QVector<double> Ts,Te,WCp,h;
            Ts.resize(10);
            Te.resize(10);
            WCp.resize(10);
            h.resize(10);
            in14.setVersion(QDataStream::Qt_5_4);
            VecPlot_CCAjustadasInc_Diversa VecCCAID(Uniform,Divers,Estatic,Increment,Ts,Te,WCp,h,Min,Max,Inc,K);
            in14 >> VecCCAID;
            bool Diverso1 =  VecCCAID.getDiverso();
            bool Uniforme1 =  VecCCAID.getUniforme();
            bool Estatico1 =  VecCCAID.getEstatico();
            bool Incremento1 =  VecCCAID.getIncremmento();
            double Min1 =  VecCCAID.getMin();
            double Max1 = VecCCAID.getMax();
            double Inc1 = VecCCAID.getInc();
            double K1 = VecCCAID.getK();
            QVector<double> TS1 =  VecCCAID.getTS();
            QVector<double> TE1 = VecCCAID.getTE();
            QVector<double> WCP1 =  VecCCAID.getWCP();
            QVector<double> h1 = VecCCAID.geth();
            plot(ventanaplot,Uniforme1,Diverso1,Estatico1,Incremento1,TS1,TE1,WCP1,h1,Min1,Max1,Inc1,K1);
            FileVec.flush();
            FileVec.close();
        }
        FileBools.flush();
        FileBools.close();
    }else if(ventanaplot==2){ // GRAN CURVA COMPUESTA
        QFile FileBools(VECPLOTGCC_BOOL_FILENAME);
        if (!FileBools.open(QIODevice::ReadOnly)){
            QMessageBox::warning(this,tr("Error"),tr("Error"));
            return;
        }
        QDataStream in10(&FileBools);
        in10.setVersion(QDataStream::Qt_5_4);
        bool uniforme = false;
        bool diverso = false;
        bool estatico = false;
        bool incremento = false;
        VecPlot_CurvasCompuestasAjustadasbool VecC(uniforme,diverso,estatico,incremento);
        in10 >> VecC;
        bool uni = VecC.getUniforme();
        bool div = VecC.getDiverso();
        bool est = VecC.getEstatico();
        bool inc = VecC.getIncremmento();
        if(uni == true && est == true){
            QFile FileVec(VECPLOTGCCESTATICO_FILENAME);
            if (!FileVec.open(QIODevice::ReadOnly)){
                QMessageBox::warning(this,tr("Error"),tr("Nada no pasa nada"));
                return;
            }
            QDataStream in11(&FileVec);
            bool Divers = false;
            bool Uniform = false;
            bool Estatic = false;
            bool Increment = false;
            double Dtmin = 0;
            QVector<double> Ts,Te,WCp,h1;
            Ts.resize(10);
            Te.resize(10);
            WCp.resize(10);
            h1.resize(10);
            in11.setVersion(QDataStream::Qt_5_4);
            VecGCCestatico VecGCest(Uniform,Divers,Estatic,Increment,Ts,Te,WCp,Dtmin);
            in11 >> VecGCest;
            bool Diverso1 =  VecGCest.getDiverso();
            bool Uniforme1 =  VecGCest.getUniforme();
            bool Estatico1 =  VecGCest.getEstatico();
            bool Incremento1 =  VecGCest.getIncremmento();
            double Min1 =  VecGCest.getDTmin();
            double Max1 = 0;
            double Inc1 = 0;
            double K1 = 0;
            QVector<double> TS1 =  VecGCest.getTS();
            QVector<double> TE1 = VecGCest.getTE();
            QVector<double> WCP1 =  VecGCest.getWCP();
            plot(ventanaplot,Uniforme1,Diverso1,Estatico1,Incremento1,TS1,TE1,WCP1,h1,Min1,Max1,Inc1,K1);
            FileVec.flush();
            FileVec.close();
        }else if(uni == true && inc == true){
            QFile FileVec(VECPLOTGCCDINAMICO_FILENAME);
            if (!FileVec.open(QIODevice::ReadOnly)){
                QMessageBox::warning(this,tr("Error"),tr("Nada no pasa nada"));
                return;
            }
            QDataStream in12(&FileVec);
            bool Divers = false;
            bool Uniform = false;
            bool Estatic = false;
            bool Increment = false;
            double Min = 0;
            double Max = 0;
            double Inc = 0;
            QVector<double> Ts,Te,WCp,h1;
            Ts.resize(10);
            Te.resize(10);
            WCp.resize(10);
            h1.resize(10);
            in12.setVersion(QDataStream::Qt_5_4);
            VecGCCdinamico VecGCdin(Uniform,Divers,Estatic,Increment,Ts,Te,WCp,Min,Max,Inc);
            in12 >> VecGCdin;
            bool Diverso1 =  VecGCdin.getDiverso();
            bool Uniforme1 =  VecGCdin.getUniforme();
            bool Estatico1 =  VecGCdin.getEstatico();
            bool Incremento1 =  VecGCdin.getIncremmento();
            double Min1 = VecGCdin.getMin();
            double Max1 = VecGCdin.getMax();
            double Inc1 = VecGCdin.getInc();
            double K1 = 0;
            QVector<double> TS1 =  VecGCdin.getTS();
            QVector<double> TE1 = VecGCdin.getTE();
            QVector<double> WCP1 =  VecGCdin.getWCP();
            plot(ventanaplot,Uniforme1,Diverso1,Estatico1,Incremento1,TS1,TE1,WCP1,h1,Min1,Max1,Inc1,K1);
            FileVec.flush();
            FileVec.close();
        }else if(div == true && est == true){
            QFile FileVec(VECPLOTGCCESTATICO_DIVERSO_FILENAME);
            if (!FileVec.open(QIODevice::ReadOnly)){
                QMessageBox::warning(this,tr("Error"),tr("Error"));
                return;
            }
            QDataStream in15(&FileVec);
            bool Divers = false;
            bool Uniform = false;
            bool Estatic = false;
            bool Increment = false;
            double DTmin = 0;
            double K = 0;
            QVector<double> Ts,Te,WCp,h1;
            Ts.resize(10);
            Te.resize(10);
            WCp.resize(10);
            h1.resize(10);
            in15.setVersion(QDataStream::Qt_5_4);
            VecGCCED GCCED(Uniform,Divers,Estatic,Increment,Ts,Te,WCp,h1,DTmin,K);
            in15 >> GCCED;
            bool Diverso1 =  GCCED.getDiverso();
            bool Uniforme1 =  GCCED.getUniforme();
            bool Estatico1 =  GCCED.getEstatico();
            bool Incremento1 =  GCCED.getIncremmento();
            double Min1 = GCCED.getDTmin();
            double Max1 = 0;
            double Inc1 = 0;
            double K1 = GCCED.getK();
            QVector<double> TS1 =  GCCED.getTS();
            QVector<double> TE1 = GCCED.getTE();
            QVector<double> WCP1 =  GCCED.getWCP();
            QVector<double> H1 = GCCED.geth();
            plot(ventanaplot,Uniforme1,Diverso1,Estatico1,Incremento1,TS1,TE1,WCP1,H1,Min1,Max1,Inc1,K1);
        }else if(div == true && inc == true){
            QFile FileVec(VECPLOTGCCDINAMICA_DIVERSO_FILENAME);
            if (!FileVec.open(QIODevice::ReadOnly)){
                QMessageBox::warning(this,tr("Error"),tr("Error"));
                return;
            }
            QDataStream in16(&FileVec);
            bool Divers = false;
            bool Uniform = false;
            bool Estatic = false;
            bool Increment = false;
            double Min = 0;
            double Max = 0;
            double Inc = 0;
            double K = 0;
            QVector<double> Ts,Te,WCp,h1;
            Ts.resize(10);
            Te.resize(10);
            WCp.resize(10);
            h1.resize(10);
            in16.setVersion(QDataStream::Qt_5_4);
            //VecGCCED GCCED(Uniform,Divers,Estatic,Increment,Ts,Te,WCp,h1,DTmin,K);
            VecGCCDD GCCDD(Uniform,Divers,Estatic,Increment,Ts,Te,WCp,h1,Min,Max,Inc,K);
            in16 >> GCCDD;
            bool Diverso1 =  GCCDD.getDiverso();
            bool Uniforme1 =  GCCDD.getUniforme();
            bool Estatico1 =  GCCDD.getEstatico();
            bool Incremento1 =  GCCDD.getIncremmento();
            double Min1 = GCCDD.getMin();
            double Max1 = GCCDD.getMax();
            double Inc1 = GCCDD.getInc();
            double K1 = GCCDD.getK();
            QVector<double> TS1 =  GCCDD.getTS();
            QVector<double> TE1 = GCCDD.getTE();
            QVector<double> WCP1 =  GCCDD.getWCP();
            QVector<double> H1 = GCCDD.geth();
            plot(ventanaplot,Uniforme1,Diverso1,Estatico1,Incremento1,TS1,TE1,WCP1,H1,Min1,Max1,Inc1,K1);
        }
    } // FALTA PARA AREAS
    Fil.flush();
    Fil.close();
}

plotter::~plotter()
{
    delete ui;
}

void plotter::plot(int ventanaplot, bool uniforme, bool diverso, bool estatico, bool incremento,
                   QVector<double> TS, QVector<double> TE, QVector<double> Wcp, QVector<double> h,
                   double Min, double Max, double Inc, double K)
{
    if(ventanaplot == 0){ // es la de las curvas compuestas OK
        ui->qcustomplot->setVisible(true);
        ui->qcustomplot->setEnabled(true);
        ui->qcustomplot->clearGraphs();
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
            ui->qcustomplot->plotLayout()->insertRow(0);
            ui->qcustomplot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->qcustomplot, "Uniform composite curves", QFont("sans", 12, QFont::Bold)));
            ui->qcustomplot->replot();
        }else if(diverso == true){
            double DTmin = Min;
            Plot_curvascompuestas_diversa plot1(TS,TE,Wcp,h,DTmin,K);
            QVector<double> CCENTALPIA = plot1.getCCENTALPIA();
            QVector<double> CCTEMPERATURAS = plot1.getCCTEMPERATURAS();
            ui->qcustomplot->setVisible(true);
            ui->qcustomplot->setEnabled(true);
            ui->qcustomplot->addGraph();
            ui->qcustomplot->graph(0)->setPen(QPen(Qt::red));
            ui->qcustomplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
            ui->qcustomplot->graph(0)->setData(CCENTALPIA,CCTEMPERATURAS);
            ui->qcustomplot->xAxis->setLabel("ENTHALPY");
            ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
            ui->qcustomplot->replot();
            QVector<double> CFENTALPIA = plot1.getCFENTALPIA();
            QVector<double> CFTEMPERATURAS = plot1.getCFTEMPERATURAS();
            ui->qcustomplot->addGraph();
            ui->qcustomplot->graph(1)->setPen(QPen(Qt::blue));
            ui->qcustomplot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
            ui->qcustomplot->graph(1)->setData(CFENTALPIA,CFTEMPERATURAS);
            ui->qcustomplot->graph(0)->rescaleAxes();
            ui->qcustomplot->graph(1)->rescaleAxes(true);
            ui->qcustomplot->plotLayout()->insertRow(0);
            ui->qcustomplot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->qcustomplot, "Diverse composite curves", QFont("sans", 12, QFont::Bold)));
            ui->qcustomplot->replot();
        }
    }else if(ventanaplot == 1){// es la de las curvas compuestas ajustadas OK
            ui->qcustomplot->setVisible(true);
            ui->qcustomplot->setEnabled(true);
            ui->qcustomplot->clearGraphs();
            if(uniforme == true && estatico == true){
                double DTmin = Min;
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
                ui->qcustomplot->plotLayout()->insertRow(0);
                ui->qcustomplot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->qcustomplot, "Uniform composite curves adjusted", QFont("sans", 12, QFont::Bold)));
                ui->qcustomplot->replot();
            }else if(uniforme == true && incremento == true){
                double Minimo = Min;
                double Maximo = Max;
                double Incremento = Inc;
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
                ui->qcustomplot->plotLayout()->insertRow(0);
                ui->qcustomplot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->qcustomplot, "Uniform composite curves adjusted", QFont("sans", 12, QFont::Bold)));
                ui->qcustomplot->replot();
            }else if(diverso == true && estatico == true){
                double DTmin = Min;
                Plot_CCAJUSTADA_DIVERSA plot2(TS,TE,Wcp,h,DTmin,K);
                QVector<double> CCENTALPIA = plot2.getCCENTALPIA();
                QVector<double> CCTEMPERATURAS = plot2.getCCTEMPERATURAS();
                ui->qcustomplot->addGraph();
                ui->qcustomplot->graph(0)->setPen(QPen(Qt::red));
                ui->qcustomplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
                ui->qcustomplot->graph(0)->setData(CCENTALPIA,CCTEMPERATURAS);
                ui->qcustomplot->xAxis->setLabel("ENTHALPY");
                ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
                ui->qcustomplot->replot();
                QVector<double> CFENTALPIAAJUSTADAS = plot2.getCFENTALPIAAJUSTADAS();
                QVector<double> CFTEMPERATURASAJUSTADAS = plot2.getCFTEMPERATURASAJUSTADAS();
                ui->qcustomplot->addGraph();
                ui->qcustomplot->graph(1)->setPen(QPen(Qt::blue));
                ui->qcustomplot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
                ui->qcustomplot->graph(1)->setData(CFENTALPIAAJUSTADAS,CFTEMPERATURASAJUSTADAS);
                ui->qcustomplot->graph(0)->rescaleAxes();
                ui->qcustomplot->graph(1)->rescaleAxes(true);
                ui->qcustomplot->plotLayout()->insertRow(0);
                ui->qcustomplot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->qcustomplot, "Diverse composite curves adjusted", QFont("sans", 12, QFont::Bold)));
                ui->qcustomplot->replot();
            }else if(diverso == true && incremento == true){
                double Minimo = Min;
                double Maximo = Max;
                double Incremento = Inc;
                double Iteraciones =(Maximo-Minimo)/Incremento;
                double DTmin = Minimo;
                int j=0;
                Plot_CCAJUSTADA_DIVERSA plot2(TS,TE,Wcp,h,DTmin,K);
                QVector<double> CCENTALPIA = plot2.getCCENTALPIA();
                QVector<double> CCTEMPERATURAS = plot2.getCCTEMPERATURAS();
                ui->qcustomplot->addGraph();
                ui->qcustomplot->graph(j)->setPen(QPen(Qt::red));
                ui->qcustomplot->graph(j)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
                ui->qcustomplot->graph(j)->setData(CCENTALPIA,CCTEMPERATURAS);
                ui->qcustomplot->graph(j)->rescaleAxes();
                for(int i = 0; i <= Iteraciones ; i++){
                    j++;
                    Plot_CCAJUSTADA_DIVERSA plot2(TS,TE,Wcp,h,DTmin,K);
                    QVector<double> CFENTALPIAAJUSTADAS = plot2.getCFENTALPIAAJUSTADAS();
                    QVector<double> CFTEMPERATURASAJUSTADAS = plot2.getCFTEMPERATURASAJUSTADAS();
                    ui->qcustomplot->addGraph();
                    ui->qcustomplot->graph(j)->setPen(QPen(Qt::blue));
                    ui->qcustomplot->graph(j)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
                    ui->qcustomplot->graph(j)->setData(CFENTALPIAAJUSTADAS,CFTEMPERATURASAJUSTADAS);
                    ui->qcustomplot->graph(j)->rescaleAxes(true);
                    DTmin = DTmin + Incremento;
                }
                ui->qcustomplot->xAxis->setLabel("ENTHALPY");
                ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
                ui->qcustomplot->plotLayout()->insertRow(0);
                ui->qcustomplot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->qcustomplot, "Diverse composite curves adjusted", QFont("sans", 12, QFont::Bold)));
                ui->qcustomplot->replot();
            }
    }else if(ventanaplot == 2){ // GRAN CURVA COMPUESTA
        ui->qcustomplot->setVisible(true);
        ui->qcustomplot->setEnabled(true);
        ui->qcustomplot->clearGraphs();
        if(uniforme == true && estatico == true){
            double DTmin = Min;
            Plot_grancurvacompuesta plot(TS,TE,Wcp,DTmin);
            QVector<double> GCENTALPIA = plot.getGCENTALPIA();
            QVector<double> GCTEMPERATURAS = plot.getGCTEMPERATURAS();
            ui->qcustomplot->addGraph();
            ui->qcustomplot->graph(0)->setPen(QPen(Qt::blue));
            ui->qcustomplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
            ui->qcustomplot->graph(0)->setLineStyle(QCPGraph::lsLine);
            ui->qcustomplot->graph(0)->setData(GCENTALPIA,GCTEMPERATURAS);
            ui->qcustomplot->xAxis->setLabel("ENTHALPY");
            ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
            ui->qcustomplot->graph(0)->rescaleAxes();
            ui->qcustomplot->graph(0)->rescaleAxes(true);
            ui->qcustomplot->plotLayout()->insertRow(0);
            ui->qcustomplot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->qcustomplot, "Uniform grand compositive curve", QFont("sans", 12, QFont::Bold)));
            ui->qcustomplot->replot();
        }else if(uniforme == true && incremento == true){
            double Minimo = Min;
            double Maximo = Max;
            double Incremento = Inc;
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
                 ui->qcustomplot->graph(i)->setData(GCENTALPIA,GCTEMPERATURAS);
                 ui->qcustomplot->graph(i)->rescaleAxes();
                 ui->qcustomplot->graph(i)->rescaleAxes(true);
                 DTmin = DTmin + Incremento;
            }
            ui->qcustomplot->xAxis->setLabel("ENTHALPY");
            ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
            ui->qcustomplot->plotLayout()->insertRow(0);
            ui->qcustomplot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->qcustomplot, "Uniform grand compositive curve", QFont("sans", 12, QFont::Bold)));
            ui->qcustomplot->replot();
        }else if(diverso == true && estatico == true){
            double DTMin = Min;
            PlotGCC_DIVERSA plotGCCD(TS,TE,Wcp,h,DTMin,K);
            QVector<double> GCENTALPIA = plotGCCD.getGCENTALPIA();
            QVector<double> GCTEMPERATURAS = plotGCCD.getGCTEMPERATURAS();
            ui->qcustomplot->addGraph();
            ui->qcustomplot->graph(0)->setPen(QPen(Qt::blue));
            ui->qcustomplot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
            ui->qcustomplot->graph(0)->setLineStyle(QCPGraph::lsLine);
            ui->qcustomplot->graph(0)->setData(GCENTALPIA,GCTEMPERATURAS);
            ui->qcustomplot->graph(0)->rescaleAxes();
            ui->qcustomplot->graph(0)->rescaleAxes(true);
            ui->qcustomplot->xAxis->setLabel("ENTHALPY");
            ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
            ui->qcustomplot->plotLayout()->insertRow(0);
            ui->qcustomplot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->qcustomplot, "Diverse grand compositive curve", QFont("sans", 12, QFont::Bold)));
            ui->qcustomplot->replot();
        }else if(diverso == true && incremento == true){
            double Minimo = Min;
            double Maximo = Max;
            double Incremento = Inc;
            double Iteraciones =(Maximo-Minimo)/Incremento;
            double DTmin = Minimo;
            for(int i = 0; i <= Iteraciones ; i++){
                 PlotGCC_DIVERSA plotGCCD(TS,TE,Wcp,h,DTmin,K);
                 QVector<double> GCENTALPIA = plotGCCD.getGCENTALPIA();
                 QVector<double> GCTEMPERATURAS = plotGCCD.getGCTEMPERATURAS();
                 ui->qcustomplot->addGraph();
                 ui->qcustomplot->graph(i)->setPen(QPen(Qt::blue));
                 ui->qcustomplot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
                 ui->qcustomplot->graph(i)->setLineStyle(QCPGraph::lsLine);
                 ui->qcustomplot->graph(i)->setData(GCENTALPIA,GCTEMPERATURAS);
                 ui->qcustomplot->graph(i)->rescaleAxes();
                 ui->qcustomplot->graph(i)->rescaleAxes(true);
                 DTmin = DTmin + Incremento;
            }
            ui->qcustomplot->xAxis->setLabel("ENTHALPY");
            ui->qcustomplot->yAxis->setLabel("TEMPERATURE");
            ui->qcustomplot->plotLayout()->insertRow(0);
            ui->qcustomplot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->qcustomplot, "Diverse grand compositive curve", QFont("sans", 12, QFont::Bold)));
            ui->qcustomplot->replot();
        }
    }else if(ventanaplot==3){ //areas

    }
}
