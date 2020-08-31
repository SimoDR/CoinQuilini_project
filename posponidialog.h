#ifndef POSPONIDIALOG_H
#define POSPONIDIALOG_H

#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QDialog>
#include <QPushButton>

class PosponiDialog : public QDialog
{
    Q_OBJECT
private:
    QLabel * _label;
    QSpinBox * _spin;
    QGridLayout * _layout;
    QPushButton * _ok;
    QPushButton * _no;
public:
    PosponiDialog(QWidget * parent=nullptr);
private slots:
    void  raccogliNumero();
signals:
    void numero(unsigned int);
};

#endif // POSPONIDIALOG_H
