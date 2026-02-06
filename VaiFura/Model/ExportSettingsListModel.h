#ifndef EXPORTSETTINGSLISTMODEL_H
#define EXPORTSETTINGSLISTMODEL_H

#include <QQmlEngine>
#include <QAbstractListModel>
#include <QObject>
#include "ExportSettings.h"

class ExportSettingsListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int size READ size NOTIFY sizeChanged FINAL)

public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        LabelRole,
        DescriptionRole,
        UnitRole,
        ValueRole,
        TypeRole
    };

    enum ValueRoles {
        Number = ExportSettings::Number,
        Text = ExportSettings::Text,
        Boolean = ExportSettings::Boolean
    };
    Q_ENUM(ValueRoles)

    explicit ExportSettingsListModel(QObject *parent = nullptr);

    int size() const { return settings_.size(); }

    void load(const QString &fileName);
    void save(const QString &fileName);

protected:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void sizeChanged();

private:
    QVector<ExportSettings> settings_;
};

#endif // EXPORTSETTINGSLISTMODEL_H
