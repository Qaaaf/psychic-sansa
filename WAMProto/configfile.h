#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QString>

class QJsonDocument;
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
    void Open(QString& name);
    void Close();
    void Save();
    void SaveAs(QString& name);

    QJsonArray& GetArray(QString& name);

    QJsonDocument* m_doc;
    QString m_name;


};

#endif // CONFIGFILE_H
