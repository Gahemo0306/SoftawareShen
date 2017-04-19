#include "graficos.h"
#include <QVector>
//#include <qalgorithms.h>
#include <QtMath>
#include <QDebug>
//#include <QtAlgorithms>
#include <algorithm>

using namespace std;

Graficos::Graficos()
{

}


Plot_curvascompuestas::Plot_curvascompuestas(QVector<double> Tsupply, QVector<double> Ttarget,
                                             QVector<double> Cp)
{
    //qDebug() << Tsupply << Ttarget << Cp;
    QVector<double> VCC ,VFC, VectorCalientes, VectorCalientesCp;
    QVector<double> VectorFrias,VectorFriasCp, VCCurvas,VFCurvas;
    int i,j,n,nfils,ncols,Pares,contador,k;
    n = Tsupply.size();
    for (i = 0; i < n ; ++i)
    {
        if(Tsupply[i] >= Ttarget[i])
        {
            VectorCalientesCp << Tsupply[i] << Ttarget[i] << Cp[i] ;//<< h[i];
            VectorCalientes << Tsupply[i] << Ttarget[i];
        }
        if(Tsupply[i] <= Ttarget[i])
        {
            VectorFriasCp << Tsupply[i] << Ttarget[i] << Cp[i] ;//<< h[i];
            VectorFrias << Tsupply[i] << Ttarget[i];
        }
        j++;
    }
    //qDebug() << VectorCalientes << VectorCalientesCp << VectorFrias << VectorFriasCp;
    QVector < QVector <double> > VectorCalientesMATRIZ;
    Pares = VectorCalientesCp.size();
    nfils = Pares/3;
    ncols = 3;
    VectorCalientesMATRIZ.resize(nfils);
    for(i = 0; i< VectorCalientesMATRIZ.size(); i++)
    {
        VectorCalientesMATRIZ[i].resize(ncols);
    }
    contador = 0;
    for(int i = 0; i < VectorCalientesMATRIZ.size(); i++)
    {
        for(int j = 0; j < VectorCalientesMATRIZ.at(i).size(); j++)
        {
            VectorCalientesMATRIZ[i][j] = VectorCalientesCp[contador];
            contador++;
        }
    }
    QVector < QVector <double > > VectorFriasMATRIZ;
    Pares = VectorFriasCp.size();
    nfils = Pares/3;
    ncols = 3;
    VectorFriasMATRIZ.resize(nfils);
    for(i = 0; i<  VectorFriasMATRIZ.size(); i++)
    {
        VectorFriasMATRIZ[i].resize(ncols);
    }
    contador = 0;
    for(int i = 0; i <  VectorFriasMATRIZ.size(); i++)
    {
        for(int j = 0; j <  VectorFriasMATRIZ.at(i).size(); j++)
        {
            VectorFriasMATRIZ[i][j] = VectorFriasCp[contador];
            contador++;
        }
    }
    VCC = VectorCalientes;
    VFC = VectorFrias;
    std::sort(VectorCalientes.begin(),VectorCalientes.end());
    std::sort(VectorFrias.begin(),VectorFrias.end());
    //qDebug() << VectorCalientes << VectorFrias;
    VCCurvas = VectorCalientes;
    VFCurvas = VectorFrias;
    QVector<double> VectorCalientesNuevo,VectorFriasNuevo;
    VectorCalientesNuevo.resize(VectorCalientes.size());
    k = VectorCalientes.size() - 1 ;
    for( i = 0; i < VectorCalientes.size(); i++){
        VectorCalientesNuevo[k] = VectorCalientes[i];
        --k;
    }
    k = VectorFrias.size() - 1;
    VectorFriasNuevo.resize(VectorFrias.size());
    for( i = 0; i < VectorFrias.size(); i++){
        VectorFriasNuevo[k] = VectorFrias[i];
        --k;
    }
    VectorCalientes = VectorCalientesNuevo;
    VectorFrias = VectorFriasNuevo;
    n = VCCurvas.size();
    for (i = 0; i < n; ++i){
        for(j = 0; j < n; ++j){
            if(i==j){
            }else{
                if (VCCurvas[i] == VCCurvas[j] ){
                    QVector<double> VCCurvaslos;
                    for (i = 0; i < j ; i++){
                        VCCurvaslos << VCCurvas[i];
                    }
                    QVector<double> VCCurvashi;
                    for (j = j + 1 ; j < n ; j++){
                        VCCurvashi << VCCurvas[j];
                    }
                    VCCurvas.clear();
                    VCCurvas = VCCurvaslos + VCCurvashi;
                    VCCurvaslos.clear();
                    VCCurvashi.clear();
                    i=0;
                    n = VCCurvas.size();
                }
            }
        }
    }
    n = VFCurvas.size();
    //ELIMINAR DUPLICADOS DE CORRIENTES FRIAS
    for (i = 0; i < n; ++i){
        for(j = 0; j < n; ++j){
            if(i==j){
            }else{
                if (VFCurvas[i] == VFCurvas[j] ){
                    QVector<double> VFCurvaslos;
                    for (i = 0; i < j ; i++){
                        VFCurvaslos << VFCurvas[i];
                    }
                    QVector<double> VFCurvashi;
                    for (j = j + 1 ; j < n ; j++){
                        VFCurvashi << VFCurvas[j];
                    }
                    VFCurvas.clear();
                    VFCurvas = VFCurvaslos + VFCurvashi;
                    VFCurvaslos.clear();
                    VFCurvashi.clear();
                    i=0;
                    n = VFCurvas.size();
                }
            }
        }
    }
    // SE FORMA LA MATRIZ DE RANGOS CALIENTES
    QVector < QVector < double > > RangosCalientes;
    n = VCCurvas.size();
    nfils = n-1;
    ncols = 3;
    RangosCalientes.resize(nfils);
    for(int i = 0; i< RangosCalientes.size(); i++)
    {
        RangosCalientes[i].resize(ncols);
    }
    for(int i = 0; i < RangosCalientes.size(); i++)
    {
        if(i <= (n-2)){
            RangosCalientes[i][0] = VCCurvas[i] ;
            RangosCalientes[i][1] = VCCurvas[i+1] ;
            RangosCalientes[i][2] = qFabs(VCCurvas[i+1]-VCCurvas[i]);
        }
    }
    // SE FORMA LA MATRIZ DE RANGOS FRIAS
    QVector < QVector < double > > RangosFrias;
    n = VFCurvas.size();
    nfils = n-1,
            ncols = 3;
    RangosFrias.resize(nfils);
    for(int i = 0; i< RangosFrias.size(); i++)
    {
        RangosFrias[i].resize(ncols);
    }
    for(int i = 0; i < RangosFrias.size(); i++)
    {
        if(i <= (n-2)){
            RangosFrias[i][0] = VFCurvas[i] ;
            RangosFrias[i][1] = VFCurvas[i+1] ;
            RangosFrias[i][2] = qFabs(VFCurvas[i+1]-VFCurvas[i]);
        }
    }
    QVector < QVector < double > > sumCpCal;
    n = VCCurvas.size() - 1;;
    nfils = n;
    ncols = 2;
    sumCpCal.resize(nfils);
    for(i = 0; i< sumCpCal.size(); i++)
    {
        sumCpCal[i].resize(ncols);
    }
    int l=0;
    int m =VectorCalientesMATRIZ.size();
    for(i = 0; i < n ; i++)
    {
        int k=0;
        for(j = 0; j < m ; j++){
            if(VCCurvas[i]<= VectorCalientesMATRIZ[j][0] - 1 && VCCurvas[i]>= VectorCalientesMATRIZ[j][1]-1 )
            {
                sumCpCal[l][k] = VectorCalientesMATRIZ[j][2];
            }else{
                sumCpCal[l][k] = 0;
            }
            k++;
        }
        l++;
    }
    // SUMCPFRI
    QVector < QVector < double > > sumCpFri;
    n = VFCurvas.size() - 1;
    nfils = n;
    ncols = 2;
    sumCpFri.resize(nfils);
    for(i = 0; i< sumCpFri.size(); i++)
    {
        sumCpFri[i].resize(ncols);
    }
    int l1=0;
    m = VectorFriasMATRIZ.size();
    for(i = 0; i < n ; i++)
    {
        int k1=0;
        for(j = 0; j < m ; j++){
            if(VFCurvas[i]>= VectorFriasMATRIZ[j][0]-1 && VFCurvas[i]<= VectorFriasMATRIZ[j][1]-1 )
            {
                sumCpFri[l1][k1] = VectorFriasMATRIZ[j][2];
            }else{
                sumCpFri[l1][k1] = 0;
            }
            k1++;
        }
        l1++;
    }
    // sumas de vector para sumCpFri y sumCpCal
    QVector<double> CpcurvaHot;
    n = sumCpCal.size();
    for(i = 0; i < n ; i++){
        CpcurvaHot << sumCpCal[i][0] + sumCpCal[i][1];
    }
    QVector<double> CpcurvaCold;
    n = sumCpFri.size();
    for(i = 0; i < n ; i++){
        CpcurvaCold << sumCpFri[i][0] + sumCpFri[i][1];
    }
    QVector<double> Val1;
    n = CpcurvaCold.size();
    for(i=0; i < n ; i++){
        Val1 << RangosFrias[i][2] * CpcurvaCold[i];
    }
    QVector<double> Val2;
    n = CpcurvaHot.size();
    for(i=0; i < n ; i++){
        Val2 << RangosCalientes[i][2] * CpcurvaHot[i];
    }
    QVector<QVector<double>> PUNTOSCF, PUNTOSCC;
    // PUNTOS CORRIENTES FRIAS
    n = RangosFrias.size();
    nfils = n;
    ncols = 4;
    PUNTOSCF.resize(nfils);
    for(i = 0; i < nfils; i++)
    {
        PUNTOSCF[i].resize(ncols);
    }
    for(i = 0; i < n ; i++)
    {
        PUNTOSCF[i][0] = RangosFrias[i][0];
        PUNTOSCF[i][1] = RangosFrias[i][1];
        PUNTOSCF[i][2] = RangosFrias[i][2];
        PUNTOSCF[i][3] = RangosFrias[i][2]*CpcurvaCold[i];
    }
    // PUNTOS CORRIENTES CALIENNTES
    n = RangosCalientes.size();
    nfils = n;
    ncols = 4;
    PUNTOSCC.resize(nfils);
    for(i = 0; i < nfils; i++){
        PUNTOSCC[i].resize(ncols);
    }
    for(i = 0 ; i < n; i++){
        PUNTOSCC[i][0] = RangosCalientes[i][0];
        PUNTOSCC[i][1] = RangosCalientes[i][1];
        PUNTOSCC[i][2] = RangosCalientes[i][2];
        PUNTOSCC[i][3] = RangosCalientes[i][2]*CpcurvaHot[i];
    }
    QVector<double> PuntosCurvasC,PuntosCurvasF;
    n = PUNTOSCC.size();
    PuntosCurvasC.resize(PUNTOSCC.size()+1);
    PuntosCurvasC[0] = 0;
    for(i = 0 ; i < n; i++){
        PuntosCurvasC[i+1] = PuntosCurvasC[i] + PUNTOSCC[i][3];
    }
    n = PUNTOSCF.size();
    PuntosCurvasF.resize(PUNTOSCF.size()+1);
    PuntosCurvasF[0] = 0;
    for(i = 0; i < n; i++){
        PuntosCurvasF[i+1] = PuntosCurvasF[i] + PUNTOSCF[i][3];
    }
    MCCENTALPIA.resize(PuntosCurvasC.size());
    MCCTEMPERATURAS.resize(VCCurvas.size());
    for ( int i = 0 ; i < PuntosCurvasC.size() ; i++){
        MCCENTALPIA[i] = PuntosCurvasC[i];
        MCCTEMPERATURAS[i] = VCCurvas[i];
    }
    MCFENTALPIA.resize(PuntosCurvasF.size());
    MCFTEMPERATURAS.resize(VFCurvas.size());
    for ( int i = 0 ; i < PuntosCurvasF.size() ; i++){
        MCFENTALPIA[i] = PuntosCurvasF[i];
        MCFTEMPERATURAS[i] = VFCurvas[i];
    }
}

QVector<double> Plot_curvascompuestas::getCCENTALPIA()
{
    return MCCENTALPIA;
}

QVector<double> Plot_curvascompuestas::getCCTEMPERATURAS()
{
    return MCCTEMPERATURAS;
}

QVector<double> Plot_curvascompuestas::getCFENTALPIA()
{
    return MCFENTALPIA;
}

QVector<double> Plot_curvascompuestas::getCFTEMPERATURAS()
{
    return MCFTEMPERATURAS;
}

Plot_curvascompuestasajustadas::Plot_curvascompuestasajustadas(QVector<double> Tsupply, QVector<double> Ttarget, QVector<double> Cp, double DTmin)
{
    QVector<double> VectorCalientes, VectorCalientesCp;
    QVector<double> VectorFrias,VectorFriasCp, VCCurvas,VFCurvas;
    int i,j,n,nfils,ncols,Pares,contador,k;
    n = Tsupply.size();
    for (i = 0; i < n ; ++i)
    {
        if(Tsupply[i] >= Ttarget[i])
        {
            VectorCalientesCp << Tsupply[i] << Ttarget[i] << Cp[i] ;//<< h[i];
            VectorCalientes << Tsupply[i] << Ttarget[i];
        }
        if(Tsupply[i] <= Ttarget[i])
        {
            VectorFriasCp << Tsupply[i] << Ttarget[i] << Cp[i] ;//<< h[i];
            VectorFrias << Tsupply[i] << Ttarget[i];
        }
        j++;
    }
    //qDebug() << VectorCalientes << VectorCalientesCp << VectorFrias << VectorFriasCp;
    QVector < QVector <double> > VectorCalientesMATRIZ;
    Pares = VectorCalientesCp.size();
    nfils = Pares/3;
    ncols = 3;
    VectorCalientesMATRIZ.resize(nfils);
    for(i = 0; i< VectorCalientesMATRIZ.size(); i++)
    {
        VectorCalientesMATRIZ[i].resize(ncols);
    }
    contador = 0;
    for(int i = 0; i < VectorCalientesMATRIZ.size(); i++)
    {
        for(int j = 0; j < VectorCalientesMATRIZ.at(i).size(); j++)
        {
            VectorCalientesMATRIZ[i][j] = VectorCalientesCp[contador];
            contador++;
        }
    }
    QVector < QVector <double > > VectorFriasMATRIZ;
    Pares = VectorFriasCp.size();
    nfils = Pares/3;
    ncols = 3;
    VectorFriasMATRIZ.resize(nfils);
    for(i = 0; i<  VectorFriasMATRIZ.size(); i++)
    {
        VectorFriasMATRIZ[i].resize(ncols);
    }
    contador = 0;
    for(i = 0; i <  VectorFriasMATRIZ.size(); i++)
    {
        for(j = 0; j <  VectorFriasMATRIZ.at(i).size(); j++)
        {
            VectorFriasMATRIZ[i][j] = VectorFriasCp[contador];
            contador++;
        }
    }
    QVector < QVector <double > > VCC,VFC;
    Pares = VectorCalientes.size();
    nfils = Pares/2;
    ncols = 2;
    VCC.resize(nfils);
    for(i = 0; i <  nfils; i++)
    {
        VCC[i].resize(ncols);
    }
    k=0;
    for(i = 0; i < nfils; i++){
        VCC[i][0] = VectorCalientes[k];
        k++;
        VCC[i][1] = VectorCalientes[k];
        k++;
    }
//    VCC = VectorCalientes;
//    VFC = VectorFrias;}
    Pares = VectorFrias.size();
    nfils = Pares/2;
    ncols = 2;
    VFC.resize(nfils);
    for(i = 0; i <  nfils; i++)
    {
        VFC[i].resize(ncols);
    }
    k=0;
    for(i = 0; i < nfils; i++){
        VFC[i][0] = VectorFrias[k];
        k++;
        VFC[i][1] = VectorFrias[k];
        k++;
    }
    std::sort(VectorCalientes.begin(),VectorCalientes.end());
    std::sort(VectorFrias.begin(),VectorFrias.end());
    VCCurvas = VectorCalientes;
    VFCurvas = VectorFrias;
    QVector<double> VectorCalientesNuevo,VectorFriasNuevo;
    VectorCalientesNuevo.resize(VectorCalientes.size());
    k = VectorCalientes.size() - 1 ;
    for( i = 0; i < VectorCalientes.size(); i++){
        VectorCalientesNuevo[k] = VectorCalientes[i];
        --k;
    }
    k = VectorFrias.size() - 1;
    VectorFriasNuevo.resize(VectorFrias.size());
    for( i = 0; i < VectorFrias.size(); i++){
        VectorFriasNuevo[k] = VectorFrias[i];
        --k;
    }
    n = VCCurvas.size();
    for (i = 0; i < n; ++i){
        for(j = 0; j < n; ++j){
            if(i==j){
            }else{
                if (VCCurvas[i] == VCCurvas[j] ){
                    QVector<double> VCCurvaslos;
                    for (i = 0; i < j ; i++){
                        VCCurvaslos << VCCurvas[i];
                    }
                    QVector<double> VCCurvashi;
                    for (j = j + 1 ; j < n ; j++){
                        VCCurvashi << VCCurvas[j];
                    }
                    VCCurvas.clear();
                    VCCurvas = VCCurvaslos + VCCurvashi;
                    VCCurvaslos.clear();
                    VCCurvashi.clear();
                    i=0;
                    n = VCCurvas.size();
                }
            }
        }
    }
    n = VFCurvas.size();
    //ELIMINAR DUPLICADOS DE CORRIENTES FRIAS
    for (i = 0; i < n; ++i){
        for(j = 0; j < n; ++j){
            if(i==j){
            }else{
                if (VFCurvas[i] == VFCurvas[j] ){
                    QVector<double> VFCurvaslos;
                    for (i = 0; i < j ; i++){
                        VFCurvaslos << VFCurvas[i];
                    }
                    QVector<double> VFCurvashi;
                    for (j = j + 1 ; j < n ; j++){
                        VFCurvashi << VFCurvas[j];
                    }
                    VFCurvas.clear();
                    VFCurvas = VFCurvaslos + VFCurvashi;
                    VFCurvaslos.clear();
                    VFCurvashi.clear();
                    i=0;
                    n = VFCurvas.size();
                }
            }
        }
    }
    QVector<double> VCCurvasT = VCCurvas;
    QVector<double> VFCurvasT = VFCurvas;
    // SE FORMA LA MATRIZ DE RANGOS CALIENTES
    QVector < QVector < double > > RangosCalientes;
    n = VCCurvas.size();
    nfils = n-1;
    ncols = 3;
    RangosCalientes.resize(nfils);
    for(int i = 0; i< RangosCalientes.size(); i++)
    {
        RangosCalientes[i].resize(ncols);
    }
    for(int i = 0; i < RangosCalientes.size(); i++)
    {
        if(i <= (n-2)){
            RangosCalientes[i][0] = VCCurvas[i] ;
            RangosCalientes[i][1] = VCCurvas[i+1] ;
            RangosCalientes[i][2] = qFabs(VCCurvas[i+1]-VCCurvas[i]);
        }
    }
    // SE FORMA LA MATRIZ DE RANGOS FRIAS
    QVector < QVector < double > > RangosFrias;
    n = VFCurvas.size();
    nfils = n-1,
    ncols = 3;
    RangosFrias.resize(nfils);
    for(int i = 0; i< RangosFrias.size(); i++)
    {
        RangosFrias[i].resize(ncols);
    }
    for(int i = 0; i < RangosFrias.size(); i++)
    {
        if(i <= (n-2)){
            RangosFrias[i][0] = VFCurvas[i] ;
            RangosFrias[i][1] = VFCurvas[i+1] ;
            RangosFrias[i][2] = qFabs(VFCurvas[i+1]-VFCurvas[i]);
        }
    }
    QVector < QVector < double > > sumCpCal;
    n = VCCurvas.size() - 1;;
    nfils = n;
    ncols = 2;
    sumCpCal.resize(nfils);
    for(i = 0; i< sumCpCal.size(); i++)
    {
        sumCpCal[i].resize(ncols);
    }
    int l=0;
    int m =VectorCalientesMATRIZ.size();
    for(i = 0; i < n ; i++)
    {
        int k=0;
        for(j = 0; j < m ; j++){
            if(VCCurvas[i]<= VectorCalientesMATRIZ[j][0]-1 && VCCurvas[i]>= VectorCalientesMATRIZ[j][1]-1 )
            {
                sumCpCal[l][k] = VectorCalientesMATRIZ[j][2];
            }else{
                sumCpCal[l][k] = 0;
            }
            k++;
        }
        l++;
    }
    // SUMCPFRI
    QVector < QVector < double > > sumCpFri;
    n = VFCurvas.size() - 1;
    nfils = n;
    ncols = 2;
    sumCpFri.resize(nfils);
    for(i = 0; i< sumCpFri.size(); i++)
    {
        sumCpFri[i].resize(ncols);
    }
    int l1=0;
    m = VectorFriasMATRIZ.size();
    for(i = 0; i < n ; i++)
    {
        int k1=0;
        for(j = 0; j < m ; j++){
            if(VFCurvas[i]>= VectorFriasMATRIZ[j][0]-1 && VFCurvas[i]<= VectorFriasMATRIZ[j][1]-1 )
            {
                sumCpFri[l1][k1] = VectorFriasMATRIZ[j][2];
            }else{
                sumCpFri[l1][k1] = 0;
            }
            k1++;
        }
        l1++;
    }
    QVector<double> CpcurvaHot;
    n = sumCpCal.size();
    for(i = 0; i < n ; i++){
        CpcurvaHot << sumCpCal[i][0] + sumCpCal[i][1];
    }
    QVector<double> CpcurvaCold;
    n = sumCpFri.size();
    for(i = 0; i < n ; i++){
        CpcurvaCold << sumCpFri[i][0] + sumCpFri[i][1];
    }
    QVector<double> Val1;
    n = CpcurvaCold.size();
    for(i=0; i < n ; i++){
        Val1 << RangosFrias[i][2] * CpcurvaCold[i];
    }
    QVector<double> Val2;
    n = CpcurvaHot.size();
    for(i=0; i < n ; i++){
        Val2 << RangosCalientes[i][2] * CpcurvaHot[i];
    }
    QVector<QVector<double>> PUNTOSCF, PUNTOSCC;
    // PUNTOS CORRIENTES FRIAS
    n = RangosFrias.size();
    nfils = n;
    ncols = 4;
    PUNTOSCF.resize(nfils);
    for(i = 0; i < nfils; i++)
    {
        PUNTOSCF[i].resize(ncols);
    }
    for(i = 0; i < n ; i++)
    {
        PUNTOSCF[i][0] = RangosFrias[i][0];
        PUNTOSCF[i][1] = RangosFrias[i][1];
        PUNTOSCF[i][2] = RangosFrias[i][2];
        PUNTOSCF[i][3] = RangosFrias[i][2]*CpcurvaCold[i];
    }
    // PUNTOS CORRIENTES CALIENNTES
    n = RangosCalientes.size();
    nfils = n;
    ncols = 4;
    PUNTOSCC.resize(nfils);
    for(i = 0; i < nfils; i++){
        PUNTOSCC[i].resize(ncols);
    }
    for(i = 0 ; i < n; i++){
        PUNTOSCC[i][0] = RangosCalientes[i][0];
        PUNTOSCC[i][1] = RangosCalientes[i][1];
        PUNTOSCC[i][2] = RangosCalientes[i][2];
        PUNTOSCC[i][3] = RangosCalientes[i][2]*CpcurvaHot[i];
    }
    // HASTA AQUI ES PARA CURVAS COMPUESTAS
    QVector<QVector<double>> VectorCalientesTmin;
    VectorCalientesTmin.resize(VCCurvasT.size());
    nfils = VCCurvasT.size();
    ncols = 2;
    for(i = 0; i < nfils; i++){
        VectorCalientesTmin[i].resize(ncols);
    }
    k = VCCurvasT.size()-1;
    for(i = 0; i < nfils; i++){
        VectorCalientesTmin[i][0] = VCCurvasT[k]-DTmin;
        VectorCalientesTmin[i][1] = VCCurvasT[k];
        --k;
    }
    QVector<QVector<double>> VectorFriasTmin;
    VectorFriasTmin.resize(VFCurvasT.size());
    nfils = VFCurvasT.size();
    ncols = 2;
    for(i = 0; i < nfils; i++){
        VectorFriasTmin[i].resize(ncols);
    }
    k = VFCurvasT.size()-1;
    for(i = 0; i < nfils; i++){
        VectorFriasTmin[i][0] = VFCurvasT[k];
        VectorFriasTmin[i][1] = VFCurvasT[k]+DTmin;
        --k;
    }
    QVector<QVector<double>> VectorCorrientesTotal;
    nfils = VCCurvasT.size() + VFCurvasT.size();
    ncols = 2;
    VectorCorrientesTotal.resize(nfils);
    for(i = 0; i < nfils ; i++){
        VectorCorrientesTotal[i].resize(ncols);
    }
    j=0;
    k=0;
    for(i = 0; i < nfils ; i++){
        if(i < VectorCalientesTmin.size()){
            VectorCorrientesTotal[i][0] = VectorCalientesTmin[j][0];
            VectorCorrientesTotal[i][1] = VectorCalientesTmin[j][1];
            ++j;
        }else{
            VectorCorrientesTotal[i][0] = VectorFriasTmin[k][0];
            VectorCorrientesTotal[i][1] = VectorFriasTmin[k][1];
            ++k;
        }
    }
    std::sort(VectorCorrientesTotal.begin(),VectorCorrientesTotal.end());
    QVector<QVector<double>> VectorCorrientesTotalOrdenar;
    nfils = VectorCorrientesTotal.size();
    ncols = 2;
    VectorCorrientesTotalOrdenar.resize(nfils);
    for(i = 0; i < nfils ; i++){
        VectorCorrientesTotalOrdenar[i].resize(ncols);
    }
    k = VectorCorrientesTotal.size()-1;
    for(i = 0; i < nfils ; i++){
        VectorCorrientesTotalOrdenar[i][0] = VectorCorrientesTotal[k][0];
        VectorCorrientesTotalOrdenar[i][1] = VectorCorrientesTotal[k][1];
        --k;
    }
    VectorCorrientesTotal = VectorCorrientesTotalOrdenar;
    int r3 = VectorCorrientesTotal.size();
    int r4 = VCC.size();
    //FORMAR LA MATRIZ PARA SUMCPCAL
    QVector<QVector<double>> sumCpCalTab;
    nfils = VectorCorrientesTotal.size()-1;
    ncols = 2;
    sumCpCalTab.resize(nfils);
    for( i = 0; i < nfils; i++){
        sumCpCalTab[i].resize(ncols);
    }
    l = 0;
    for( i = 1; i < r3; ++i){
        k = 0;
        for(j = 0; j < r4; ++j){
            if(VectorCorrientesTotal[i][1] <= VCC[j][0]-1 && VectorCorrientesTotal[i][1] >= VCC[j][1] ){
                sumCpCalTab[l][k] = VectorCalientesMATRIZ[j][2];
            }else{
                sumCpCalTab[l][k] = 0.0 ;
            }
            ++k;
        }
        ++l;
    }
    QVector<QVector<double>> sumCpFriTab;
    nfils = VectorCorrientesTotal.size()-1;
    ncols = 2;
    sumCpFriTab.resize(nfils);
    for( i = 0; i < nfils; i++){
        sumCpFriTab[i].resize(ncols);
    }
    l = 0;
    int r5 = VFC.size();
    for( i = 1; i < r3; ++i){
        k = 0;
        for(j = 0; j < r5; ++j){
            if(VectorCorrientesTotal[i][1] <= VFC[j][1]-1 && VectorCorrientesTotal[i][1] >= VFC[j][0] ){
                sumCpFriTab[l][k] = VectorFriasMATRIZ[j][2];
            }else{
                sumCpFriTab[l][k] = 0.0 ;
            }
            ++k;
        }
        ++l;
    }
    QVector<double> SumatoriaCP;
    nfils = VectorCorrientesTotal.size()-1;
    SumatoriaCP.resize(nfils);
    for(i = 0; i < nfils; ++i){
        SumatoriaCP[i] = sumCpFriTab[i][0] + sumCpFriTab[i][1] - sumCpCalTab[i][0] - sumCpCalTab[i][1];
    }
    QVector<double> DifTemperaturas;
    nfils = VectorCorrientesTotal.size()-1;
    DifTemperaturas.resize(nfils);
    j = 1;
    for(i = 0; i < VectorCorrientesTotal.size() ; ++i){
        if (j < VectorCorrientesTotal.size()){
            DifTemperaturas[i] = VectorCorrientesTotal[i][1] - VectorCorrientesTotal[j][1];
            ++j;
        }else if(j == VectorCorrientesTotal.size()){
            break;
        }
    }
    QVector<double> Deficit;
    nfils = DifTemperaturas.size();
    Deficit.resize(DifTemperaturas.size());
    for( i = 0 ; i < nfils; ++i){
        Deficit[i] = DifTemperaturas[i] * SumatoriaCP[i];
    }
    int Ldef = Deficit.size();
    QVector<QVector<double>> VecHeatFlow;
    QVector<double> VAL1,VAL2;
    nfils = DifTemperaturas.size();
    ncols = 2;
    VecHeatFlow.resize(nfils);
    VAL1.resize(nfils+1);
    VAL2.resize(nfils);
    for(i = 0; i < nfils ; i++){
        VecHeatFlow[i].resize(ncols);
    }
    VAL1[0]=0;
    for(i = 0; i < Ldef ; i++){
        VAL2[i] = VAL1[i] - Deficit[i];
        VAL1[i+1] = VAL2[i];
        VecHeatFlow[i][0] = VAL1[i]; // Val1
        VecHeatFlow[i][1] = VAL2[i]; // Val2
    }
    double min = *std::min_element(VAL2.begin(),VAL2.end());
    VAL1.clear();
    VAL2.clear();
    VAL1.resize(nfils+1);
    VAL2.resize(nfils);
    QVector<QVector<double>> VecAdjHeatFlow;
    nfils = DifTemperaturas.size();
    ncols = 2;
    VecAdjHeatFlow.resize(nfils);
    for(i = 0; i < nfils ; i++){
        VecAdjHeatFlow[i].resize(ncols);
    }
    VAL1[0]= qFabs(min);
    for(i = 0; i < Ldef ; i++){
        VAL2[i] = VAL1[i] - Deficit[i];
        VAL1[i+1] = VAL2[i];
        VecAdjHeatFlow[i][0] = VAL1[i]; // Val1
        VecAdjHeatFlow[i][1] = VAL2[i]; // Val2
    }
    // PUNTOS DE LA CURVAS COMPUESTAS
    QVector<double> PuntosCurvasC,PuntosCurvasF;
    n = PUNTOSCC.size();
    PuntosCurvasC.resize(PUNTOSCC.size()+1);
    PuntosCurvasC[0] = 0;
    for(i = 0 ; i < n; i++){
        PuntosCurvasC[i+1] = PuntosCurvasC[i] + PUNTOSCC[i][3];
    }
    n = PUNTOSCF.size();
    PuntosCurvasF.resize(PUNTOSCF.size()+1);
    double max = *std::max_element(VAL2.begin(),VAL2.end());
    PuntosCurvasF[0] = max ;
    for(i = 0; i < n; i++){
        PuntosCurvasF[i+1] = PuntosCurvasF[i] + PUNTOSCF[i][3];
    }
    MCCENTALPIA.resize(PuntosCurvasC.size());
    MCCTEMPERATURAS.resize(VCCurvas.size());
    for ( int i = 0 ; i < PuntosCurvasC.size() ; i++){
        MCCENTALPIA[i] = PuntosCurvasC[i];
        MCCTEMPERATURAS[i] = VCCurvas[i];
    }
    MCFENTALPIAAJUSTADA.resize(PuntosCurvasF.size());
    MCFTEMPERATURASAJUSTADA.resize(VFCurvas.size());
    for ( int i = 0 ; i < PuntosCurvasF.size() ; i++){
        MCFENTALPIAAJUSTADA[i] = PuntosCurvasF[i];
        MCFTEMPERATURASAJUSTADA[i] = VFCurvas[i];
    }
}

QVector<double> Plot_curvascompuestasajustadas::getCCENTALPIA()
{
    return MCCENTALPIA;
}

QVector<double> Plot_curvascompuestasajustadas::getCCTEMPERATURAS()
{
    return MCCTEMPERATURAS;
}

QVector<double> Plot_curvascompuestasajustadas::getCFENTALPIAAJUSTADAS()
{
    return MCFENTALPIAAJUSTADA;
}

QVector<double> Plot_curvascompuestasajustadas::getCFTEMPERATURASAJUSTADAS()
{
    return MCFTEMPERATURASAJUSTADA;
}
