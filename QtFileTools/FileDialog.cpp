#include "FileDialog.h"
#include <QStandardPaths>
#include <QStorageInfo>
#include <QGridLayout>
#include "FileDialogExtension.h"


using namespace Qt::FileTools;



FileDiagArgs::FileDiagArgs(bool bOpenFile) : m_pExtension{ nullptr }, m_bOpenFile{ bOpenFile }
{
    //
}

FileDiagArgs& FileDiagArgs::setCaption(const QString& caption)noexcept
{
    m_sCaption = caption;
    return *this;
}

FileDiagArgs& FileDiagArgs::setDirectory(const QString& directory)noexcept
{
    m_sDirectory = directory;
    return *this;
}

FileDiagArgs& FileDiagArgs::setFilter(const QString& filter)noexcept
{
    m_sFilter = filter;
    return *this;
}


QString FileDiagArgs::caption()const noexcept
{
    return m_sCaption;
}

QString FileDiagArgs::directory()const noexcept
{
    return m_sDirectory;
}

QString FileDiagArgs::filter()const noexcept
{
    return m_sFilter;
}


FileDiagArgs& FileDiagArgs::setExtensionWidget(FileDialogExtension* pExt)noexcept
{
    m_pExtension = pExt;
    return *this;
}

FileDialogExtension* FileDiagArgs::extensionWidget()const noexcept
{
    return m_pExtension;
}

bool FileDiagArgs::isOpenFile()const noexcept
{
    return m_bOpenFile;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void FileDialog::init()
{
    setOption(QFileDialog::DontUseNativeDialog);
    setLabelText(LookIn, tr("Look in"));
    setLabelText(FileName, tr("File name:"));
    setLabelText(FileType, tr("File type:"));
    setLabelText(Accept, acceptMode() ? tr("Save") : tr("Open"));
    setLabelText(Reject, tr("Cancel"));

    // setup url
    QList<QStorageInfo> qlStorage = QStorageInfo::mountedVolumes();

    for (QStorageInfo store : qlStorage)
        m_DefaultURL << QUrl::fromUserInput(store.rootPath());

    m_DefaultURL << QUrl::fromUserInput(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    m_DefaultURL << QUrl::fromUserInput(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    m_DefaultURL << QUrl::fromUserInput(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
}

FileDialog::FileDialog(const FileDiagArgs& args, GetDirectories getDirCallback, SetDirectories setDirCallBack,
    GUITools::RestoreGeometry getGeom, GUITools::SaveGeometry setGeom, QWidget* parent) : QFileDialog(parent, args.caption(), args.directory(), args.filter()),
    m_directoryGet{ getDirCallback },
    m_directorySet{ setDirCallBack },
    m_geometryGet{ getGeom },
    m_GeometrySet{ setGeom }
{
    setAcceptMode(args.isOpenFile() ? AcceptOpen : AcceptSave);
    init();
    
    QList<QUrl> urls = m_DefaultURL;
    if (m_directoryGet)
        urls << m_directoryGet();
    setSidebarUrls(urls);

    if (args.extensionWidget())
    {
        QLayout* layout = this->layout();
        QGridLayout* gridbox = qobject_cast<QGridLayout*>(layout);
        gridbox->addWidget(args.extensionWidget(), 1, gridbox->columnCount(), gridbox->rowCount() - 1, 1);
        QObject::connect(this, &QFileDialog::currentChanged, args.extensionWidget(), &FileDialogExtension::readFileInfo);
    }

    if (m_geometryGet)
        restoreGeometry(m_geometryGet());
}

FileDialog::FileDialog(const FileDiagArgs& args, GUITools::RestoreGeometry getGeom, GUITools::SaveGeometry setGeom, QWidget* parent) : QFileDialog(parent, args.caption(), args.directory(), args.filter()),
    m_geometryGet{ getGeom },
    m_GeometrySet{ setGeom }
{
    setAcceptMode(args.isOpenFile() ? AcceptOpen : AcceptSave);
    init();

    QList<QUrl> urls = m_DefaultURL;
    if (m_directoryGet)
        urls << m_directoryGet();
    setSidebarUrls(urls);

    // restore geometry
    if (m_geometryGet)
        restoreGeometry(m_geometryGet());
}

FileDialog::FileDialog(const FileDiagArgs& args, GetDirectories getDirCallback, SetDirectories setDirCallBack, QWidget* parent) : QFileDialog(parent, args.caption(), args.directory(), args.filter()),
    m_directoryGet{ getDirCallback },
    m_directorySet{ setDirCallBack }
{
    setAcceptMode(args.isOpenFile() ? AcceptOpen : AcceptSave);
    init();

    QList<QUrl> urls = m_DefaultURL;
    if (m_directoryGet)
        urls << m_directoryGet();
    setSidebarUrls(urls);

    // restore geometry
    if (m_geometryGet)
        restoreGeometry(m_geometryGet());
}

void FileDialog::closeEvent(QCloseEvent* event)
{
    if (m_directorySet)
        m_directorySet(sidebarUrls());

    if (m_GeometrySet)
        m_GeometrySet(saveGeometry());    
}
