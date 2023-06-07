#pragma once

#include <Spore\MathUtils.h>
#include <Spore\Resource\ResourceObject.h>
#include <EASTL\vector.h>
#include <EASTL\string.h>

#define cArithmeticaResourcePtr eastl::intrusive_ptr<App::cArithmeticaResource>

namespace App
{
	/// Represents an `.arth` file, which is ascripts that allows doing mathematical operations on certain values.
	/// Example usage:
	/// ```cpp
	/// App::cArithmeticaResource arithmetica;
	/// App::cArithmeticaResource::Load(id("CustomArthTest"), GroupIDs::Scripts1, arithmetica);
	/// arithmetica.SetValue("myVariable", 2.0f);
	/// arithmetica.ComputeAll();
	/// App::ConsolePrintF("%f", arithmetica.GetValue("output"));
	/// ```
	class cArithmeticaResource
		: public Resource::CachedResourceObject
	{
	public:
		static const uint32_t TYPE = 0x355D6F5;

		cArithmeticaResource();
		virtual ~cArithmeticaResource();

		/* 14h */	virtual void func14h();

		/// Clears all data and computes only a specific function in the file.
		/// @param functionName
		/* 18h */	virtual void ComputeFunction(const char* functionName);

		/// Clears all data and computes the entire arithmetic file.
		/* 1Ch */	virtual void ComputeAll();

		/// Loads an instance of arithmetica resource.
		/// @param instanceID
		/// @param groupID Usually GroupIDs::Scripts1
		/// @param dst
		/// @returns
		static bool Load(uint32_t instanceID, uint32_t groupID, cArithmeticaResource& dst);

		/// Gets the value of a variable, the file must have been computed before calling this.
		/// @param variableName
		/// @returns The value of the variable, or 0.0 if the variable is not found
		float GetValue(const char* variableName);

		/// Sets the value of a variable. It will not affect the results until the file is computed again.
		/// @param variableName
		/// @param value
		void SetValue(const char* variableName, float value);

	public:
		struct OperationDefinition
		{
			/* 00h */	int opCode;  // 9
			/* 04h */	float value;
			/* 08h */	int variableIndex;  // -1, index to mVariableNames
			/* 0Ch */	int line;  // not initialized
		};
		ASSERT_SIZE(OperationDefinition, 0x10);

		struct ArithmeticaState
		{
			/* 00h */	eastl::vector<float> mStack;
			/* 14h */	eastl::vector<int> mCallStackOpIndices;
		};
		ASSERT_SIZE(ArithmeticaState, 0x28);

		struct ArithmeticaFunction
		{
			/* 00h */	int mStringIndex;
			/* 04h */	int mStartOpIndex;
		};
		ASSERT_SIZE(ArithmeticaFunction, 8);

		/* 18h */	eastl::vector<eastl::string> mVariableNames;
		/* 2Ch */	eastl::vector<float> mVariableValues;
		/* 40h */	eastl::vector<OperationDefinition> mOperators;
		/* 54h */	int field_54;  // not initialized
		/* 58h */	ArithmeticaState mState;
		/* 80h */	eastl::vector<ArithmeticaFunction> mFunctions;
	};
	ASSERT_SIZE(cArithmeticaResource, 0x94);

	namespace Addresses(cArithmeticaResource)
	{
		DeclareAddress(Load);  // 0x7F2810 0x7F2300
		DeclareAddress(ComputeFunction);  // 0x7F26A0 0x7F2190
		DeclareAddress(ComputeAll);  // 0x7F2AD0 0x7F25C0
		DeclareAddress(GetValue);  // 0x7F2B60 0x7F2650
		DeclareAddress(SetValue);  // 0x7F2B90 0x7F2680
	}
}
