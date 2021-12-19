#include "pch.h"
#include "../Dynamic_Array_v2/List.h"

TEST(List, Capacity) 
{
  List<int> emptyList;
  EXPECT_EQ(emptyList.capacity(), 8);

  List<int> notEmptyList(13);
  EXPECT_EQ(notEmptyList.capacity(), 13);
}

TEST(List, Size)
{
	List<int> emptyList;
	EXPECT_EQ(emptyList.size(), 0);
}

TEST(List, InsertInt)
{
	List<int> list;
	list.insert(5);
	list.insert(6);
	list.insert(7);
	EXPECT_EQ(list[0], 5);
	EXPECT_EQ(list[1], 6);

	list.insert(1, 1);
	EXPECT_EQ(list[0], 5);
	EXPECT_EQ(list[1], 1);
	EXPECT_EQ(list[2], 6);
	EXPECT_EQ(list[3], 7);
}

TEST(List, InsertString)
{
	List <std::string> list1(10);
	list1.insert("h");
	list1.insert("world");
	list1.insert("!");
	EXPECT_EQ(list1[0], "h");
	EXPECT_EQ(list1[1], "world");

	list1.insert(1, "ello ");
	EXPECT_EQ(list1[0], "h");
	EXPECT_EQ(list1[1], "ello ");
	EXPECT_EQ(list1[2], "world");
	EXPECT_EQ(list1[3], "!");
}

TEST(List, Remove)
{
	List <std::string> list1;
	list1.insert("h");
	list1.insert("w");
	list1.insert("!");
	list1.insert("1");

	list1.remove(0);
	list1.remove(1);
	EXPECT_EQ(list1[0], "w");
	EXPECT_EQ(list1[1], "1");
}

TEST(List, Iterator)
{
	List <std::string> list1;
	for (int i = 0; i < 10; ++i)
	{
		list1.insert("hello");
		//list1.insert("world");
	}

	for (auto it = list1.iterator(); it.hasNext(); it.next())
	{
		EXPECT_EQ("hello", it.get());
		//it.next();
		//if (!it.hasNext()) break;
		//EXPECT_EQ("world", it.get());
	}

	//EXPECT_EQ(400, list1.size());
}

TEST(List, SetIterator)
{
	List <std::string> list1;
	for (int i = 0; i < 10; ++i)
	{
		list1.insert("hello");
	}

	for (auto it = list1.iterator(); it.hasNext(); it.next())
	{
		it.set("qwe");
	}

	for (auto it = list1.iterator(); it.hasNext(); it.next())
	{
		EXPECT_EQ("qwe", it.get());
	}
}