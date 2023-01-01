/*
// T2=int
template <typename T, typename T2=int>
struct vector
{
	static int _DEFAULT_T2;

	T* mpBegin;
	T mTestData;
	T2 mTest2;
};

struct ExportClass
{
	virtual vector<int>& method();

	vector<int> intVector;
	vector<float, long long> boolVector2;
	float matrix[4][4];
};*/

/*namespace eastl
{
	struct other_struct
	{
		int test;
	};

	template <typename T1, typename _T2=int>
	struct vector
	{
		T1 field_1;
		_T2 field_2;
	};
}*/

#include "eastl_include.h"

struct Test
{
	eastl::vector<int> test;
};