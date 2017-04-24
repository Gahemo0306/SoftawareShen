#include "contenido_plots_costos.h"
#include "ui_contenido_plots_costos.h"

contenido_plots_costos::contenido_plots_costos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::contenido_plots_costos)
{
    ui->setupUi(this);
}

contenido_plots_costos::~contenido_plots_costos()
{
    delete ui;
}
