#ifndef DUVALORACTION_H
#define DUVALORACTION_H
#include <QDataStream>
#include <QVector>
#include <QDebug>
//FUNCIONAS
class Duvaloraction
{
public:
    Duvaloraction(int valact = -1);
    void setvalact(int valact);
    int getvalact() const;

    friend QDataStream &operator<<(QDataStream &out1,const Duvaloraction &valoraction);
    friend QDataStream &operator>>(QDataStream &in1, Duvaloraction &valoraction);

private:
    int Mvalact;
};
QDataStream &operator<<(QDataStream &out1, const Duvaloraction &valor); //salida
QDataStream &operator>>(QDataStream &in1, Duvaloraction &valoraction); //entrada

//FUNCIONA

class Workspace
{
public:
    Workspace(QVector<QVector<double> > &matriz);
    QVector<QVector<double>> getMatriz() const;
    friend QDataStream &operator<<(QDataStream &out2, const Workspace &MATRIZ );
    friend QDataStream &operator>>(QDataStream &in2, Workspace &MATRIZ);
private:
    QVector<QVector<double>> MMatriz;
    QVector<QVector<double>> matriz;
};
QDataStream &operator<<(QDataStream &out2, const Workspace &MATRIZ);
QDataStream &operator>>(QDataStream &in2, Workspace &MATRIZ);


//FUNCIONA

class Unidades
{
public:
    Unidades(bool SI = false, bool SIS = false, int UTemp = -1, int UWcp= -1, int Uh =-1 );
    bool getSI();
    bool getSIS();
    int getUTemp();
    int getUWcp();
    int getUh();
    //VOID CONVERTIR UNIDAES
    friend QDataStream &operator<<(QDataStream &out3, const Unidades &units);
    friend QDataStream &operator>>(QDataStream &in3, Unidades &units);

private:
    bool MSI,MSIS;
    int  MUTemp,MUWcp,MUh;
};
QDataStream &operator<<(QDataStream &out3, const Unidades &units);
QDataStream &operator>>(QDataStream &in3, Unidades &units);


class Tabplot
{
public:
    Tabplot(int tabvalue = -1);
    void settabvalue(int tabvalue);
    int gettabvalue();
    friend QDataStream &operator<<(QDataStream &out4, const Tabplot &tabvalue);
    friend QDataStream &operator>>(QDataStream &in4, Tabplot &tabvalue);
private:
    int Mtabvalue;
};
QDataStream &operator<<(QDataStream &out4, const Tabplot &tabvalue);
QDataStream &operator>>(QDataStream &in4, Tabplot &tabvalue);

//NIIDEA

class Valordeoperacion
{
public:
    Valordeoperacion(int valor = -1);
    void setvalor(int valor);
    int getvalor() const;
    friend QDataStream &operator<<(QDataStream &out5, const Valordeoperacion &valor);
    friend QDataStream &operator>>(QDataStream &in5, Valordeoperacion &valor);
private:
    int Mvalor;
};
QDataStream &operator<<(QDataStream &out5, const Valordeoperacion &valor);
QDataStream &operator>>(QDataStream &in5, Valordeoperacion &valor);

// NI IDEA
class Operaciones
{
public:
    Operaciones(int tabval,int method,int analisis,int dtmin,int maximo,int minimo,int k,QVector<QVector<double>> Matriz);
    //void operaciones(int tipo,int method,int analisis,int dtmin,int maximo,int minimo,int k,QVector<QVector<double>> Matriz);
private:
    int Mtabval,Mmethod,Manalisis,Mdtmin,Mmaximo,Mminimo,Mk,Mtipo;
    QVector<QVector<double>> MMatriz;
};
//DUVALORACTION


#endif // DUVALORACTION_H
