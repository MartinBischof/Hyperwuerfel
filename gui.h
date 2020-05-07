#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QMainWindow
{
    Q_OBJECT
public:
    GUI(QWidget *parent = nullptr);
    ~GUI();
private:
    Ui::GUI *ui;
    QString datei;
private slots:
    void AddToWarteschlange();
    void RemoveFromWarteschlange();
    void on_actionOffnen();
    void rotate();
};
#endif // GUI_H
