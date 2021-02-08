#pragma once
#ifndef __ENGINE_ENUM_H__

enum class EDisplayMode
{
	FullMode,
	WinMode
};

enum class ERenderID
{
	Priority,
	NonAlpha,
	Alpha,
	UI,
	Max
};

enum class ETextureType
{
	Default,
	Cube,
	Auto,
};

#define __ENGINE_ENUM_H__
#endif

