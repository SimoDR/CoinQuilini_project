#ifndef SELEZIONEDIALOG_H
#define SELEZIONEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class SelezioneDialog : public QDialog
{
    Q_OBJECT
private:
    QComboBox *_combo;
    QCheckBox * _regular;
    QVBoxLayout * _layout;
    QLabel * _explanation;
    QHBoxLayout * _conferma;
    QPushButton * _ok;
    QPushButton * _no;
public:
    SelezioneDialog(QWidget * parent =nullptr);

signals:
    void datiSelezionati(const QString &, bool);
private slots:
    void inoltraDati();
};

#endif // SELEZIONEDIALOG_H
