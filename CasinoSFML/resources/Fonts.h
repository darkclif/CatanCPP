#pragma once
#pragma once

#include <map>
#include <string>

namespace Catan {

	class Fonts
	{
	public:
		enum Name {
			/* All font names */
			DEFAULT
		};

		static std::string getPath(Name _name);

		Fonts();
		~Fonts();
	private:
		// Paths to resources
		static const std::map< Name, std::string> mPaths;
	};

}

