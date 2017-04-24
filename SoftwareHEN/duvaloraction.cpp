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

