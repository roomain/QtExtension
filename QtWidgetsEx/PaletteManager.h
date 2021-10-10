#pragma once
#include <qobject.h>
#include "qtwidgetsex_global.h"

namespace Qt::WidgetsEx
{
	class Palette;

	class QTWIDGETSEX_EXPORT PaletteManager :public QObject
	{
		friend class Palette;
		Q_OBJECT
	private:
		static PaletteManager* m_pInstance;	/*!< single ton instance*/
		std::vector<Palette*> m_vPalettes;	/*!< palettes database*/
		PaletteManager() = default;

		void newPalette(Palette* pNew);
		void releasePalette(Palette* pPalette);

	public:
		static PaletteManager* const Instance();
		virtual ~PaletteManager();
		using iterator = std::vector<Palette*>::iterator;
		using const_iterator = std::vector<Palette*>::const_iterator;
		iterator begin() { return m_vPalettes.begin(); }
		iterator end() { return m_vPalettes.end(); }
		const_iterator cbegin()const noexcept { return m_vPalettes.cbegin(); }
		const_iterator cend()const noexcept { return m_vPalettes.cend(); }
		
	signals:
		void sg_newPalette(const Palette*);
	};
}

