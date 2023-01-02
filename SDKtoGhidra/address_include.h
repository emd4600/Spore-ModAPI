#pragma once
#define MODAPI_DLL_EXPORT
#define Addresses(name) name##_addresses
#define DefineAddress(name, address) unsigned int name = address

//unsigned int SelectAddress(unsigned int disk, unsigned int march2017);