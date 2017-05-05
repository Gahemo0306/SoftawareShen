#include "duvaloraction.h"
#include <QVector>
#include <qalgorithms.h>
#include <iostream>
#include <qalgorithms.h>
#include <QtMath>
#include <QDebug>
#include <QtAlgorithms>

Duvaloraction::Duvaloraction(int valact)
{
    Mvalact = valact;
}

int Duvaloraction::getvalact() const //GETTER
{
    return Mvalact;
}

void Duvaloraction::setvalact(int valact) //SETTER
{
    Mvalact = valact;
}

Workspace::Workspace(QVector<QVector<double>>&matriz)
{
//    qDebug() << "Guardando";
    int filas = matriz.size();
    int columnas = matriz.at(0).size();
    MMatriz.resize(filas);
    for(int i = 0; i < filas; i++)
    {
        MMatriz[i].resize(columnas);
    }
    for(int i = 0; i < matriz.size(); i++){
        for(int j = 0 ; j < matriz.at(i).size() ;j++){
        MMatriz[i][j] = matriz[i][j];
//        qDebug() << matriz[i][j];
        }
    }
//    qDebug() << "Guardado";
}

QVector<QVector<double> > Workspace::getMatriz() const
{
    return MMatriz;
}

Valordeoperacion::Valordeoperacion(int valor)
{
    Mvalor =  valor;
}

void Valordeoperacion::setvalor(int valor)
{
    Mvalor = valor;
}

int Valordeoperacion::getvalor() const
{
    return Mvalor;
}

Unidades::Unidades(bool SI, bool SIS, int UTemp, int UWcp, int Uh)
{
    MSI = SI;
    MSIS = SIS;
    MUTemp = UTemp;
    MUWcp = UWcp;
    MUh = Uh;
}

bool Unidades::getSI()
{
    return MSI;
}

bool Unidades::getSIS()
{
    return MSIS;
}

int Unidades::getUTemp()
{
    return MUTemp;
}

int Unidades::getUWcp()
{
    return MUWcp;
}

int Unidades::getUh()
{
    return MUh;
}


void Unidades::ConvertirUnidades(QVector<double> ST, QVector<double> TT, QVector<double> Cp, bool SI, bool SIN, int A, int B)
{
    MST.resize(ST.size());
    MTT.resize(TT.size());
    MCp.resize(Cp.size());
    if(SI == true){
        //  CONVIERTE LAS TEMPERATURAS A UNIDADES DE �F
        //  WCP A UNIDADES DE BTU/HR�F
        //  H SIGUE CONSTANTE BTU/HR FT^2 �F
        // CONVERSION DE TEMPERATURA DE ENTRADA Y OBJETIVO
        if (A == 1) {
            // Conversi�n de Kelvin a Farenheit
            for (int i = 0; i < ST.size(); i++){
                MST[i] = ST[i] * 1.8 - 459.67;
                MTT[i] = TT[i] * 1.8 - 459.67;
            }
        } else if (A == 2) {
            // Conversi�n de Farenheit a Farenheit
            for (int i = 0; i < ST.size(); i++){
                MST[i] = ST[i];
                MTT[i] = TT[i];
            }
        } else if (A == 3) {
            // Conversi�n de Celsius a Farenheit
            for (int i =0; i < ST.size(); i++){
                MST[i] = ST[i] * 1.8 + 32.0;
                MTT[i] = TT[i] * 1.8 + 32.0;
            }
        } else if (A == 4) {
            // Conversi�n de Ranking a Farenheit
            for (int i =0; i < ST.size(); i++){
                MST[i] = ST[i] - 459.67;
                MTT[i] = TT[i] - 459.67;
            }
        }
        //  CONVERCI�N DE WCP
        if (B == 1) {
            for (int i =0; i < Cp.size(); i++){
                MCp[i] = Cp[i];
            }
        } else if (B == 2) {
            for (int i =0; i < Cp.size(); i++){
                MCp[i] = Cp[i] * 60.0;
            }
        } else if (B == 3) {
            for (int i =0; i < Cp.size(); i++){
                MCp[i] = Cp[i] * 3600.0;
            }
        } else if (B == 4) {
            for (int i =0; i < Cp.size(); i++){
                MCp[i] = Cp[i] * 0.55555555556;
            }
        } else if (B == 5) {
            for (int i =0; i < Cp.size(); i++){
                MCp[i] = Cp[i] * 0.55555555556 * 60.0;
            }
        } else if (B == 6.) {
            for (int i =0; i < Cp.size(); i++){
                MCp[i] = Cp[i] * 0.55555555556 * 3600.0;
            }
        } else if (B == 7) {
            for (int i =0; i < Cp.size(); i++){
                MCp[i] = Cp[i];
            }
        } else if (B == 8) {
            for (int i =0; i < Cp.size(); i++){
                MCp[i] = Cp[i] * 60.0;
            }
        } else if (B == 9){
            for (int i =0; i < Cp.size(); i++){
                MCp[i] = Cp[i] * 3600.0;
            }
        }
    } else {
        if (SIN == 1) {
            // SISTEMA INTERNACIONAL
            //  CONVIERTE LAS TEMPERATURAS A UNIDADES DE �C
            //  WCP A UNIDADES DE BTU/HR�F
            //  H SIGUE CONSTANTE BTU/HR FT^2 �F
            // CONVERSION DE TEMPERATURA DE ENTRADA Y OBJETIVO
            if (A == 1) {
                // Conversi�n de Kelvin a Celsius
                for (int i =0; i < ST.size(); i++){
                    MST[i] = ST[i] + 273.15;
                    MTT[i] = TT[i] + 273.15;
                }
            } else if (A == 2) {
                // Conversi�n de Farenheit a Celsius
                for (int i =0; i < ST.size(); i++){
                    MST[i] = ST[i] * 1.8 + 32.0;
                    MTT[i] = TT[i] * 1.8 + 32.0;
                }
            } else if (A == 3) {
                // Conversi�n de Celsius a Celsius
                for (int i =0; i < ST.size(); i++){
                    MST[i] = ST[i];
                    MTT[i] = TT[i];
                }
            } else if (A == 4){
                // Conversi�n de Ranking a Celsius
                for (int i =0; i < ST.size(); i++){
                    MST[i] = (MST[i] + 273.15) * 1.8;
                    MTT[i] = (MTT[i] + 273.15) * 1.8;
                }
            }
            //  CONVERCI�N DE WCP
            if (B == 1) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i] / 3600.0;
                }
            } else if (B == 2) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i] / 60.0;
                }
            } else if (B == 3) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i];
                }
            } else if (B == 4) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i] / 3600.0;
                }
            } else if (B == 5) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i] / 60.0;
                }
            } else if (B == 6) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i];
                }
            } else if (B == 7) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i] * 1000.0 / 3600.0;
                }
            } else if (B == 8) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i] * 1000.0 / 60.0;
                }
            } else if (B == 9) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i] * 1000.0;
                }
            } else if (B == 10) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i] * 1000.0 / 3600.0;
                }
            } else if (B == 11) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i] * 1000.0 / 60.0;
                }
            } else if (B == 12) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i]* 1000.0;
                }
            } else if (B == 13) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i] * 4186.8 / 3600.0;
                }
            } else if (B == 14) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i] * 4186.8 / 60.0;
                }
            } else if (B == 15) {
                for (int i =0; i < Cp.size(); i++){
                    MCp[i] = Cp[i]* 4186.8;
                }
            }
        }
    }
}

QVector<double> Unidades::getST()
{
    return MST;
}

QVector<double> Unidades::getTT()
{
    return MTT;
}

QVector<double> Unidades::getCp()
{
    return MCp;
}

Tabplot::Tabplot(int tabvalue)
{
    Mtabvalue = tabvalue;
}

void Tabplot::settabvalue(int tabvalue)
{
    Mtabvalue = tabvalue;
}

int Tabplot::gettabvalue()
{
    return Mtabvalue;
}


QDataStream &operator<<(QDataStream &out1, const Duvaloraction &valoraction)
{
    return out1 << valoraction.Mvalact;
}

QDataStream &operator>>(QDataStream &in1, Duvaloraction &valoraction)
{
    return in1 >> valoraction.Mvalact;
}

QDataStream &operator<<(QDataStream &out2, const Workspace &MATRIZ)
{
//        qDebug() << "out";
    return out2 << MATRIZ.MMatriz;
}

QDataStream &operator>>(QDataStream &in2, Workspace &MATRIZ)
{
//        qDebug() << "in";
    return in2  >> MATRIZ.MMatriz;
}


QDataStream &operator<<(QDataStream &out3, const Unidades &units)
{
    return out3 << units.MSI << units.MSIS << units.MUTemp << units.MUWcp << units.MUh;
}

QDataStream &operator>>(QDataStream &in3, Unidades &units)
{
    return in3 >> units.MSI >> units.MSIS >> units.MUTemp >> units.MUWcp >> units.MUh;
}

QDataStream &operator<<(QDataStream &out4, const Tabplot &tabvalue)
{
    return out4 << tabvalue.Mtabvalue;
}

QDataStream &operator>>(QDataStream &in4, Tabplot &tabvalue)
{
    return in4 >> tabvalue.Mtabvalue;
}

QDataStream &operator<<(QDataStream &out5, const Valordeoperacion &valor)
{
    return out5 << valor.Mvalor;
}

QDataStream &operator>>(QDataStream &in5, Valordeoperacion &valor)
{
    return in5 >> valor.Mvalor;
}


VecPlot_CurvasCompuestas::VecPlot_CurvasCompuestas(bool uniforme, bool diverso, bool estatico, bool incremento,
                                                   QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                                                   QVector<double> &h,
                                                   double Min, double Max, double Inc, double K)
{
    MMin = Min;
    MMax = Max;
    MInc = Inc;
    Muniforme = uniforme;
    Mdiverso = diverso;
    Mestatico = estatico;
    Mincremento = incremento;
    MTS.resize(TS.size());
    MTE.resize(TE.size());
    MWCP.resize(Wcp.size());
    Mh.resize(h.size());
    for(int i = 0; i < TS.size(); i++){
        MTS[i] = TS[i];
    }
    for(int i = 0; i < TE.size(); i++){
        MTE[i] = TE[i];
    }
    for(int i = 0; i < Wcp.size(); i++){
        MWCP[i] = Wcp[i];
    }
    for(int i = 0; i < Wcp.size(); i++){
        Mh[i] = h[i];
    }
    MK = K;
}

bool VecPlot_CurvasCompuestas::getUniforme() const
{
    return Muniforme;
}

bool VecPlot_CurvasCompuestas::getDiverso() const
{
    return Mdiverso;
}

bool VecPlot_CurvasCompuestas::getEstatico() const
{
    return Mestatico;
}

bool VecPlot_CurvasCompuestas::getIncremmento() const
{
    return Mincremento;
}

double VecPlot_CurvasCompuestas::getMin() const
{
    return MMin;
}

double VecPlot_CurvasCompuestas::getMax() const
{
    return MMax;
}

double VecPlot_CurvasCompuestas::getInc() const
{
    return MInc;
}

double VecPlot_CurvasCompuestas::getK() const
{
    return MK;
}

QVector<double> VecPlot_CurvasCompuestas::getTS() const
{
    return MTS;
}

QVector<double> VecPlot_CurvasCompuestas::getTE() const
{
    return MTE;
}

QVector<double> VecPlot_CurvasCompuestas::getWCP() const
{
    return MWCP;
}

QVector<double> VecPlot_CurvasCompuestas::geth() const
{
    return Mh;
}

QDataStream &operator<<(QDataStream &out6, const VecPlot_CurvasCompuestas &VecCC)
{
    return out6 << VecCC.Muniforme << VecCC.Mdiverso << VecCC.Mestatico << VecCC.Mincremento
                << VecCC.MTS << VecCC.MTE << VecCC.MWCP << VecCC.Mh << VecCC.MMin << VecCC.MMax << VecCC.MInc << VecCC.MK;
}

QDataStream &operator>>(QDataStream &in6, VecPlot_CurvasCompuestas &VecCC)
{
    return in6 >> VecCC.Muniforme >> VecCC.Mdiverso >> VecCC.Mestatico >> VecCC.Mincremento
               >> VecCC.MTS >> VecCC.MTE >> VecCC.MWCP >>  VecCC.Mh >> VecCC.MMin >> VecCC.MMax >> VecCC.MInc >> VecCC.MK;
}

VecPlot_CurvasCompuestasAjustadasEstatico::VecPlot_CurvasCompuestasAjustadasEstatico(bool uniforme, bool diverso, bool estatico, bool incremento,
                                                   QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                                                   double DTMin)
{
    MDTmin = DTMin;
    Muniforme = uniforme;
    Mdiverso = diverso;
    Mestatico = estatico;
    Mincremento = incremento;
    MTS.resize(TS.size());
    MTE.resize(TE.size());
    MWCP.resize(Wcp.size());
    for(int i = 0; i < TS.size(); i++){
        MTS[i] = TS[i];
    }
    for(int i = 0; i < TE.size(); i++){
        MTE[i] = TE[i];
    }
    for(int i = 0; i < Wcp.size(); i++){
        MWCP[i] = Wcp[i];
    }
}

bool VecPlot_CurvasCompuestasAjustadasEstatico::getUniforme() const
{
    return Muniforme;
}

bool VecPlot_CurvasCompuestasAjustadasEstatico::getDiverso() const
{
    return Mdiverso;
}

bool VecPlot_CurvasCompuestasAjustadasEstatico::getEstatico() const
{
    return Mestatico;
}

bool VecPlot_CurvasCompuestasAjustadasEstatico::getIncremmento() const
{
    return Mincremento;
}

double VecPlot_CurvasCompuestasAjustadasEstatico::getDTmin() const
{
    return MDTmin;
}

QVector<double> VecPlot_CurvasCompuestasAjustadasEstatico::getTS() const
{
    return MTS;
}

QVector<double> VecPlot_CurvasCompuestasAjustadasEstatico::getTE() const
{
    return MTE;
}

QVector<double> VecPlot_CurvasCompuestasAjustadasEstatico::getWCP() const
{
    return MWCP;
}

QDataStream &operator<<(QDataStream &out7, const VecPlot_CurvasCompuestasAjustadasEstatico &VecCCAE)
{
    return out7 << VecCCAE.Muniforme << VecCCAE.Mdiverso << VecCCAE.Mestatico << VecCCAE.Mincremento << VecCCAE.MTS
                << VecCCAE.MTE << VecCCAE.MWCP << VecCCAE.MDTmin ;
}

QDataStream &operator>>(QDataStream &in7, VecPlot_CurvasCompuestasAjustadasEstatico &VecCCAE)
{
    return in7 >> VecCCAE.Muniforme >> VecCCAE.Mdiverso >> VecCCAE.Mestatico >> VecCCAE.Mincremento >> VecCCAE.MTS
               >> VecCCAE.MTE >> VecCCAE.MWCP >> VecCCAE.MDTmin ;
}

VecPlot_CurvasCompuestasAjustadasIncremento::VecPlot_CurvasCompuestasAjustadasIncremento(bool uniforme, bool diverso, bool estatico, bool incremento,
                                                   QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                                                   double Min, double Max, double Inc)
{
    MMin = Min;
    MMax = Max;
    MInc = Inc;
    Muniforme = uniforme;
    Mdiverso = diverso;
    Mestatico = estatico;
    Mincremento = incremento;
    MTS.resize(TS.size());
    MTE.resize(TE.size());
    MWCP.resize(Wcp.size());
    for(int i = 0; i < TS.size(); i++){
        MTS[i] = TS[i];
    }
    for(int i = 0; i < TE.size(); i++){
        MTE[i] = TE[i];
    }
    for(int i = 0; i < Wcp.size(); i++){
        MWCP[i] = Wcp[i];
    }
}

bool VecPlot_CurvasCompuestasAjustadasIncremento::getUniforme() const
{
    return Muniforme;
}

bool VecPlot_CurvasCompuestasAjustadasIncremento::getDiverso() const
{
    return Mdiverso;
}

bool VecPlot_CurvasCompuestasAjustadasIncremento::getEstatico() const
{
    return Mestatico;
}

bool VecPlot_CurvasCompuestasAjustadasIncremento::getIncremmento() const
{
    return Mincremento;
}

double VecPlot_CurvasCompuestasAjustadasIncremento::getMin() const
{
    return MMin;
}

double VecPlot_CurvasCompuestasAjustadasIncremento::getMax() const
{
    return MMax;
}

double VecPlot_CurvasCompuestasAjustadasIncremento::getInc() const
{
    return MInc;
}

QVector<double> VecPlot_CurvasCompuestasAjustadasIncremento::getTS() const
{
    return MTS;
}

QVector<double> VecPlot_CurvasCompuestasAjustadasIncremento::getTE() const
{
    return MTE;
}

QVector<double> VecPlot_CurvasCompuestasAjustadasIncremento::getWCP() const
{
    return MWCP;
}

QDataStream &operator<<(QDataStream &out8, const VecPlot_CurvasCompuestasAjustadasIncremento &VecCCAI)
{
    return out8 << VecCCAI.Muniforme << VecCCAI.Mdiverso << VecCCAI.Mestatico << VecCCAI.Mincremento
                << VecCCAI.MTS << VecCCAI.MTE << VecCCAI.MWCP << VecCCAI.MMin << VecCCAI.MMax << VecCCAI.MInc ;
}

QDataStream &operator>>(QDataStream &in8, VecPlot_CurvasCompuestasAjustadasIncremento &VecCCAI)
{
    return in8 >> VecCCAI.Muniforme >> VecCCAI.Mdiverso >> VecCCAI.Mestatico >> VecCCAI.Mincremento
               >> VecCCAI.MTS >> VecCCAI.MTE >> VecCCAI.MWCP >> VecCCAI.MMin >> VecCCAI.MMax >> VecCCAI.MInc ;
}

VecPlot_CurvasCompuestasAjustadasbool::VecPlot_CurvasCompuestasAjustadasbool(bool uniforme, bool diverso,
                                                                             bool estatico, bool incremento)
{
    Muniforme = uniforme;
    Mdiverso = diverso;
    Mestatico = estatico;
    Mincremento = incremento;
}

bool VecPlot_CurvasCompuestasAjustadasbool::getUniforme() const
{
    return Muniforme;
}

bool VecPlot_CurvasCompuestasAjustadasbool::getDiverso() const
{
    return Mdiverso;
}

bool VecPlot_CurvasCompuestasAjustadasbool::getEstatico() const
{
    return Mestatico;
}

bool VecPlot_CurvasCompuestasAjustadasbool::getIncremmento() const
{
    return Mincremento;
}


QDataStream &operator<<(QDataStream &out9, const VecPlot_CurvasCompuestasAjustadasbool &VecCCAB)
{
     return out9 << VecCCAB.Muniforme << VecCCAB.Mdiverso << VecCCAB.Mestatico << VecCCAB.Mincremento ;
}

QDataStream &operator>>(QDataStream &in9, VecPlot_CurvasCompuestasAjustadasbool &VecCCAB)
{
    return in9 >> VecCCAB.Muniforme >> VecCCAB.Mdiverso >> VecCCAB.Mestatico >> VecCCAB.Mincremento ;
}



VecGCCbool::VecGCCbool(bool uniforme, bool diverso, bool estatico, bool incremento)
{
    Muniforme = uniforme;
    Mdiverso = diverso;
    Mestatico = estatico;
    Mincremento = incremento;
}

bool VecGCCbool::getUniforme() const
{
    return Muniforme;
}

bool VecGCCbool::getDiverso() const
{
    return Mdiverso;
}

bool VecGCCbool::getEstatico() const
{
    return Mestatico;
}

bool VecGCCbool::getIncremmento() const
{
    return Mincremento;
}

QDataStream &operator<<(QDataStream &out10, const VecGCCbool &VecGCCbools)
{
    return out10 << VecGCCbools.Muniforme << VecGCCbools.Mdiverso << VecGCCbools.Mestatico << VecGCCbools.Mincremento ;
}

QDataStream &operator>>(QDataStream &in10, VecGCCbool &VecGCCbools)
{
    return in10 >> VecGCCbools.Muniforme >> VecGCCbools.Mdiverso >> VecGCCbools.Mestatico >> VecGCCbools.Mincremento ;
}


VecGCCestatico::VecGCCestatico(bool uniforme, bool diverso, bool estatico, bool incremento,
                               QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp, double DTmin)
{
    Muniforme = uniforme;
    Mdiverso = diverso;
    Mestatico = estatico;
    Mincremento = incremento;
    MDTmin = DTmin;
    MTS.resize(TS.size());
    MTE.resize(TE.size());
    MWCP.resize(Wcp.size());
    for(int i = 0; i < TS.size(); i++){
        MTS[i] = TS[i];
    }
    for(int i = 0; i < TE.size(); i++){
        MTE[i] = TE[i];
    }
    for(int i = 0; i < Wcp.size(); i++){
        MWCP[i] = Wcp[i];
    }
}

bool VecGCCestatico::getUniforme() const
{
    return Muniforme;
}

bool VecGCCestatico::getDiverso() const
{
    return Mdiverso;
}

bool VecGCCestatico::getEstatico() const
{
    return Mestatico;
}

bool VecGCCestatico::getIncremmento() const
{
    return Mincremento;
}

double VecGCCestatico::getDTmin() const
{
    return MDTmin;
}

QVector<double> VecGCCestatico::getTS() const
{
    return MTS;
}

QVector<double> VecGCCestatico::getTE() const
{
    return MTE;
}

QVector<double> VecGCCestatico::getWCP() const
{
    return MWCP;
}

QDataStream &operator<<(QDataStream &out11, const VecGCCestatico &VecGCest)
{
    return out11 << VecGCest.Muniforme << VecGCest.Mdiverso << VecGCest.Mestatico << VecGCest.Mincremento
                 << VecGCest.MDTmin << VecGCest.MTS << VecGCest.MTE << VecGCest.MWCP;
}

QDataStream &operator>>(QDataStream &in11, VecGCCestatico &VecGCest)
{
    return in11 >> VecGCest.Muniforme >> VecGCest.Mdiverso >> VecGCest.Mestatico >> VecGCest.Mincremento
                >> VecGCest.MDTmin >> VecGCest.MTS >> VecGCest.MTE >> VecGCest.MWCP;
}


VecGCCdinamico::VecGCCdinamico(bool uniforme, bool diverso, bool estatico, bool incremento,
                               QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                               double Min, double Max, double Inc)
{
    Muniforme = uniforme;
    Mdiverso = diverso;
    Mestatico = estatico;
    Mincremento = incremento;
    MMin = Min;
    MMax = Max;
    MInc = Inc;
    MTS.resize(TS.size());
    MTE.resize(TE.size());
    MWCP.resize(Wcp.size());
    for(int i = 0; i < TS.size(); i++){
        MTS[i] = TS[i];
    }
    for(int i = 0; i < TE.size(); i++){
        MTE[i] = TE[i];
    }
    for(int i = 0; i < Wcp.size(); i++){
        MWCP[i] = Wcp[i];
    }
}

bool VecGCCdinamico::getUniforme() const
{
    return Muniforme;
}

bool VecGCCdinamico::getDiverso() const
{
    return Mdiverso;
}

bool VecGCCdinamico::getEstatico() const
{
    return Mestatico;
}

bool VecGCCdinamico::getIncremmento() const
{
    return Mincremento;
}

double VecGCCdinamico::getMin() const
{
    return MMin;
}

double VecGCCdinamico::getMax() const
{
    return MMax;
}

double VecGCCdinamico::getInc() const
{
    return MInc;
}

QVector<double> VecGCCdinamico::getTS() const
{
    return MTS;
}

QVector<double> VecGCCdinamico::getTE() const
{
    return MTE;
}

QVector<double> VecGCCdinamico::getWCP() const
{
    return MWCP;
}

QDataStream &operator<<(QDataStream &out12, const VecGCCdinamico &VecGCdin)
{
    return out12 << VecGCdin.Muniforme << VecGCdin.Mdiverso << VecGCdin.Mestatico << VecGCdin.Mincremento
                 << VecGCdin.MMin << VecGCdin.MMax << VecGCdin.MInc << VecGCdin.MTS << VecGCdin.MTE << VecGCdin.MWCP;
}

QDataStream &operator>>(QDataStream &in12, VecGCCdinamico &VecGCdin)
{
    return in12 >> VecGCdin.Muniforme >> VecGCdin.Mdiverso >> VecGCdin.Mestatico >> VecGCdin.Mincremento
                >> VecGCdin.MMin >> VecGCdin.MMax >> VecGCdin.MInc >> VecGCdin.MTS >> VecGCdin.MTE >> VecGCdin.MWCP;
}

VecPlot_CCAjustadasEst_Diversa::VecPlot_CCAjustadasEst_Diversa(bool uniforme, bool diverso, bool estatico, bool incremento,
                                                                         QVector<double> &TS, QVector<double> &TE,
                                                                         QVector<double> &Wcp, QVector<double> &h,
                                                                         double DTmin,double K)
{
    Muniforme = uniforme;
    Mdiverso = diverso;
    Mestatico = estatico;
    Mincremento = incremento;
    MDTmin = DTmin;
    MTS.resize(TS.size());
    MTE.resize(TE.size());
    MWCP.resize(Wcp.size());
    Mh.resize(h.size());
    for(int i = 0; i < TS.size(); i++){
        MTS[i] = TS[i];
    }
    for(int i = 0; i < TE.size(); i++){
        MTE[i] = TE[i];
    }
    for(int i = 0; i < Wcp.size(); i++){
        MWCP[i] = Wcp[i];
    }
    for(int i = 0; i < Wcp.size(); i++){
        Mh[i] = h[i];
    }
    MK = K;
}

bool VecPlot_CCAjustadasEst_Diversa::getUniforme() const
{
    return Muniforme;
}

bool VecPlot_CCAjustadasEst_Diversa::getDiverso() const
{
    return Mdiverso;
}

bool VecPlot_CCAjustadasEst_Diversa::getEstatico() const
{
    return Mestatico;
}

bool VecPlot_CCAjustadasEst_Diversa::getIncremmento() const
{
    return Mincremento;
}

double VecPlot_CCAjustadasEst_Diversa::getDTmin() const
{
    return MDTmin;
}

double VecPlot_CCAjustadasEst_Diversa::getK() const
{
    return MK;
}

QVector<double> VecPlot_CCAjustadasEst_Diversa::getTS() const
{
    return MTS;
}

QVector<double> VecPlot_CCAjustadasEst_Diversa::getTE() const
{
    return MTE;
}

QVector<double> VecPlot_CCAjustadasEst_Diversa::getWCP() const
{
    return MWCP;
}

QVector<double> VecPlot_CCAjustadasEst_Diversa::geth() const
{
    return Mh;
}

QDataStream &operator<<(QDataStream &out13, const VecPlot_CCAjustadasEst_Diversa &VecCCAED)
{
    return out13 << VecCCAED.Muniforme << VecCCAED.Mdiverso << VecCCAED.Mestatico << VecCCAED.Mincremento
                 << VecCCAED.MDTmin << VecCCAED.MK << VecCCAED.MTS << VecCCAED.MTE << VecCCAED.MWCP << VecCCAED.Mh;
}

QDataStream &operator>>(QDataStream &in13, VecPlot_CCAjustadasEst_Diversa &VecCCAED)
{
    return in13 >> VecCCAED.Muniforme >> VecCCAED.Mdiverso >> VecCCAED.Mestatico >> VecCCAED.Mincremento
                >> VecCCAED.MDTmin >> VecCCAED.MK >> VecCCAED.MTS >> VecCCAED.MTE >> VecCCAED.MWCP >> VecCCAED.Mh;
}

VecPlot_CCAjustadasInc_Diversa::VecPlot_CCAjustadasInc_Diversa(bool uniforme, bool diverso,
                                                               bool estatico, bool incremento,
                                                               QVector<double> &TS, QVector<double> &TE,
                                                               QVector<double> &Wcp, QVector<double> &h,
                                                               double min, double max, double inc, double K)
{
    Muniforme = uniforme;
    Mdiverso = diverso;
    Mestatico = estatico;
    Mincremento = incremento;
    MMin = min;
    MMax = max;
    MInc = inc;
    MTS.resize(TS.size());
    MTE.resize(TE.size());
    MWCP.resize(Wcp.size());
    Mh.resize(h.size());
    for(int i = 0; i < TS.size(); i++){
        MTS[i] = TS[i];
    }
    for(int i = 0; i < TE.size(); i++){
        MTE[i] = TE[i];
    }
    for(int i = 0; i < Wcp.size(); i++){
        MWCP[i] = Wcp[i];
    }
    for(int i = 0; i < Wcp.size(); i++){
        Mh[i] = h[i];
    }
    MK = K;
}

bool VecPlot_CCAjustadasInc_Diversa::getUniforme() const
{
    return Muniforme;
}

bool VecPlot_CCAjustadasInc_Diversa::getDiverso() const
{
    return Mdiverso;
}

bool VecPlot_CCAjustadasInc_Diversa::getEstatico() const
{
    return Mestatico;
}

bool VecPlot_CCAjustadasInc_Diversa::getIncremmento() const
{
    return Mincremento;
}

double VecPlot_CCAjustadasInc_Diversa::getMin() const
{
    return MMin;
}

double VecPlot_CCAjustadasInc_Diversa::getMax() const
{
    return MMax;
}

double VecPlot_CCAjustadasInc_Diversa::getInc() const
{
    return MInc;
}

double VecPlot_CCAjustadasInc_Diversa::getK() const
{
    return MK;
}

QVector<double> VecPlot_CCAjustadasInc_Diversa::getTS() const
{
    return MTS;
}

QVector<double> VecPlot_CCAjustadasInc_Diversa::getTE() const
{
    return MTE;
}

QVector<double> VecPlot_CCAjustadasInc_Diversa::getWCP() const
{
    return MWCP;
}

QVector<double> VecPlot_CCAjustadasInc_Diversa::geth() const
{
    return Mh;
}

QDataStream &operator<<(QDataStream &out14, const VecPlot_CCAjustadasInc_Diversa &VecCCAID)
{
    return out14 << VecCCAID.Muniforme << VecCCAID.Mdiverso << VecCCAID.Mestatico << VecCCAID.Mincremento
                 << VecCCAID.MMin << VecCCAID.MMax << VecCCAID.MInc << VecCCAID.MK << VecCCAID.MTS
                 << VecCCAID.MTE << VecCCAID.MWCP << VecCCAID.Mh;
}

QDataStream &operator>>(QDataStream &in14, VecPlot_CCAjustadasInc_Diversa &VecCCAID)
{
    return in14  >> VecCCAID.Muniforme >> VecCCAID.Mdiverso >> VecCCAID.Mestatico >> VecCCAID.Mincremento
                 >> VecCCAID.MMin >> VecCCAID.MMax >> VecCCAID.MInc >> VecCCAID.MK >> VecCCAID.MTS
                 >> VecCCAID.MTE >> VecCCAID.MWCP >> VecCCAID.Mh;
}
