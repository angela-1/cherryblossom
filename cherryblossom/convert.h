#pragma once



void UTF8ToUnicode(char *str, wchar_t *end);
void UnicodeToUTF8(wchar_t * str, char *end);
void ANSIToUnicode(char *str, wchar_t *end);
void UnicodeToANSI(wchar_t * str, char *end);
