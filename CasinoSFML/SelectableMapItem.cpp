#include "SelectableMapItem.h"

SelectableMapItem::Type SelectableMapItem::getType() const
{
	return itemType;
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
