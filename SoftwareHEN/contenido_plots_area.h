#ifndef CONTENIDO_PLOTS_AREA_H
#define CONTENIDO_PLOTS_AREA_H

#include <QWidget>

namespace Ui {
class contenido_plots_area;
}

class contenido_plots_area : public QWidget
{
    Q_OBJECT

public:
    explicit contenido_plots_area(QWidget *parent = 0);
    ~contenido_plots_area();

private slots:
    void on_Uniform_clicked();
    void on_Diverse_clicked();
    void on_Static_clicked();
    void on_Increment_clicked();
    void on_Plot_clicked();
    void RADIOBUTTONS();
    void Plot(int ventanaplot, bool uniforme, bool diverso, bool estatico, bool incremento,
              QVector<double> TS, QVector<double> TE, QVector<double> Wcp , QVector<double> h,
              QVector<double> Enfriamento, QVector<double> Calentamiento, int CTo, int CCo);

private:
    Ui::contenido_plots_area *ui;
};

#endif // CONTENIDO_PLOTS_AREA_H
