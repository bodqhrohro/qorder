#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QObject>
#include <QtWidgets/QMainWindow>

#include "ui_mainwindow.h"
#include "actions_model.h"

enum dirType {
    SOURCE_DIR,
    TARGET_DIR,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);

    private:
        Ui::MainWindow ui;
        ActionsModel *actionsModel;

        void directoryDialog(dirType);
        void newMoveAction();
};

#endif // MAINWINDOW_H
