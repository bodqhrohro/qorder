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

        void handle_exception(const QString& title, std::exception_ptr eptr);
        void error(const QString& title, const QString& text);
        void directoryDialog(dirType);
        void newMoveAction();
        void loadDirsFromPreset();
        void saveDirsToPreset();
};

#endif // MAINWINDOW_H
