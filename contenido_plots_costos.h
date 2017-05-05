#ifndef CONTENIDO_PLOTS_COSTOS_H
#define CONTENIDO_PLOTS_COSTOS_H

#include <QWidget>

namespace Ui {
class contenido_plots_costos;
}

class contenido_plots_costos : public QWidget
{
    Q_OBJECT

public:
    explicit contenido_plots_costos(QWidget *parent = 0);
    ~contenido_plots_costos();

private:
    Ui::contenido_plots_costos *ui;
};

#endif // CONTENIDO_PLOTS_COSTOS_H
