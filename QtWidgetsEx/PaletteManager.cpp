#include "PaletteManager.h"

namespace Qt::WidgetsEx
{
	PaletteManager* PaletteManager::m_pInstance = nullptr;
	
	void PaletteManager::newPalette(Palette* pNew)
	{
		auto iter = std::find(m_vPalettes.begin(), m_vPalettes.end(), pNew);
		if (iter == m_vPalettes.end())
		{
			m_vPalettes.push_back(pNew);
			emit sg_newPalette(pNew);
		}
	}

	void PaletteManager::releasePalette(Palette* pPalette)
	{
		auto iter = std::find(m_vPalettes.begin(), m_vPalettes.end(), pPalette);
		if (iter != m_vPalettes.end())
			m_vPalettes.erase(iter);
	}

	PaletteManager* const PaletteManager::Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new PaletteManager;
		return m_pInstance;
	}

	PaletteManager::~PaletteManager()
	{
		//
	}
}