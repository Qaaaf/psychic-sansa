#include "configfile.h"

#include <QJsonDocument>



ConfigFile::ConfigFile()
{
    m_doc = 0;
    m_name = "emptyname";
}

ConfigFile::~ConfigFile()
{
}

void ConfigFile::New(QString& name)
{
}
void ConfigFile::Open(QString& name)
{
}
void ConfigFile::Close()
{
}
void ConfigFile::Save()
{
}
void ConfigFile::SaveAs(QString& name)
{
}

QJsonArray& ConfigFile::GetArray(QString& name)
{
}
