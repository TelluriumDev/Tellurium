#pragma once

#ifndef TUAPI
#ifdef TU_EXPORT
#define TUAPI __declspec(dllexport)
#else
#define TUAPI __declspec(dllimport)
#endif
#endif