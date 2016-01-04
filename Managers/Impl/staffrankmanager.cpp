#include "staffrankmanager.h"
#include "Model/Impl/staffrank.h"
#include "Network/netutils.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

StaffRankManager::StaffRankManager()
{
    
}

DataStructure* StaffRankManager::add()
{
    StaffRank *rank = new StaffRank();
    rank->setName("Admin");
    rank->setPermissions(INT32_MAX);
    return rank;
}

DataStructure* StaffRankManager::edit()
{
    StaffRank *rank = new StaffRank();
    rank->setName("Admin");
    rank->setPermissions(INT32_MAX);
    return rank;
}

DataStructure* StaffRankManager::deleteFunction()
{
    StaffRank *rank = new StaffRank();
    rank->setName("Admin");
    rank->setPermissions(INT32_MAX);
    return rank;
}

void StaffRankManager::refresh()
{
    NetUtils net;
    QString html = net.get("http://localhost:8080/staffrank/all");
    QJsonDocument loadDoc(QJsonDocument::fromJson(html.toUtf8()));
    QJsonArray array = loadDoc.array();
    StaffRank *staffRank = new StaffRank();
    staffRank->read(array[0].toObject());
    qDebug() << staffRank->getName();
}

void StaffRankManager::onAdd(DataStructure *structure)
{
    
}

void StaffRankManager::onEdit(DataStructure *structure)
{
    
}

void StaffRankManager::onDelete(DataStructure *structure)
{
    
}
