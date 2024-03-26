/* Aerials Util Functions */
#pragma once
#include <dmsdk/sdk.h>


/* APIs */
namespace AcUtil {

	inline int Base64Encode(lua_State* L) {
		// Get Lua String, Acquire InSize & Calculate OutSize
		// Encode & Do Returns
		return 1;
	}

	inline int Base64Decode(lua_State* L) {
		// Get Lua String, Acquire InSize & Calculate OutSize
		// Decode & Do Returns
		return 1;
	}

	inline int StrToSha1(lua_State* L) {
		// Get Lua String, Acquire InSize
		// Calculate & Do Returns
		return 1;
	}

	inline int StrToSha256(lua_State* L) {
		// Get Lua String, Acquire InSize
		// Calculate & Do Returns
		return 1;
	}

	inline int StrToSha512(lua_State* L) {
		// Get Lua String, Acquire InSize
		// Calculate & Do Returns
		return 1;
	}

	inline int StrToMd5(lua_State* L) {
		// Get Lua String, Acquire InSize
		// Calculate & Do Returns
		return 1;
	}

	inline int DoHapticFeedback(lua_State* L) {
		return 0;
	}

}


/* Binding Stuff */
namespace AuBinding {

	// Lua Registry
	constexpr luaL_reg LuaAPIs[] = {
		{"Base64Encode", AcUtil::Base64Encode}, {"Base64Decode", AcUtil::Base64Decode}, {"StrToSha1", AcUtil::StrToSha1},
		{"StrToSha256", AcUtil::StrToSha256}, {"StrToSha512", AcUtil::StrToSha512}, {"StrToMd5", AcUtil::StrToMd5},
		{"DoHapticFeedback", AcUtil::DoHapticFeedback}, {nullptr, nullptr}
	};

	// Init
	inline dmExtension::Result Init(dmExtension::Params* p) {
		luaL_register( p->m_L, "AcUtil", AuBinding::LuaAPIs );
		lua_pop( p->m_L, 1 );
		return dmExtension::RESULT_OK;
	}

	// OK
	inline dmExtension::Result OK(dmExtension::Params* p) {
		return dmExtension::RESULT_OK;
	}

	// APPOK
	inline dmExtension::Result APPOK(dmExtension::AppParams* params) {
		return dmExtension::RESULT_OK;
	}

}

DM_DECLARE_EXTENSION(AcUtil, "AcUtil", AuBinding::APPOK, AuBinding::APPOK, AuBinding::Init, nullptr, nullptr, AuBinding::OK)