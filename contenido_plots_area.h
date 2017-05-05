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

    void on_SBk_valueChanged(double arg1);

    void on_SBmin_valueChanged(double arg1);

    void on_SBmax_valueChanged(double arg1);

    void on_SBinc_valueChanged(double arg1);

    void on_Services_cellChanged(int row, int column);

private:
    Ui::contenido_plots_area *ui;
};

#endif // CONTENIDO_PLOTS_AREA_H
