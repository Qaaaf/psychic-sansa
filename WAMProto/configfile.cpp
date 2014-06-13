#include "configfile.h"

#include <QJsonDocument>
#include <QJsonArray>

#include <qfile.h>



ConfigFile::ConfigFile()
{
    m_name = "emptyname";
}

ConfigFile::~ConfigFile()
{
    m_name = "";
}

void ConfigFile::New(QString& name)
{
    m_name =  name;
}
void ConfigFile::Load(QString& name)
{
    QFile f(name + ".wamf");
    f.open(QIODevice::ReadOnly);

    QByteArray data = f.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(data));

    m_data = doc.object();


}

void ConfigFile::Save()
{
    SaveAs(m_name);
}
void ConfigFile::SaveAs(QString& name)
{
    QFile f(name + ".wamf");
    f.open(QIODevice::WriteOnly);

    QJsonDocument doc(m_data);

    f.write(doc.toJson());

    f.close();
}

QJsonArray& ConfigFile::GetArray(QString& name)
{
    return m_data[name].toArray();
}
