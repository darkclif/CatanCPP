#include "ResourceBag.h"
#include <sstream>

namespace Catan {

	ResourceBag::ResourceBag()
	{
		int lResNumber = (int)Resource::_SIZE;
		resources.resize(lResNumber);

		for (int i = 0; i < lResNumber; i++) {
			resources[i] = 0;
		}
	}

	ResourceBag::ResourceBag(int _wood, int _sheep, int _clay, int _iron, int _wheat) : ResourceBag()
	{
		resources[0] = _wood;
		resources[1] = _sheep;
		resources[2] = _clay;
		resources[3] = _iron;
		resources[4] = _wheat;
	}

	ResourceBag::ResourceBag(int _count, Resource _res) : ResourceBag()
	{
		if ((int)_res < (int)Resource::_SIZE && (int)_res >= 0)
			resources[(int)_res] += _count;
	}

	ResourceBag::~ResourceBag()
	{
	}

	const std::vector<int>::iterator ResourceBag::begin()
	{
		return resources.begin();
	}

	const std::vector<int>::iterator ResourceBag::end()
	{
		return resources.end();
	}

	void ResourceBag::addResource(int _count, Resource _res)
	{
		if ((int)_res < (int)Resource::_SIZE && (int)_res >= 0)
			resources[(int)_res] += _count;
		else
			return;
	}

	int ResourceBag::operator[](int _res) {
		if ((int)_res < (int)Resource::_SIZE && (int)_res >= 0)
			return resources[(int)_res];
		else
			return 0;
	}

	ResourceBag&	ResourceBag::operator=(const ResourceBag& _bag) {
		for (int i = 0; i < (int)Resource::_SIZE; i++) {
			this->resources[i] = _bag.resources[i];
		}
		return *this;
	}

	ResourceBag&	ResourceBag::operator+=(const ResourceBag& _bag) {
		for (int i = 0; i < (int)Resource::_SIZE; i++) {
			this->resources[i] += _bag.resources[i];
		}
		return *this;
	}

	ResourceBag&	ResourceBag::operator-=(const ResourceBag& _bag) {
		for (int i = 0; i < (int)Resource::_SIZE; i++) {
			this->resources[i] -= _bag.resources[i];
		}
		return *this;
	}

	bool	ResourceBag::operator<=(const ResourceBag& _bag) const {
		for (int i = 0; i < (int)Resource::_SIZE; i++) {
			if (!(this->resources[i] <= _bag.resources[i]))
				return false;
		}

		return true;
	};

	bool	ResourceBag::operator>=(const ResourceBag& _bag) const {
		for (int i = 0; i < (int)Resource::_SIZE; i++) {
			if (!(this->resources[i] >= _bag.resources[i]))
				return false;
		}

		return true;
	};

	std::string ResourceBag::print() const
	{
		std::stringstream retString;
		retString << "(";

		for (auto lResource : resources) {
			retString << lResource << ",";
		}

		retString << ")";
		return retString.str();
	}

}