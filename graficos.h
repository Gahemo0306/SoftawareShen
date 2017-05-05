#ifndef GRAFICOS_H
#define GRAFICOS_H
#include <QVector>
#include <QDebug>
//#include <qalgorithms.h>

class Graficos
{
public:
    Graficos();
};

class Plot_curvascompuestas
{
public:
    //Operaciones(QVector<double> ST, QVector<double> TT, QVector<double> Cp,QVector<double> h);
    Plot_curvascompuestas(QVector<double> Tsupply, QVector<double> Ttarget,
                          QVector<double> Cp);
    QVector<double> getCCENTALPIA();
    QVector<double> getCCTEMPERATURAS();
    QVector<double> getCFENTALPIA();
    QVector<double> getCFTEMPERATURAS();
private:
    QVector<double> MCCENTALPIA,MCCTEMPERATURAS; //,Mh;
    QVector<double> MCFENTALPIA,MCFTEMPERATURAS;
};

class Plot_curvascompuestasajustadas
{
public:
    Plot_curvascompuestasajustadas(QVector<double> Tsupply, QVector<double> Ttarget,
                                   QVector<double> Cp,double DTmin);
    QVector<double> getCCENTALPIA();
    QVector<double> getCCTEMPERATURAS();
    QVector<double> getCFENTALPIAAJUSTADAS();
    QVector<double> getCFTEMPERATURASAJUSTADAS();
    QVector<QVector<double>> getVectorCorrientesTotal();
    QVector<QVector<double>> getVecHeatFlow();
    QVector<QVector<double>> getVecAdjHeatFlow();
    QVector<double> getDeficit();
private:
    QVector<double> MCCENTALPIA,MCCTEMPERATURAS; //,Mh;
    QVector<double> MCFENTALPIAAJUSTADA,MCFTEMPERATURASAJUSTADA;
    QVector<QVector<double>> MVectorCorrientesTotal;
    QVector<QVector<double>> MVecHeatFlow,MVecAdjHeatFlow;
    QVector<double> MDeficit;
};

class Plot_grancurvacompuesta
{
public:
    Plot_grancurvacompuesta(QVector<double> Tsupply, QVector<double> Ttarget,
                            QVector<double> Cp, double DTmin);
    QVector<double> getGCTEMPERATURAS();
    QVector<double> getGCENTALPIA();
private:
    QVector<double> MGCTEMPERATURAS,MGCENTALPIA;
};

class Plot_Dtmin_vs_Areas
{
public:
    Plot_Dtmin_vs_Areas(QVector<double> Tsupply, QVector<double> Ttarget,
                        QVector<double> Cp, QVector<double> h, QVector<double> Calentamiento,
                        QVector<double> Enfriamento,double DTmin,int CTo,int CCo);
    double getAREAS();
private:
    double MAREAS;
};

class Plot_curvascompuestas_diversa
{
public:
    Plot_curvascompuestas_diversa(QVector<double> Tsupply, QVector<double> Ttarget,
                          QVector<double> Cp, QVector<double> h, double DTmin, double K);
    QVector<double> getCCENTALPIA();
    QVector<double> getCCTEMPERATURAS();
    QVector<double> getCFENTALPIA();
    QVector<double> getCFTEMPERATURAS();
private:
    QVector<double> MCCENTALPIA,MCCTEMPERATURAS; //,Mh;
    QVector<double> MCFENTALPIA,MCFTEMPERATURAS;
};


class Plot_CCAJUSTADA_DIVERSA
{
public:
    Plot_CCAJUSTADA_DIVERSA(QVector<double> Tsupply, QVector<double> Ttarget,
                            QVector<double> Cp, QVector<double> h, double DTmin, double K);
    QVector<double> getCCENTALPIA();
    QVector<double> getCCTEMPERATURAS();
    QVector<double> getCFENTALPIAAJUSTADAS();
    QVector<double> getCFTEMPERATURASAJUSTADAS();
    QVector<QVector<double>> getVectorCorrientesTotal();
    QVector<QVector<double>> getVecHeatFlow();
    QVector<QVector<double>> getVecAdjHeatFlow();
    QVector<double> getDeficit();
private:
    QVector<double> MCCENTALPIA,MCCTEMPERATURAS; //,Mh;
    QVector<double> MCFENTALPIAAJUSTADA,MCFTEMPERATURASAJUSTADA;
    QVector<QVector<double>> MVectorCorrientesTotal;
    QVector<QVector<double>> MVecHeatFlow,MVecAdjHeatFlow;
    QVector<double> MDeficit;
};

#endif // GRAFICOS_H
