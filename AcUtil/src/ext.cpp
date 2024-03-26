/* Aerials Util Functions */
#include <dmsdk/sdk.h>
constexpr auto EMPTYSTR = "";


/* APIs */
#if !( defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID) )
	void AcUtilDoHapticFeedback() {}
#else
	extern void AcUtilDoHapticFeedback();
#endif

namespace AcUtil {

	inline int Base64Encode(lua_State* L) {
		size_t InSize, OutSize;
		uint32_t OSZ;

		// Get Lua String, Acquire InSize & Calculate OutSize
		const auto Input = (uint8_t*)luaL_checklstring(L, 1, &InSize);
		OutSize = (InSize / 3 + 1) * 4;

		// Encode & Do Returns
		auto Output = new uint8_t[OutSize + 1];
		if ( dmCrypt::Base64Encode(Input, (uint32_t)InSize, Output, &OSZ) )
			lua_pushlstring(L, (char*)Output, OutSize);
		else
			lua_pushlstring(L, (char*)EMPTYSTR, 0);

		delete Output;   // POD, using either delete or delete[] is ok
		return 1;
	}

	inline int Base64Decode(lua_State* L) {
		size_t InSize;		uint32_t OSZ;
		const auto Input = (uint8_t*)luaL_checklstring(L, 1, &InSize);

		// Decode & Do Returns
		auto Output = new uint8_t[InSize / 4];
		if ( dmCrypt::Base64Decode(Input, (uint32_t)InSize, Output, &OSZ) )
			lua_pushlstring( L, (char*)Output, InSize / 4 );
		else
			lua_pushlstring(L, (char*)EMPTYSTR, 0);

		delete Output;
		return 1;
	}

	inline int StrToSha1(lua_State* L) {
		size_t InSize;
		const auto Input = (uint8_t*)luaL_checklstring(L, 1, &InSize);

		// Calculate & Do Returns
		auto Output = new uint8_t[20];
		if ( dmCrypt::HashSha1(Input, (uint32_t)InSize, Output) )
			lua_pushlstring(L, (char*)Output, 20);
		else
			lua_pushlstring(L, (char*)EMPTYSTR, 0);

		delete Output;
		return 1;
	}

	inline int StrToSha256(lua_State* L) {
		size_t InSize;
		const auto Input = (uint8_t*)luaL_checklstring(L, 1, &InSize);

		// Calculate & Do Returns
		auto Output = new uint8_t[32];
		if ( dmCrypt::HashSha256(Input, (uint32_t)InSize, Output) )
			lua_pushlstring(L, (char*)Output, 32);
		else
			lua_pushlstring(L, (char*)EMPTYSTR, 0);

		delete Output;
		return 1;
	}

	inline int StrToSha512(lua_State* L) {
		size_t InSize;
		const auto Input = (uint8_t*)luaL_checklstring(L, 1, &InSize);

		// Calculate & Do Returns
		auto Output = new uint8_t[64];
		if ( dmCrypt::HashSha512(Input, (uint32_t)InSize, Output) )
			lua_pushlstring(L, (char*)Output, 64);
		else
			lua_pushlstring(L, (char*)EMPTYSTR, 0);

		delete Output;
		return 1;
	}

	inline int StrToMd5(lua_State* L) {
		size_t InSize;
		const auto Input = (uint8_t*)luaL_checklstring(L, 1, &InSize);

		// Calculate & Do Returns
		auto Output = new uint8_t[16];
		if ( dmCrypt::HashMd5(Input, (uint32_t)InSize, Output) )
			lua_pushlstring(L, (char*)Output, 16);
		else
			lua_pushlstring(L, (char*)EMPTYSTR, 0);

		delete Output;
		return 1;
	}

	inline int DoHapticFeedback(lua_State* L) {
		AcUtilDoHapticFeedback();
		return 0;
	}

}


/* Binding Stuff */
namespace AuBinding {

	constexpr luaL_reg LuaAPIs[] = {
		{"Base64Encode", AcUtil::Base64Encode}, {"Base64Decode", AcUtil::Base64Decode}, {"StrToSha1", AcUtil::StrToSha1}, {"StrToSha256", AcUtil::StrToSha256},
		{"StrToSha512", AcUtil::StrToSha512}, {"StrToMd5", AcUtil::StrToMd5}, {"DoHapticFeedback", AcUtil::DoHapticFeedback}, {nullptr, nullptr}
	};

	// Lifecycle Calls
	inline dmExtension::Result Init(dmExtension::Params* p) {   // Init
		luaL_register( p->m_L, "AcUtil", AuBinding::LuaAPIs );
		lua_pop( p->m_L, 1 );
		return dmExtension::RESULT_OK;
	}
	inline dmExtension::Result OK(dmExtension::Params* p) {   // Final
		return dmExtension::RESULT_OK;
	}
	inline dmExtension::Result APPOK(dmExtension::AppParams* params) {   // AppInit, AppFinal
		return dmExtension::RESULT_OK;
	}

}

DM_DECLARE_EXTENSION(AcUtilExt, "AcUtil", AuBinding::APPOK, AuBinding::APPOK, AuBinding::Init, nullptr, nullptr, AuBinding::OK)