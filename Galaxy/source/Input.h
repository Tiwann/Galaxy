#pragma once

namespace Galaxy
{
	enum class Key
	{
		NONE,
		A, B, C, D, E, F, G,
		H, I, K, L, M, N, O, 
		P, Q, R, S, T, U, V, 
		W, X, Y, Z,
		ALPHA0, ALPHA2, ALPHA3,
		ALPHA4, ALPHA5, ALPHA6,
		ALPHA7, ALPHA8, ALPHA9,
		CTRL, SHIFT, ALT, TAB, CAPS,
		SPACE, BACKSPACE, DELETE, 
	};


	class Input
	{
		static bool GetKeyDown(const Key& key);
	};
}


