#pragma once
#include <vector>
#include "GameEnums.h"

namespace Catan {

	class ResourceBag {
	public:
		ResourceBag();
		ResourceBag(int _wood, int _sheep, int _clay, int _iron, int _wheat);
		ResourceBag(int _count, Resource _res);
		~ResourceBag();

		const std::vector<int>::iterator begin();
		const std::vector<int>::iterator end();

		void			addResource(int _count, Resource _res);
		int				operator[](int _el);

		ResourceBag&	operator=(const ResourceBag& _bag);

		ResourceBag&	operator+=(const ResourceBag& _bag);
		ResourceBag&	operator-=(const ResourceBag& _bag);

		bool			operator<=(const ResourceBag& _bag) const;
		bool			operator>=(const ResourceBag& _bag) const;

		std::string		print() const;

	private:
		std::vector<int> resources;
	};

}