#pragma once


class helper
{
public:
	static char* getDataFromBuffer(char* buffer)
	{
		int len = stringLen(buffer);
		char* str = new char[len + 1];
		for (int i = 0; i < len; i++) {
			str[i] = buffer[i];
		}
		str[len] = '\0';
		return str;
	}

	static int stringLen(const char* str)
	{
		int len;
		for (len = 0; str[len] != '\0'; len++);
		return len;
	}

	static void stringCopy(const char* src, char*& dest)
	{
		if (dest) {
			delete[] dest;
			dest = 0;
		}
		int len = stringLen(src);
		dest = new char[len + 1];
		for (int i = 0; i < len; i++) {
			dest[i] = src[i];
		}
		dest[len] = '\0';
	}

	static bool stringCompare(const char* str1, const char* str2)
	{
		int len1 = stringLen(str1);
		int len2 = stringLen(str2);

		if (len1 == len2) {
			for (int i = 0; i < len1; i++) {
				if (str1[i] != str2[i])
					return false;
			}
			return true;
		}
		return false;
	}
};