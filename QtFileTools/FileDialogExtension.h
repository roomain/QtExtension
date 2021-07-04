#pragma once
#include "qtfiletools_global.h"
#include <QWidget>

namespace Qt::FileTools
{
	class QT_EXTENSION_EXPORT FileDialogExtension : public QWidget
	{
		Q_OBJECT
	public:
		virtual void readFileInfo(const QString& sFile) = 0;
	};
}