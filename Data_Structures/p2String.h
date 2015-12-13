#ifndef __p2String_H__
#define __p2String_H__

//#include <stdlib.h>
//#include <stdarg.h>
#include <string.h>
#include "p2Defs.h"

class p2String
{
public:

	// Constructors
	p2String()
	{
		Alloc(1);
		clear();
	}

	p2String(uint max_capacity)
	{
		Alloc(MAX(1,max_capacity));
		clear();
	}

	p2String(const p2String& string)
	{
		Alloc(string.length() + 1);
		strcpy_s(str, max_capacity, string.str);
	}

	p2String(const char *string)
	{
		if(string != nullptr)
		{
			Alloc(strlen(string) + 1);
			strcpy_s(str, max_capacity, string);
		}
		else
		{
			Alloc(1);
			clear();
		}
	}
	
	// Destructor
	virtual ~p2String()
	{
		RELEASE_ARRAY(str);
	}

	// Operators
	bool operator== (const p2String& string) const
	{
		return strcmp(string.str, str) == 0;
	}

	bool operator== (const char* string) const
	{
		if(string != nullptr)
			return strcmp(string, str) == 0;
		return false;
	}

	bool operator!= (const p2String& string) const
	{
		return strcmp(string.str, str) != 0;
	}

	bool operator!= (const char* string) const
	{
		if(string != nullptr)
			return strcmp(string, str) != 0;
		return true;
	}
	
	const p2String& operator= (const p2String& string)
	{
		if(string.length() + 1 > this->max_capacity)
		{
			RELEASE_ARRAY(str);
			Alloc(string.length() + 1);
		}

		strcpy_s(str, max_capacity, string.str);

		return(*this);
	}

	const p2String& operator= (const char* string)
	{
		if(string != nullptr)
		{
			if(strlen(string) + 1 > max_capacity)
			{
				RELEASE_ARRAY(str);
				Alloc(strlen(string)+1);
			}

			strcpy_s(str, max_capacity, string);
		}
		else
			clear();

		return(*this);
	}
	
	const p2String& operator+= (const p2String& string)
	{
		unsigned int need_max_capacity = string.length() + length() + 1;

		if(need_max_capacity > max_capacity)
		{
			char* tmp = str;
			Alloc(need_max_capacity);
			strcpy_s(str, max_capacity, tmp);
			RELEASE_ARRAY(tmp);
		}

		strcat_s(str, max_capacity, string.str);

		return(*this);
	}

	const p2String& operator+= (const char* string)
	{
		if(string != nullptr)
		{
			unsigned int need_max_capacity = strlen(string) + length() + 1;

			if(need_max_capacity > max_capacity)
			{
				char* tmp = str;
				Alloc(need_max_capacity);
				strcpy_s(str, max_capacity, tmp);
				RELEASE_ARRAY(tmp);
			}

			strcat_s(str, max_capacity, string);
		}

		return(*this);
	}

	// Utils
	uint length() const
	{
		return strlen(str);
	}

	uint size() const
	{
		return strlen(str);
	}

	bool empty() const
	{
		return strlen(str) == 0;
	}

	void clear()
	{
		str[0] = '\0';
	}

	const char* c_str() const
	{
		return str;
	}

	uint capacity() const
	{
		return max_capacity;
	}

private:

	void Alloc(unsigned int required_memory)
	{
		max_capacity = required_memory;
		str = new char[max_capacity];
	}

private:

	char* str;
	uint max_capacity;

};

#endif // __p2String_H__