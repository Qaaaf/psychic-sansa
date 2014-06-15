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

	void New(const QString& name);
	void Load(const QString& name);
    void Save();
	void SaveAs(const QString& name);

    QJsonObject m_data;
    QString m_name;


};

#endif // CONFIGFILE_H
