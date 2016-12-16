#pragma once
#include <vector>

namespace Catan {

	enum Resource : int {
		WOOD,
		SHEEP,
		CLAY,
		IRON,
		WHEAT,
		_SIZE
	};

	class ResourceBag {
	public:
		ResourceBag();
		ResourceBag(int _wood, int _sheep, int _clay, int _iron, int _wheat);
		ResourceBag(int _count, Resource _res);
		~ResourceBag();

		void			addResource(int _count, Resource _res);
		int				operator[](int _el);

		ResourceBag&	operator=(const ResourceBag& _bag);

		ResourceBag&	operator+=(const ResourceBag& _bag);
		ResourceBag&	operator-=(const ResourceBag& _bag);

		bool	operator<=(const ResourceBag& _bag) const;
		bool	operator>=(const ResourceBag& _bag) const;

		std::string		print() const;

	private:
		std::vector<int> resources;
	};

}