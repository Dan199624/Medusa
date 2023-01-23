#include "pch.h"
#include "log.h"
#include "batch.h"
#include "range.h"

namespace memory
{
	void batch::Add(std::string name, pattern pattern, std::function<void(Ptr)> callback)
	{
		m_entries.emplace_back(std::move(name), std::move(pattern), std::move(callback));
	}

	void batch::run(range region)
	{
		bool all_found = true;
		for (auto& entry : m_entries)
		{
			if (auto result = region.scan(entry.m_pattern))
			{
				if (entry.m_callback)
				{
					std::invoke(std::move(entry.m_callback), result);
					medusa::g_logger.log("Pattern", std::format("Found {}", entry.m_name).c_str());
				}
				else
				{
					all_found = false;
					medusa::g_logger.log("Pattern", std::format("Failed To Find {}", entry.m_name).c_str());
				}
			}
			else
			{
				all_found = false;
				medusa::g_logger.log("Pattern", std::format("Failed To Find {}", entry.m_name).c_str());
			}
		}
		m_entries.clear();
		if (!all_found)
		{
			throw std::runtime_error("Failed to find some patterns.");
		}
	}
}