#include "ventanaprincipal.h"
#include "unidadesentrada.h"
#include "contenido_plots.h"
#include "tabladatos.h"
#include <QDesktopWidget>
#include <QMainWindow>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    //QDesktopWidget dw;
    VentanaPrincipal first;

//    int x=dw.width()*0.8;
//    int y=dw.height()*0.8;
//    first.setFixedSize(x,y);
    //TablaDatos second;

    //QObject::connect(&second,SIGNAL(on_plot_push_clicked(bool)),&first,SLOT(on_actionPlotter()));
    //QObject::connect(&first,SIGNAL(on_SIS_toggled(bool)),&fourth,SLOT(OnnewSignalSIS(bool)));
    //QObject::connect(&fourth, SIGNAL(subwindow(int)),&second, SLOT(subwindowVALUE(int)));
    //QObject::connect(&fourth, SIGNAL(newSignalSIS(bool)),&second, SLOT(OnnewSignalSIS(bool)));


    first.show();

    return a.exec();
}
