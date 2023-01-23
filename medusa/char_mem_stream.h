#pragma once
#include "pch.h"

class MemoryStreamBuf : public std::streambuf
{
public:
	MemoryStreamBuf(char* array, std::size_t size)
	{
		std::fill_n(array, size, '\0');
		std::streambuf::setp(array, array + size - 1);
	}

	template <std::size_t size>
	MemoryStreamBuf(char(&array)[size]) :
		MemoryStreamBuf(&array[0], size)
	{
	}
};
class MemoryStringStream : virtual MemoryStreamBuf, public std::iostream
{
public:
	MemoryStringStream(char* array, std::size_t size) :
		MemoryStreamBuf(array, size),
		std::iostream(static_cast<MemoryStreamBuf*>(this))
	{
	}

	template <std::size_t size>
	MemoryStringStream(char(&array)[size]) :
		MemoryStreamBuf(array),
		std::iostream(static_cast<MemoryStreamBuf*>(this))
	{
	}
};

template <std::size_t N>
class MemoryStringStreamWithBuffer : public MemoryStringStream
{
public:
	MemoryStringStreamWithBuffer() :
		MemoryStringStream(m_Buffer)
	{}
private:
	char m_Buffer[N];
};
