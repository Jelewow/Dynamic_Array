#include "gtest/gtest.h"
#include "../Dynamic_Array_v2/List.h"

TEST(List, Init)
{
	List<int> emptyList;
	EXPECT_EQ(emptyList.size(), 0);

	List<int> notEmptyList(12);
	EXPECT_EQ(notEmptyList.size(), 12);
}