#include "SelectableMapItem.h"

namespace Catan {

	SelectableMapItem::Mode SelectableMapItem::getMode() const
	{
		return mode;
	}

	SelectableMapItem::LocationSelectionMode SelectableMapItem::getLocationSelectionMode() const
	{
		return locationSelectionMode;
	}

	void SelectableMapItem::setLocationSelectionMode(LocationSelectionMode _locationSelectionMode)
	{
		locationSelectionMode = _locationSelectionMode;
	}

	bool SelectableMapItem::isHighlighted()
	{
		return highlighted;
	}

	void SelectableMapItem::setHighlight(bool _light)
	{
		highlighted = _light;
	}

	SelectableMapItem::~SelectableMapItem()
	{
	}

}