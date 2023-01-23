#pragma once
#include <vector>
#include "fwddec.h"
#include "ptr.h"

namespace memory
{
	class range
	{
	public:
		range(Ptr base, std::size_t size);

		Ptr begin();
		Ptr end();
		std::size_t size();

		bool contains(Ptr h);

		Ptr scan(pattern const& sig);
		std::vector<Ptr> scan_all(pattern const& sig);
	protected:
		Ptr m_base;
		std::size_t m_size;
	};
}