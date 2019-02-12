#ifndef LOCALE_H
#define LOCALE_H
#include <string>
class Locale{
	public:
		static std::string mLocale;
		static void SetLocale( std::string locale ){ mLocale = locale; }
};
#endif
