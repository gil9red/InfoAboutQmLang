#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow: public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow( QWidget * parent = 0 );
    ~MainWindow();
    
private slots:
    void on_tButtonSelectIcon_clicked();
    void on_tButtonOpen_clicked();
    void on_tButtonSaveAs_clicked();
    void on_tButtonQuit_clicked();
    void on_listWidgetFiles_itemSelectionChanged();
    void on_tButtonAdd_clicked();
    void on_tButtonRemove_clicked();
    void on_tButtonRemoveAll_clicked();

    void updateStates();

private:
    Ui::MainWindow * ui;
};

#endif // MAINWINDOW_H
