#pragma once
class SelectableMapItem
{
public:
	enum Type {
		TILE,
		LOCATION,
		ROAD
	};

	Type		getType() const;

	bool		isHighlighted();
	void		setHighlight(bool _light);

	SelectableMapItem(Type _type) : itemType{ _type }, highlighted{false} {};
	~SelectableMapItem();
private:
	Type		itemType;
	bool		highlighted;
};

