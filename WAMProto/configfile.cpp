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

void ConfigFile::New(const QString& name)
{
    m_name =  name;
}
void ConfigFile::Load(const QString& name)
{
	m_name = name;
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
void ConfigFile::SaveAs(const QString& name)
{
    QFile f(name + ".wamf");
    f.open(QIODevice::WriteOnly);

    QJsonDocument doc(m_data);

    f.write(doc.toJson());

    f.close();
}
