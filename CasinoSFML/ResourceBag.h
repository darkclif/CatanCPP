#pragma once
#include <vector>

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
	ResourceBag(int _count, Resource _res);
	~ResourceBag();

	void			addResource(int _count, Resource _res);
	int				operator[](int _el);
	ResourceBag&	operator+=(const ResourceBag& _bag);

	std::string		print() const;

private:
	std::vector<int> resources;
};