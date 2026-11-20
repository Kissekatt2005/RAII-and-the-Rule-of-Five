#include "pch.h"
#include "NaiveVector.h"
#include <cstddef>
#include <concepts>

DISABLE_WARNINGS_FROM_GTEST

using workshop::NaiveVector;
//static_assert(std::regular <NaiveVector>);

TEST(NaiveVector, StartsEmpty) {
	const NaiveVector<int> values;

	EXPECT_EQ(std::size_t{ 0 }, values.size());
	EXPECT_TRUE(values.empty());
	EXPECT_EQ(nullptr, values.data());
}

TEST(NaiveVector, HasFill) {
	const NaiveVector<int> values(5, 3);

	EXPECT_EQ(std::size_t{ 5 }, values.size());
	EXPECT_EQ(3, values.at(3));
	EXPECT_THROW(values.at(values.size()), std::out_of_range);

}

TEST(NaiveVector, CanModefy) {
	NaiveVector<int> values(5, 3);

	values.at(0) = 2;
	EXPECT_EQ(std::size_t{ 2 }, values.at(0));
	EXPECT_EQ(std::size_t{ 3 }, values.at(1));
}
TEST(NaiveVector, CanCopy) {
	NaiveVector<int> values1(5, 3);
	values1.at(0) = 2;

	NaiveVector<int> values2 = values1;
	EXPECT_NE(values1.data(), values2.data());

	EXPECT_EQ(values1.at(0), values2.at(0));
	EXPECT_EQ(values1.at(1), values2.at(1));
	EXPECT_EQ(values1.at(3), values2.at(3));
}

TEST(NaiveVector, CanCopyValue) {
	NaiveVector<int> values1(3, 3);
	NaiveVector<int> values2(5, 2);
	values2 = values1;
	NaiveVector<int> valuesEmpty(0, 2);
	values1 = valuesEmpty;
	(values2 = values2);

	EXPECT_EQ(values1.size(), 0);
	EXPECT_EQ(values2.size(), 3);
	EXPECT_EQ(values2.at(0), 3);
	EXPECT_EQ(values2.at(2), 3);


}
TEST(NaiveVector, CanTransfer) {
	NaiveVector<int> values1(3, 3);
	int* pointer = values1.data();
	NaiveVector<int> valuesSaved = std::move(values1);
	NaiveVector<int> valuesOwns(5, 7);
	NaiveVector<int> values2(6, 4);
	NaiveVector<int> valuesEmpty(0, 4);
	NaiveVector<int> valuesSelfMove(1, 2);
	valuesSelfMove = std::move(valuesSelfMove);
	values2 = std::move(valuesEmpty);
	valuesOwns = std::move(valuesSaved);

	EXPECT_EQ(values1.data(), nullptr);
	EXPECT_EQ(values1.size(), 0);

	EXPECT_EQ(valuesOwns.data(), pointer);
	EXPECT_EQ(valuesOwns.size(), 3);

	EXPECT_EQ(values2.data(), nullptr);
	EXPECT_EQ(values2.size(), 0);

	values1 = NaiveVector<int>(8, 9);
	EXPECT_EQ(values1.size(), 8);

	EXPECT_EQ(valuesSelfMove.size(), 1);


}

TEST(NaiveVector, CanCopyEmpty) {
	NaiveVector<int> values1(0, 3);

	NaiveVector<int> values2 = values1;
	EXPECT_EQ(values2.data(), nullptr);
}
TEST(NaiveVector, CanCopyLifeTime) {
	NaiveVector <int>values1(3, 3);
	values1.at(1) = 2;

	{
		NaiveVector<int> values2 = values1;

	}

	EXPECT_EQ(values1.at(0), 3);
	EXPECT_EQ(values1.at(1), 2);
	EXPECT_EQ(values1.at(2), 3);
}

TEST(NaiveVector, Empty)
{
	const NaiveVector<int> values(0, 3);

	EXPECT_TRUE(values.empty());

}

TEST(NaiveVector, BracketTest)
{
	NaiveVector<int> values(3, 3);
	values[1] = 5;

	EXPECT_EQ(values.at(1), values[1]);
	EXPECT_EQ(values.at(1), 5);
	EXPECT_EQ(values[1], 5);
	//EXPECT_EQ(values[5], 5);
}

TEST(NaiveVector, FrontBack)
{
	NaiveVector<int> values(4, 88);
	std::ranges::iota(values, 0);
	EXPECT_EQ(values.front(), 0);
	//EXPECT_EQ(values[1], 1);
	//EXPECT_EQ(values[2], 2);
	EXPECT_EQ(values.back(), 3);
}

#ifndef NDEBUG
TEST(NaiveVector, FrontDeath)
{
	NaiveVector<int> empty;

	EXPECT_DEATH(empty.front(), "empty");
}
#endif

#ifndef NDEBUG
TEST(NaiveVector, BackDeath)
{
	NaiveVector<int> empty;

	EXPECT_DEATH(empty.back(), "empty");
}
#endif

TEST(NaiveVector, TestBegin)
{
	NaiveVector<int> values(4, 88);
	std::ranges::iota(values, 0);

	NaiveVector<int> empty;
	EXPECT_EQ(*values.begin(), values.at(0));
	EXPECT_EQ(empty.begin(), empty.end());
}

#ifndef NDEBUG
TEST(NaiveVector, TestEnd)
{
	NaiveVector<int> values(4, 88);
	std::ranges::iota(values, 0);

	NaiveVector<int> empty;
	EXPECT_EQ(values.end(), values.begin()+ values.size());
	EXPECT_EQ(empty.begin(), empty.end());
}
#endif

TEST(NaiveVector, RangeForVisitsEveryElement) {
	NaiveVector<int> values(3);
	values.at(0) = 1;
	values.at(1) = 10;
	values.at(2) = 100;

	int sum = 0;
	for (const int value : values) {
		sum += value;
	}

	EXPECT_EQ(sum, 111);
}

TEST(NaiveVector, RangeForVisitsEveryElement7) {
	NaiveVector<int> values(3);
	values.at(0) = 1;
	values.at(1) = 10;
	values.at(2) = 100;

	for (int& value : values) {
		value = 7;
	}

	EXPECT_EQ(values.at(0), 7);
	EXPECT_EQ(values.at(2), 7);
}

TEST(NaiveVector, TestFind) {
	NaiveVector<int> values(4, 88);
	std::ranges::iota(values, 0);

	const NaiveVector values2 = values;

	auto number2 = std::find(values2.begin(), values2.end(), 2);

	EXPECT_EQ(*number2, values2.at(2));
	//EXPECT_EQ(values.at(2), 7);
}

TEST(NaiveVector, TestSort) {
	NaiveVector<int> values(3);
	values.at(0) = 3;
	values.at(1) = 1;
	values.at(2) = 2;

	std::sort(values.begin(), values.end());

	EXPECT_GT(values.at(1), values.at(0));
	EXPECT_GT(values.at(2), values.at(1));
}

TEST(NaiveVector, TestEqual) {
	const NaiveVector<int> values1(5, 3);
	const NaiveVector<int> values2 = values1;
	const NaiveVector<int> valuesDifferent(6,3);

	EXPECT_TRUE(values1 == values2);
	EXPECT_FALSE(values1 != values2);
	EXPECT_TRUE(valuesDifferent != values1);
}

TEST(NaiveVector, TestEqualEmptyu) {
	const NaiveVector<int> values1;
	const NaiveVector<int> values2;

	EXPECT_TRUE(values1 == values2);
	//EXPECT_FALSE(values1 != values2);
}

//TEST(NaiveVector, TestRegular) {
//	EXPECT_TRUE(std::regular <NaiveVector>);
//}

TEST(NaiveVector, TestSpaceShip) {
	NaiveVector<int> values1(2,1);
	values1.at(1) = 9;
	NaiveVector<int> values2(2,1);
	values2.at(0) = 2;
	values2.at(1) = 0;

	EXPECT_TRUE((values1 <=> values2) < 0);
	EXPECT_TRUE((values2 <=> values1) > 0);
	//EXPECT_FALSE(values1 != values2);
}

TEST(NaiveVector, TestSpaceShip2) {
	NaiveVector<int> values1(3, 1);
	values1.at(0) = 1;
	values1.at(1) = 2;
	values1.at(2) = 0;
	NaiveVector<int> values2(2, 1);
	values2.at(0) = 1;
	values2.at(1) = 2;

	EXPECT_TRUE((values2 <=> values1) < 0);
	//EXPECT_FALSE(values1 != values2);
}

TEST(NaiveVector, TestSpaceShip3) {
	NaiveVector<int> values1(3, 1);
	values1.at(0) = 1;
	values1.at(1) = 2;
	values1.at(2) = 0;
	NaiveVector<int> values2 = values1;

	EXPECT_TRUE((values2 <=> values1) == 0);
	//EXPECT_FALSE(values1 != values2);
}

TEST(NaiveVector, TestDouble) {
	NaiveVector<double> values1(3, 1.2);

	EXPECT_EQ(values1.at(1), 1.2);
	//EXPECT_FALSE(values1 != values2);
}

TEST(NaiveVector, TestClear) {
	NaiveVector<double> values1(3, 1.2);
	values1.clear();
	EXPECT_EQ(values1.begin(), values1.end());
	//EXPECT_FALSE(values1 != values2);
}

TEST(NaiveVector, TestPushBack) {
	NaiveVector<int> values;
	values.push_back(1);
	EXPECT_EQ(values.at(0),1);
	//EXPECT_FALSE(values1 != values2);
}

RESTORE_WARNINGS