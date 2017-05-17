#ifndef DUVALORACTION_H
#define DUVALORACTION_H
#include <QDataStream>
#include <QVector>
#include <QDebug>
#include <qalgorithms.h>

//FUNCIONA
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
    void ConvertirUnidades(QVector<double> ST, QVector<double> TT, QVector<double> Cp, bool SI, bool SIN, int A, int B);
    QVector<double> getST();
    QVector<double> getTT();
    QVector<double> getCp();
    //VOID CONVERTIR UNIDAES
    friend QDataStream &operator<<(QDataStream &out3, const Unidades &units);
    friend QDataStream &operator>>(QDataStream &in3, Unidades &units);

private:
    QVector<double> MST,MTT,MCp,Mh;
    bool MSI,MSIS;
    int  MUTemp,MUWcp,MUh, MA, MB ,MC;
};
QDataStream &operator<<(QDataStream &out3, const Unidades &units);
QDataStream &operator>>(QDataStream &in3, Unidades &units);

//FUNCIONA

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

//FUNCIONA

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

class VecPlot_CurvasCompuestas
{
public:
    VecPlot_CurvasCompuestas(bool uniforme, bool diverso, bool estatico, bool incremento,
                             QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                             QVector<double> &h,
                             double Min, double Max,
                             double Inc, double K);
    //,uniforme,diverso,estatico,incremento,TS,TE,Wcp
    bool getUniforme() const;
    bool getDiverso() const;
    bool getEstatico() const;
    bool getIncremmento() const;
    double getMin() const;
    double getMax() const;
    double getInc() const;
    double getK() const;
    QVector<double> getTS() const;
    QVector<double> getTE() const;
    QVector<double> getWCP() const;
    QVector<double> geth() const;
    friend QDataStream &operator<<(QDataStream &out6, const VecPlot_CurvasCompuestas &VecCC);
    friend QDataStream &operator>>(QDataStream &in6, VecPlot_CurvasCompuestas &VecCC);
private:
    bool Muniforme,Mdiverso,Mestatico,Mincremento;
    double MMin,MMax,MInc,MK;
    QVector<double> MTS;
    QVector<double> MTE;
    QVector<double> MWCP;
    QVector<double> Mh;
};
QDataStream &operator<<(QDataStream &out6, const VecPlot_CurvasCompuestas &VecCC);
QDataStream &operator>>(QDataStream &in6, VecPlot_CurvasCompuestas &VecCC);

class VecPlot_CurvasCompuestasAjustadasEstatico
{
public:
    VecPlot_CurvasCompuestasAjustadasEstatico(bool uniforme, bool diverso, bool estatico, bool incremento,
                             QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                             double DTmin);
    //,uniforme,diverso,estatico,incremento,TS,TE,Wcp
    bool getUniforme() const;
    bool getDiverso() const;
    bool getEstatico() const;
    bool getIncremmento() const;
    double getDTmin() const;
    QVector<double> getTS() const;
    QVector<double> getTE() const;
    QVector<double> getWCP() const;
    friend QDataStream &operator<<(QDataStream &out7, const VecPlot_CurvasCompuestasAjustadasEstatico &VecCCAE);
    friend QDataStream &operator>>(QDataStream &in7, VecPlot_CurvasCompuestasAjustadasEstatico &VecCCAE);
private:
    bool Muniforme,Mdiverso,Mestatico,Mincremento;
    double MDTmin;
    QVector<double> MTS;
    QVector<double> MTE;
    QVector<double> MWCP;
};
QDataStream &operator<<(QDataStream &out7, const VecPlot_CurvasCompuestasAjustadasEstatico &VecCCAE);
QDataStream &operator>>(QDataStream &in7, VecPlot_CurvasCompuestasAjustadasEstatico &VecCCAE);

class VecPlot_CurvasCompuestasAjustadasIncremento
{
public:
    VecPlot_CurvasCompuestasAjustadasIncremento(bool uniforme, bool diverso, bool estatico, bool incremento,
                             QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                             double Min, double Max, double Inc);
    //,uniforme,diverso,estatico,incremento,TS,TE,Wcp
    bool getUniforme() const;
    bool getDiverso() const;
    bool getEstatico() const;
    bool getIncremmento() const;
    double getMin() const;
    double getMax() const;
    double getInc() const;
    QVector<double> getTS() const;
    QVector<double> getTE() const;
    QVector<double> getWCP() const;
    friend QDataStream &operator<<(QDataStream &out8, const VecPlot_CurvasCompuestasAjustadasIncremento &VecCCAI);
    friend QDataStream &operator>>(QDataStream &in8, VecPlot_CurvasCompuestasAjustadasIncremento &VecCCAI);
private:
    bool Muniforme,Mdiverso,Mestatico,Mincremento;
    double MMin,MMax,MInc;
    QVector<double> MTS;
    QVector<double> MTE;
    QVector<double> MWCP;
};
QDataStream &operator<<(QDataStream &out8, const VecPlot_CurvasCompuestasAjustadasIncremento &VecCCAI);
QDataStream &operator>>(QDataStream &in8, VecPlot_CurvasCompuestasAjustadasIncremento &VecCCAI);

class VecPlot_CurvasCompuestasAjustadasbool
{
public:
    VecPlot_CurvasCompuestasAjustadasbool(bool uniforme, bool diverso, bool estatico, bool incremento);
    bool getUniforme() const;
    bool getDiverso() const;
    bool getEstatico() const;
    bool getIncremmento() const;
    friend QDataStream &operator<<(QDataStream &out9, const VecPlot_CurvasCompuestasAjustadasbool &VecCCAB);
    friend QDataStream &operator>>(QDataStream &in9, VecPlot_CurvasCompuestasAjustadasbool &VecCCAB);
private:
    bool Muniforme,Mdiverso,Mestatico,Mincremento;
};
QDataStream &operator<<(QDataStream &out9, const VecPlot_CurvasCompuestasAjustadasbool &VecCCAB);
QDataStream &operator>>(QDataStream &in9, VecPlot_CurvasCompuestasAjustadasbool &VecCCAB);

class VecGCCbool
{
public:
    VecGCCbool(bool uniforme, bool diverso, bool estatico, bool incremento);
    bool getUniforme() const;
    bool getDiverso() const;
    bool getEstatico() const;
    bool getIncremmento() const;
    friend QDataStream &operator<<(QDataStream &out10, const VecGCCbool &VecGCCbools);
    friend QDataStream &operator>>(QDataStream &in10, VecGCCbool &VecGCCbools);
private:
    bool Muniforme,Mdiverso,Mestatico,Mincremento;
};
QDataStream &operator<<(QDataStream &out10, const VecGCCbool &VecGCCbools);
QDataStream &operator>>(QDataStream &in10, VecGCCbool &VecGCCbools);

class VecGCCestatico
{
public:
    VecGCCestatico(bool uniforme, bool diverso, bool estatico, bool incremento,
                             QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                             double DTmin);
    bool getUniforme() const;
    bool getDiverso() const;
    bool getEstatico() const;
    bool getIncremmento() const;
    double getDTmin() const;
    QVector<double> getTS() const;
    QVector<double> getTE() const;
    QVector<double> getWCP() const;
    friend QDataStream &operator<<(QDataStream &out11, const VecGCCestatico &VecGCest);
    friend QDataStream &operator>>(QDataStream &in11, VecGCCestatico &VecGCest);
private:
    bool Muniforme,Mdiverso,Mestatico,Mincremento;
    double MDTmin;
    QVector<double> MTS;
    QVector<double> MTE;
    QVector<double> MWCP;
};
QDataStream &operator<<(QDataStream &out11, const VecGCCestatico &VecGCest);
QDataStream &operator>>(QDataStream &in11, VecGCCestatico &VecGCest);

class VecGCCdinamico
{
public:
    VecGCCdinamico(bool uniforme, bool diverso, bool estatico, bool incremento,
                             QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                             double Min, double Max,double Inc);
    bool getUniforme() const;
    bool getDiverso() const;
    bool getEstatico() const;
    bool getIncremmento() const;
    double getMin() const;
    double getMax() const;
    double getInc() const;
    QVector<double> getTS() const;
    QVector<double> getTE() const;
    QVector<double> getWCP() const;
    friend QDataStream &operator<<(QDataStream &out12, const VecGCCdinamico &VecGCdin);
    friend QDataStream &operator>>(QDataStream &in12, VecGCCdinamico &VecGCdin);
private:
    bool Muniforme,Mdiverso,Mestatico,Mincremento;
    double MMin,MMax,MInc;
    QVector<double> MTS;
    QVector<double> MTE;
    QVector<double> MWCP;
};
QDataStream &operator<<(QDataStream &out12, const VecGCCdinamico &VecGCdin);
QDataStream &operator>>(QDataStream &in12, VecGCCdinamico &VecGCdin);

class VecPlot_CCAjustadasEst_Diversa
{
public:
    VecPlot_CCAjustadasEst_Diversa(bool uniforme, bool diverso, bool estatico, bool incremento,
                                   QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                                   QVector<double> &h, double DTmin,double K);
    bool getUniforme() const;
    bool getDiverso() const;
    bool getEstatico() const;
    bool getIncremmento() const;
    double getDTmin() const;
    double getK() const;
    QVector<double> getTS() const;
    QVector<double> getTE() const;
    QVector<double> getWCP() const;
    QVector<double> geth() const;
    friend QDataStream &operator<<(QDataStream &out13, const VecPlot_CCAjustadasEst_Diversa &VecCCAED);
    friend QDataStream &operator>>(QDataStream &in13, VecPlot_CCAjustadasEst_Diversa &VecCCAED);
private:
    bool Muniforme,Mdiverso,Mestatico,Mincremento;
    double MDTmin;
    double MK;
    QVector<double> MTS;
    QVector<double> MTE;
    QVector<double> MWCP;
    QVector<double> Mh;
};
QDataStream &operator<<(QDataStream &out13, const VecPlot_CCAjustadasEst_Diversa &VecCCAED);
QDataStream &operator>>(QDataStream &in13, VecPlot_CCAjustadasEst_Diversa &VecCCAED);


class VecPlot_CCAjustadasInc_Diversa
{
public:
    VecPlot_CCAjustadasInc_Diversa(bool uniforme, bool diverso, bool estatico, bool incremento,
                                   QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                                   QVector<double> &h, double min, double max, double inc ,double K);
    bool getUniforme() const;
    bool getDiverso() const;
    bool getEstatico() const;
    bool getIncremmento() const;
    double getMin() const;
    double getMax() const;
    double getInc() const;
    double getK() const;
    QVector<double> getTS() const;
    QVector<double> getTE() const;
    QVector<double> getWCP() const;
    QVector<double> geth() const;
    friend QDataStream &operator<<(QDataStream &out14, const VecPlot_CCAjustadasInc_Diversa &VecCCAID);
    friend QDataStream &operator>>(QDataStream &in14, VecPlot_CCAjustadasInc_Diversa &VecCCAID);
private:
    bool Muniforme,Mdiverso,Mestatico,Mincremento;
    double MMin,MMax,MInc,MK;
    QVector<double> MTS,MTE,MWCP,Mh;
};
QDataStream &operator<<(QDataStream &out14, const VecPlot_CCAjustadasInc_Diversa &VecCCAID);
QDataStream &operator>>(QDataStream &in14, VecPlot_CCAjustadasInc_Diversa &VecCCAID);

class VecGCCED
{
public:
    VecGCCED(bool uniforme, bool diverso, bool estatico, bool incremento,
                             QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                             QVector<double> &h ,double DTmin,double K);
    bool getUniforme() const;
    bool getDiverso() const;
    bool getEstatico() const;
    bool getIncremmento() const;
    double getDTmin() const;
    double getK() const;
    QVector<double> getTS() const;
    QVector<double> getTE() const;
    QVector<double> getWCP() const;
    QVector<double> geth() const;
    friend QDataStream &operator<<(QDataStream &out15, const VecGCCED &GCCED);
    friend QDataStream &operator>>(QDataStream &in15, VecGCCED &GCCED);
private:
    bool Muniforme,Mdiverso,Mestatico,Mincremento;
    double MDTmin, MK;
    QVector<double> MTS, MTE, MWCP, Mh;
};
QDataStream &operator<<(QDataStream &out15, const VecGCCED &GCCED);
QDataStream &operator>>(QDataStream &in15, VecGCCED &GCCED);

class VecGCCDD
{
public:
    VecGCCDD(bool uniforme, bool diverso, bool estatico, bool incremento,
                             QVector<double> &TS, QVector<double> &TE, QVector<double> &Wcp,
                             QVector<double> &h ,double Min,double Max, double Inc,double K);
    bool getUniforme() const;
    bool getDiverso() const;
    bool getEstatico() const;
    bool getIncremmento() const;
    double getMin() const;
    double getMax() const;
    double getInc() const;
    double getK() const;
    QVector<double> getTS() const;
    QVector<double> getTE() const;
    QVector<double> getWCP() const;
    QVector<double> geth() const;
    friend QDataStream &operator<<(QDataStream &out16, const VecGCCDD &GCCDD);
    friend QDataStream &operator>>(QDataStream &in16, VecGCCDD &GCCDD);
private:
    bool Muniforme,Mdiverso,Mestatico,Mincremento;
    double MMin,MMax,MInc,MK;
    QVector<double> MTS, MTE, MWCP, Mh;
};
QDataStream &operator<<(QDataStream &out16, const VecGCCDD &GCCDD);
QDataStream &operator>>(QDataStream &in16, VecGCCDD &GCCDD);

class VecAreasUniforme
{
public:
    VecAreasUniforme(bool uniforme, bool diverso,
                     QVector<double> &TS, QVector<double> &TE,
                     QVector<double> &Wcp,QVector<double> &h ,
                     QVector<double> &Calentamiento, QVector<double> &Enfriamento,
                     double Min,double Max, double Inc, int CTo,int CCo);
    bool getUniforme() const;
    bool getDiverso() const;
    double getMin() const;
    double getMax() const;
    double getInc() const;
    int getCTo() const;
    int getCCo() const;
    QVector<double> getTS() const;
    QVector<double> getTE() const;
    QVector<double> getWCP() const;
    QVector<double> geth() const;
    QVector<double> getCalentamiento() const;
    QVector<double> getEnfriamento() const;
    friend QDataStream &operator<<(QDataStream &out17, const VecAreasUniforme &VAU);
    friend QDataStream &operator>>(QDataStream &in17, VecAreasUniforme &VAU);
private:
    bool Muniforme,Mdiverso;
    double MMin, MMax, MInc, MCTo, MCCo;
    QVector<double> MTS, MTE, MWCP, Mh , MCalentamiento, MEnfriamento;
};
QDataStream &operator<<(QDataStream &out17, const VecAreasUniforme &VAU);
QDataStream &operator>>(QDataStream &in17, VecAreasUniforme &VAU);

class VecAreasUniformebool
{
public:
    VecAreasUniformebool(bool uniforme, bool diverso);
    bool getUniforme() const;
    bool getDiverso() const;
    friend QDataStream &operator<<(QDataStream &out18, const VecAreasUniformebool &VecAUB);
    friend QDataStream &operator>>(QDataStream &in18, VecAreasUniformebool &VecAUB);
private:
    bool Muniforme,Mdiverso;
};
QDataStream &operator<<(QDataStream &out18, const VecAreasUniformebool &VecAUB);
QDataStream &operator>>(QDataStream &in18, VecAreasUniformebool &VecAUB);

class VecAreasDiverso
{
public:
    VecAreasDiverso(bool uniforme, bool diverso,
                     QVector<double> &TS, QVector<double> &TE,
                     QVector<double> &Wcp,QVector<double> &h ,
                     QVector<double> &Calentamiento, QVector<double> &Enfriamento,
                     double Min,double Max, double Inc, double K, int CTo,int CCo);
    bool getUniforme() const;
    bool getDiverso() const;
    double getMin() const;
    double getMax() const;
    double getInc() const;
    double getK() const;
    int getCTo() const;
    int getCCo() const;
    QVector<double> getTS() const;
    QVector<double> getTE() const;
    QVector<double> getWCP() const;
    QVector<double> geth() const;
    QVector<double> getCalentamiento() const;
    QVector<double> getEnfriamento() const;
    friend QDataStream &operator<<(QDataStream &out19, const VecAreasDiverso &VAD);
    friend QDataStream &operator>>(QDataStream &in19, VecAreasDiverso &VAD);
private:
    bool Muniforme,Mdiverso;
    double MMin, MMax, MInc, MCTo, MCCo,MK;
    QVector<double> MTS, MTE, MWCP, Mh , MCalentamiento, MEnfriamento;
};
QDataStream &operator<<(QDataStream &out19, const VecAreasDiverso &VAD);
QDataStream &operator>>(QDataStream &in19, VecAreasDiverso &VAD);

#endif // DUVALORACTION_H
