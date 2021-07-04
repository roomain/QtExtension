#pragma once
#include "qtfiletools_global.h"
#include <functional>
#include <QFileDialog>
#include <QList>
#include <QUrl>
#include "guitools.h"

namespace Qt::FileTools
{
    /*@brief file dialog extension widget*/
    class FileDialogExtension;

    /*@brief get directories list callback*/
    using GetDirectories = std::function<QList<QUrl>()>;

    /*@brief save directories callback*/
    using SetDirectories = std::function<void(const QList<QUrl>&)>;

    /*@brief file dialog arguments*/
    class QT_EXTENSION_EXPORT FileDiagArgs
    {
    private:
        QString m_sCaption;                 /*@brief file dialog caption*/
        QString m_sDirectory;               /*@brief current directory*/
        QString m_sFilter;                  /*@brief filter extension*/
        FileDialogExtension* m_pExtension;  /*@brief widget extension*/
        bool m_bOpenFile;                   /*@brief is open file dialog*/

    public:
        FileDiagArgs(bool bOpenFile);
        FileDiagArgs& setCaption(const QString& caption)noexcept;
        FileDiagArgs& setDirectory(const QString& directory)noexcept;
        FileDiagArgs& setFilter(const QString& filter)noexcept;
        FileDiagArgs& FileDiagArgs::setExtensionWidget(FileDialogExtension* pExt)noexcept;
        QString caption()const noexcept;
        QString directory()const noexcept;
        QString filter()const noexcept;
        FileDialogExtension* FileDiagArgs::extensionWidget()const noexcept;
        bool isOpenFile()const noexcept;
    };


    /*@brief file dialog*/
    class QT_EXTENSION_EXPORT FileDialog : public QFileDialog
    {
        Q_OBJECT

    private:
        GetDirectories m_directoryGet;          /*@brief get directory callback*/
        SetDirectories m_directorySet;          /*@brief set directory callback*/
        GUITools::RestoreGeometry m_geometryGet;/*@brief get geometry callback*/
        GUITools::SaveGeometry m_GeometrySet;   /*@brief set geometry callback*/
        QList<QUrl> m_DefaultURL;               /*@brief default urls*/

        void init();

    public:
        FileDialog(const FileDiagArgs& args, GetDirectories getDirCallback, SetDirectories setDirCallBack,
            GUITools::RestoreGeometry getGeom, GUITools::SaveGeometry setGeom,  QWidget* parent = nullptr);
        FileDialog(const FileDiagArgs& args, GUITools::RestoreGeometry getGeom, GUITools::SaveGeometry setGeom, QWidget* parent = nullptr);
        FileDialog(const FileDiagArgs& args, GetDirectories getDirCallback, SetDirectories setDirCallBack, QWidget* parent = nullptr);

    protected:
        void closeEvent(QCloseEvent* event)override;
    };
}