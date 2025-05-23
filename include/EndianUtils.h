#pragma once

#include "Types.h"
#ifdef _MSC_VER
#include <stdlib.h>
#define __builtin_bswap16(a) _byteswap_ushort(a)
#define __builtin_bswap32(a) _byteswap_ulong(a)
#define __builtin_bswap64(a) _byteswap_uint64(a)
#endif

namespace Framework
{
	class CEndian
	{
	public:
		template <typename IntType>
		static void FromMSBF(IntType&);

		static uint16 FromMSBF16(uint16 value)
		{
			return __builtin_bswap16(value);
		}

		static uint32 FromMSBF32(uint32 value)
		{
			return __builtin_bswap32(value);
		}

		static uint64 FromMSBF64(uint64 value)
		{
			return __builtin_bswap64(value);
		}

		static uint16 ToMSBF16(uint16 value)
		{
			return __builtin_bswap16(value);
		}

		static uint32 ToMSBF32(uint32 value)
		{
			return __builtin_bswap32(value);
		}

		static uint64 ToMSBF64(uint64 value)
		{
			return __builtin_bswap64(value);
		}
	};

	template <>
	inline void CEndian::FromMSBF(uint16& value)
	{
		value = FromMSBF16(value);
	}

	template <>
	inline void CEndian::FromMSBF(uint32& value)
	{
		value = FromMSBF32(value);
	}

	template <>
	inline void CEndian::FromMSBF(uint64& value)
	{
		value = FromMSBF64(value);
	}

	class MSBFU16
	{
	public:
		MSBFU16() = default;

		MSBFU16(uint16 value)
		{
			(*this) = value;
		}
		
		MSBFU16& operator =(uint16 rhs)
		{
			value = CEndian::ToMSBF16(rhs);
			return (*this);
		}

		operator uint16() const
		{
			return CEndian::FromMSBF16(value);
		}
		
	private:
		uint16 value = 0;
	};

	class MSBFS32
	{
	public:
		MSBFS32& operator =(int32 rhs)
		{
			value = CEndian::ToMSBF32(rhs);
			return (*this);
		}

		operator int32() const
		{
			return CEndian::FromMSBF32(value);
		}
		
	private:
		int32 value = 0;
	};

	class MSBFU32
	{
	public:
		MSBFU32() = default;

		MSBFU32(uint32 value)
		{
			(*this) = value;
		}

		MSBFU32& operator =(uint32 rhs)
		{
			value = CEndian::ToMSBF32(rhs);
			return (*this);
		}

		operator uint32() const
		{
			return CEndian::FromMSBF32(value);
		}
		
	private:
		uint32 value = 0;
	};

	class MSBFU64
	{
	public:
		MSBFU64() = default;

		MSBFU64& operator =(uint64 rhs)
		{
			value = CEndian::ToMSBF64(rhs);
			return (*this);
		}
		
		operator uint64() const
		{
			return CEndian::FromMSBF64(value);
		}
		
	private:
		uint64 value = 0;
	};

	class MSBFFP32
	{
	public:
		MSBFFP32() = default;

		MSBFFP32& operator =(float rhs)
		{
			uint32 intValue = *reinterpret_cast<uint32*>(&rhs);
			value = CEndian::ToMSBF32(intValue);
			return (*this);
		}
		
		operator float() const
		{
			uint32 intValue = CEndian::FromMSBF32(value);
			return *reinterpret_cast<float*>(&intValue);
		}
		
	private:
		uint32 value = 0;
	};

	class MSBFFP64
	{
	public:
		MSBFFP64() = default;

		MSBFFP64& operator =(double rhs)
		{
			uint64 intValue = *reinterpret_cast<uint64*>(&rhs);
			value = CEndian::ToMSBF64(intValue);
			return (*this);
		}
		
		operator double() const
		{
			uint64 intValue = CEndian::FromMSBF64(value);
			return *reinterpret_cast<double*>(&intValue);
		}
		
	private:
		uint64 value = 0;
	};
}
