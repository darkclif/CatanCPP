#include "ResourceBag.h"
#include <sstream>

ResourceBag::ResourceBag()
{
	resources.resize(_SIZE);
	for (int i = 0; i < _SIZE; i++) {
		resources[i] = 0;
	}
}

ResourceBag::ResourceBag(int _count, Resource _res): ResourceBag()
{
	resources[_res] += _count;
}


ResourceBag::~ResourceBag()
{
}

void ResourceBag::addResource(int _count, Resource _res)
{
	resources[_res] += _count;
}

int ResourceBag::operator[](int _res) {
	return resources[_res];
}

ResourceBag&	ResourceBag::operator+=(const ResourceBag& _bag) {
	for (int i = 0; i < Resource::_SIZE; i++) {
		this->resources[i] += _bag.resources[i];
	}
	return *this;
}

std::string ResourceBag::print() const
{
	std::stringstream retString;
	retString << "(";

	for ( auto lResource : resources) {
		retString << lResource << ",";
	}

	retString << ")";
	return retString.str();
}
