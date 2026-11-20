#include "pch.h"
#include "NaiveVector.h"
#include <cstddef>

DISABLE_WARNINGS_FROM_GTEST

using workshop::NaiveVector;

TEST(NaiveVector, StartsEmpty) {
	const NaiveVector values;

	EXPECT_EQ(std::size_t{ 0 }, values.size());
	EXPECT_TRUE(values.empty());
	EXPECT_EQ(nullptr, values.data());
}

TEST(NaiveVector, HasFill) {
	const NaiveVector values(5, 3);

	EXPECT_EQ(std::size_t{ 5 }, values.size());
	EXPECT_EQ(3, values.at(3));
	EXPECT_THROW(values.at(values.size()), std::out_of_range);

}

TEST(NaiveVector, CanModefy) {
	NaiveVector values(5, 3);

	values.at(0) = 2;
	EXPECT_EQ(std::size_t{ 2 }, values.at(0));
	EXPECT_EQ(std::size_t{ 3 }, values.at(1));
}
TEST(NaiveVector, CanCopy) {
	NaiveVector values1(5, 3);
	values1.at(0) = 2;

	NaiveVector values2 = values1;
	EXPECT_NE(values1.data(), values2.data());

	EXPECT_EQ(values1.at(0), values2.at(0));
	EXPECT_EQ(values1.at(1), values2.at(1));
	EXPECT_EQ(values1.at(3), values2.at(3));
}

TEST(NaiveVector, CanCopyValue) {
	NaiveVector values1(3, 3);
	NaiveVector values2(5, 2);
	values2 = values1;
	NaiveVector valuesEmpty(0, 2);
	values1 = valuesEmpty;
	(values2 = values2);

	EXPECT_EQ(values1.size(), 0);
	EXPECT_EQ(values2.size(), 3);
	EXPECT_EQ(values2.at(0), 3);
	EXPECT_EQ(values2.at(2), 3);


}
TEST(NaiveVector, CanTransfer) {
	NaiveVector values1(3, 3);
	int* pointer = values1.data();
	NaiveVector valuesSaved = std::move(values1);
	NaiveVector valuesOwns(5, 7);
	NaiveVector values2(6, 4);
	NaiveVector valuesEmpty(0, 4);
	NaiveVector valuesSelfMove(1, 2);
	valuesSelfMove = std::move(valuesSelfMove);
	values2 = std::move(valuesEmpty);
	valuesOwns = std::move(valuesSaved);

	EXPECT_EQ(values1.data(), nullptr);
	EXPECT_EQ(values1.size(), 0);

	EXPECT_EQ(valuesOwns.data(), pointer);
	EXPECT_EQ(valuesOwns.size(), 3);

	EXPECT_EQ(values2.data(), nullptr);
	EXPECT_EQ(values2.size(), 0);

	values1 = NaiveVector(8, 9);
	EXPECT_EQ(values1.size(), 8);

	EXPECT_EQ(valuesSelfMove.size(), 1);


}

TEST(NaiveVector, CanCopyEmpty) {
	NaiveVector values1(0, 3);

	NaiveVector values2 = values1;
	EXPECT_EQ(values2.data(), nullptr);
}
TEST(NaiveVector, CanCopyLifeTime) {
	NaiveVector values1(3, 3);
	values1.at(1) = 2;

	{
		NaiveVector values2 = values1;

	}

	EXPECT_EQ(values1.at(0), 3);
	EXPECT_EQ(values1.at(1), 2);
	EXPECT_EQ(values1.at(2), 3);
}

TEST(NaiveVector, Empty)
{
	const NaiveVector values(0, 3);

	EXPECT_TRUE(values.empty());

}

TEST(NaiveVector, BracketTest)
{
	NaiveVector values(3, 3);
	values[1] = 5;

	EXPECT_EQ(values.at(1), values[1]);
	EXPECT_EQ(values.at(1), 5);
	EXPECT_EQ(values[1], 5);
	//EXPECT_EQ(values[5], 5);
}

TEST(NaiveVector, FrontBack)
{
	NaiveVector values(4, 3);
	for (std::size_t i = 0; i < values.size() - 1; i++) {
		values[i] = i;
	}
	EXPECT_EQ(values.front(), 0);
	EXPECT_EQ(values[1], 1);
	EXPECT_EQ(values[2], 3);
	EXPECT_EQ(values.back(), 3);
}

RESTORE_WARNINGS