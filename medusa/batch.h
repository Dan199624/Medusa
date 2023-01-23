#pragma once
#include <functional>
#include <vector>
#include "pattern.h"

namespace memory
{
	class batch
	{
	public:
		explicit batch() = default;
		~batch() noexcept = default;

		void Add(std::string name, pattern pattern, std::function<void(memory::Ptr)> callback);
		void run(range region);

		struct entry
		{
			std::string m_name;
			pattern m_pattern;
			std::function<void(memory::Ptr)> m_callback;

			explicit entry(std::string name, pattern pattern, std::function<void(memory::Ptr)> callback) :
				m_name(std::move(name)),
				m_pattern(std::move(pattern)),
				m_callback(std::move(callback))
			{}
		};

	private:
		std::vector<entry> m_entries;
	};
}