#pragma once
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace memory
{
	class Ptr
	{
	public:
		Ptr(void* ptr = nullptr);
		explicit Ptr(std::uintptr_t ptr);

		template <typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> as();

		template <typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> as();

		template <typename T>
		std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> as();

		template <typename T>
		Ptr add(T offset);

		template <typename T>
		Ptr sub(T offset);

		Ptr rip();

		Ptr from_instruction();

		Ptr call();

		explicit operator bool();

		friend bool operator==(Ptr a, Ptr b);
		friend bool operator!=(Ptr a, Ptr b);
	private:
		void* ptr;
	};

	inline Ptr::Ptr(void* ptr) :
		ptr(ptr)
	{}

	inline Ptr::Ptr(std::uintptr_t ptr) :
		ptr(reinterpret_cast<void*>(ptr))
	{}

	template <typename T>
	inline std::enable_if_t<std::is_pointer_v<T>, T> Ptr::as()
	{
		return static_cast<T>(ptr);
	}

	template <typename T>
	inline std::enable_if_t<std::is_lvalue_reference_v<T>, T> Ptr::as()
	{
		return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(ptr);
	}

	template <typename T>
	inline std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> Ptr::as()
	{
		return reinterpret_cast<std::uintptr_t>(ptr);
	}

	template <typename T>
	inline Ptr Ptr::add(T offset)
	{
		return Ptr(as<std::uintptr_t>() + offset);
	}

	template <typename T>
	inline Ptr Ptr::sub(T offset)
	{
		return Ptr(as<std::uintptr_t>() - offset);
	}

	inline Ptr Ptr::rip()
	{
		return add(as<std::int32_t&>()).add(4);
	}

	inline Ptr Ptr::from_instruction()
	{
		return add(3).rip();
	}

	inline Ptr Ptr::call()
	{
		return add(1).rip();
	}

	inline bool operator==(Ptr a, Ptr b)
	{
		return a.ptr == b.ptr;
	}

	inline bool operator!=(Ptr a, Ptr b)
	{
		return a.ptr != b.ptr;
	}

	inline Ptr::operator bool()
	{
		return ptr != nullptr;
	}
}