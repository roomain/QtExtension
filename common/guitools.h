#pragma once
#include <functional>
#include <QByteArray>

namespace Qt::GUITools
{
    /*@brief restore geometry callback*/
    using RestoreGeometry = std::function<QByteArray()>;
    
    /*@brief save geometry callback*/
    using SaveGeometry = std::function<void(const QByteArray &)>;
}