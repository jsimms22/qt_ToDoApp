#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStandardPaths>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

    void on_btnRemoveAll_clicked();

    void on_btnSave_clicked();

private:
    Ui::MainWindow *ui;
    // defaults to saving a file in the documents folder of the client's system
    QString m_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\\todofile.txt";
};
#endif // MAINWINDOW_H
