#include "duvaloraction.h"
#include <QVector>

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

//FALTA POR DEFINIR LAS OPERACIONES

Operaciones::Operaciones(int tabval, int method, int analisis, int dtmin, int maximo, int minimo,
                         int k, QVector<QVector<double> > Matriz)
{
    Mtabval= tabval;
    Mmethod= method;
    Manalisis = analisis;
    Mdtmin = dtmin;
    Mmaximo = maximo;
    Mminimo = minimo;
    Mk = k;
    MMatriz = Matriz;
}

//void Operaciones::operaciones(int tipo, int method, int analisis, int dtmin, int maximo, int minimo, int k, QVector<QVector<double> > Matriz)
//{
//    // aun si declarar nada
//}

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

