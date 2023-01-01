#pragma once

#ifndef DECLSPEC_NOVTABLE
#if (_MSC_VER >= 1100) && defined(__cplusplus)
#define DECLSPEC_NOVTABLE   __declspec(novtable)
#else
#define DECLSPEC_NOVTABLE
#endif
#endif

#ifdef _68K_
#define STDMETHODCALLTYPE       __cdecl
#else
//#define STDMETHODCALLTYPE       __stdcall
#define STDMETHODCALLTYPE       
#endif
#define STDMETHODVCALLTYPE      __cdecl

#define STDAPICALLTYPE          __stdcall
#define STDAPIVCALLTYPE         __cdecl

#define DECLARE_INTERFACE(iface)                        struct DECLSPEC_NOVTABLE iface
#define DECLARE_INTERFACE_(iface, baseiface)            struct DECLSPEC_NOVTABLE iface : public baseiface

#define STDMETHOD(method)        virtual COM_DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type,method)  virtual COM_DECLSPEC_NOTHROW type STDMETHODCALLTYPE method
#define PURE                    = 0
#define THIS_
#define THIS                    void
#define CONST const

#define REFIID const GUID &
#define REFGUID const GUID &

#define COM_DECLSPEC_NOTHROW   __declspec(nothrow)

struct GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
};

typedef long HRESULT;
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL           *PBOOL;
typedef BOOL            *LPBOOL;
typedef BYTE           *PBYTE;
typedef BYTE            *LPBYTE;
typedef int            *PINT;
typedef int             *LPINT;
typedef WORD           *PWORD;
typedef WORD            *LPWORD;
typedef long            *LPLONG;
typedef DWORD          *PDWORD;
typedef DWORD           *LPDWORD;
typedef void            *LPVOID;
typedef const void      *LPCVOID;
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
#endif

typedef char         INT8, *PINT8;
typedef short        INT16, *PINT16;
typedef int          INT32, *PINT32;
typedef long long      INT64 __attribute__ ((aligned (8))), *PINT64;
typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef unsigned long long    UINT64 __attribute__ ((aligned (8))), *PUINT64;

typedef long long LONGLONG __attribute__ ((aligned (8)));
typedef unsigned long long ULONGLONG __attribute__ ((aligned (8)));

struct HWND{int unused;};
struct HMONITOR{int unused;};
struct HDC{int unused;};

union LARGE_INTEGER {
    struct {
        DWORD LowPart;
        LONG HighPart;
    } u;
    LONGLONG QuadPart;
};

typedef void *HANDLE;

struct RECT
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
};

struct PALETTEENTRY {
    BYTE        peRed;
    BYTE        peGreen;
    BYTE        peBlue;
    BYTE        peFlags;
};

struct RGNDATAHEADER {
    DWORD   dwSize;
    DWORD   iType;
    DWORD   nCount;
    DWORD   nRgnSize;
    RECT    rcBound;
};

struct RGNDATA {
    RGNDATAHEADER   rdh;
    char            Buffer[1];
};

struct POINT
{
    LONG  x;
    LONG  y;
};