#include "mainwindow.h"
#include "presetfile.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);

    actionsModel = new ActionsModel(this);
    ui.actionsTable->setModel(actionsModel);

    ui.actionNewMoveAction->setShortcut(Qt::CTRL | Qt::Key_M);

    connect(ui.actionLoadDirsFromPreset, &QAction::triggered, this, &MainWindow::loadDirsFromPreset);
    connect(ui.actionSaveDirsToPreset, &QAction::triggered, this, &MainWindow::saveDirsToPreset);
    connect(ui.actionNewMoveAction, &QAction::triggered, this, &MainWindow::newMoveAction);
    connect(ui.actionAbout, &QAction::triggered, this, [this]{ QMessageBox::about(this, tr("About"), tr("QOrder: filesystem transactions executor\n\n© Bohdan Horbeshko, 2024")); });
    connect(ui.actionAboutQt, &QAction::triggered, this, [this]{ QMessageBox::aboutQt(this); });

    connect(ui.sourceDirButton, &QPushButton::clicked, this, [=]{ MainWindow::directoryDialog(SOURCE_DIR); });
    connect(ui.targetDirButton, &QPushButton::clicked, this, [=]{ MainWindow::directoryDialog(TARGET_DIR); });
}

void MainWindow::handle_exception(const QString& title, std::exception_ptr eptr)
{
    try
    {
        if (eptr) {
            std::rethrow_exception(eptr);
        }
    }
    catch (const std::exception& e)
    {
        this->error(title, e.what());
    }
}

void MainWindow::error(const QString& title, const QString& text)
{
    QMessageBox::critical(this, title, text);
    ui.statusBar->showMessage(text);
}

void MainWindow::directoryDialog(dirType type)
{
    QLineEdit* dirEdit;
    QString title;
    switch (type) {
        case SOURCE_DIR:
            dirEdit = ui.sourceDir;
            title = tr("Choose the source directory");
        break;
        case TARGET_DIR:
            dirEdit = ui.targetDir;
            title = tr("Choose the target directory");
        break;
    }

    QString newPath = QFileDialog::getExistingDirectory(this,
                                                        title,
                                                        dirEdit->text(),
                                                        QFileDialog::ShowDirsOnly);
    if (newPath != "") {
        dirEdit->setText(newPath);
    }
}

void MainWindow::newMoveAction()
{
    actionsModel->addAction(QString(""), QString(""));
    ui.actionsTable->repaint();
}

void MainWindow::loadDirsFromPreset()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open preset file"));
    if (path == "") {
        return;
    }

    try
    {
        Preset preset = Preset::readFromFile(path.toStdString());
        ui.sourceDir->setText(QString::fromStdString(preset.sourceDirectory));
        ui.targetDir->setText(QString::fromStdString(preset.targetDirectory));

        ui.statusBar->showMessage(tr("Successfully loaded"));
    }
    catch (...)
    {
        std::exception_ptr ex = std::current_exception();
        this->handle_exception(tr("Preset load error"), ex);
    }
}

void MainWindow::saveDirsToPreset()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save preset file"));
    if (path == "") {
        return;
    }

    try
    {
        Preset preset = Preset(
            ui.sourceDir->text().toStdString(),
            ui.targetDir->text().toStdString(),
            std::vector<Category>());
        Preset::writeToFile(path.toStdString(), preset);

        ui.statusBar->showMessage(tr("Successfully saved"));
    }
    catch (...)
    {
        std::exception_ptr ex = std::current_exception();
        this->handle_exception(tr("Preset save error"), ex);
    }
}
