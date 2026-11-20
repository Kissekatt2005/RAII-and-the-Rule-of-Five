#pragma once
#include <CodeAnalysis/Warnings.h>

#pragma warning(push, 0)
#pragma warning(disable : ALL_CODE_ANALYSIS_WARNINGS)
#include <gtest/gtest.h>
#pragma warning(pop)

#define DISABLE_WARNINGS_FROM_GTEST \
    __pragma(warning(push)) \
    __pragma(warning(disable : 26446 26455 26426 26409 26477 26433 26818 26440))

#define RESTORE_WARNINGS __pragma(warning(pop))