#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QString>
#include <QJsonObject>

class QJsonArray;

class ConfigFile
{
    ConfigFile();
public:
    static ConfigFile& I()
    {
        static ConfigFile f;
        return f;
    }

    ~ConfigFile();

    void New(QString& name);
    void Load(QString& name);
    void Save();
    void SaveAs(QString& name);

    QJsonArray& GetArray(QString& name);

    QJsonObject m_data;
    QString m_name;


};

#endif // CONFIGFILE_H
