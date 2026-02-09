#ifndef SETTINGSLISTMODEL_H
#define SETTINGSLISTMODEL_H

#include <QQmlEngine>
#include <QAbstractListModel>
#include <QObject>
#include "Settings.h"

class SettingsListModel : public QAbstractListModel
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
        Number = Settings::Number,
        Text = Settings::Text,
        Boolean = Settings::Boolean
    };
    Q_ENUM(ValueRoles)

    explicit SettingsListModel(QObject *parent = nullptr);

    int size() const { return settings_.size(); }

    void setSettings(const QVector<Settings> &newSettings);
    const QVector<Settings> &settings() const { return settings_; }

protected:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void sizeChanged();

private:
    QVector<Settings> settings_;
};

#endif // SETTINGSLISTMODEL_H
