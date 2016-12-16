#pragma once

namespace Catan {

	class SelectableMapItem
	{
	public:
		enum Mode {
			TILE,
			LOCATION,
			ROAD
		};

		enum LocationSelectionMode {
			CITY,
			VILLAGE,
			NONE
		};

		Mode					getMode() const;
		LocationSelectionMode	getLocationSelectionMode() const;

		void			setLocationSelectionMode(LocationSelectionMode _locationType);

		bool		isHighlighted();
		void		setHighlight(bool _light);

		SelectableMapItem(Mode _mode) : mode{ _mode }, highlighted{ false }, locationSelectionMode{ LocationSelectionMode::NONE } {};
		~SelectableMapItem();
	private:
		Mode					mode;
		LocationSelectionMode	locationSelectionMode;

		bool			highlighted;
	};

}