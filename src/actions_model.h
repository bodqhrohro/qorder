#ifndef ACTIONS_MODEL_H
#define ACTIONS_MODEL_H

#include <QAbstractItemModel>
#include <QStyle>

class Action
{
public:
    QString source;
    QString dest;

    Action(QString s, QString d) : source{s}, dest{d} {}
};

class ActionsModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_DISABLE_COPY(ActionsModel)

public:
    explicit ActionsModel(QObject *parent = nullptr);
    ~ActionsModel() override;

    void addAction(const QString, const QString);

private:
    QVector<Action> actions;

protected:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;

Q_SIGNALS:
    void dataChanged();
};

#endif // ACTIONS_MODEL_H
