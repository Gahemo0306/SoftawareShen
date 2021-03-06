#ifndef CONTENIDO_PLOTS_H
#define CONTENIDO_PLOTS_H
#include <QFileSystemModel>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFile>
#include <QDataStream>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QWidget>
#include "qalgorithms.h"
#include "duvaloraction.h"
#include "valoraction.h"

namespace Ui {
class Contenido_PLOTS;
}

class Contenido_PLOTS : public QWidget
{
    Q_OBJECT

public:
    explicit Contenido_PLOTS(QWidget *parent = 0);
    ~Contenido_PLOTS();

private slots:

    void on_Uniforme_clicked();
    void on_Diverso_clicked();
    void on_StaticradioButton_clicked();
    void on_IncrementradioButton_clicked();
    void RADIOBUTTONS();
    void on_plot_push_clicked();
    void plot(int ventanaplot, bool uniforme, bool diverso, bool estatico, bool incremento,
              QVector<double> TS, QVector<double> TE, QVector<double> Wcp);

private:
    Ui::Contenido_PLOTS *ui;
};

#endif // CONTENIDO_PLOTS_H
