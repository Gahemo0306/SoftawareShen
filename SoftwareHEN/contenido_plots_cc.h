#ifndef CONTENIDO_PLOTS_CC_H
#define CONTENIDO_PLOTS_CC_H

#include <QWidget>

namespace Ui {
class contenido_plots_cc;
}

class contenido_plots_cc : public QWidget
{
    Q_OBJECT

public:
    explicit contenido_plots_cc(QWidget *parent = 0);
    ~contenido_plots_cc();

private slots:
    void on_radioButton_clicked();
    void RADIOBUTTONS();
    void on_radioButton_2_clicked();

private:
    Ui::contenido_plots_cc *ui;
};

#endif // CONTENIDO_PLOTS_CC_H
