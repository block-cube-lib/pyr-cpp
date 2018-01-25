#include <type_traits>

#include <pyrite/core/type.hpp>

#include "gtest/gtest.h"

TEST(type_test, type_size)
{
  using namespace pyrite;
  EXPECT_EQ(sizeof(i8), 1u);
  EXPECT_EQ(sizeof(i16), 2u);
  EXPECT_EQ(sizeof(i32), 4u);
  EXPECT_EQ(sizeof(i64), 8u);

  EXPECT_EQ(sizeof(u8), 1u);
  EXPECT_EQ(sizeof(u16), 2u);
  EXPECT_EQ(sizeof(u32), 4u);
  EXPECT_EQ(sizeof(u64), 8u);

  EXPECT_EQ(sizeof(f32), 4u);
  EXPECT_EQ(sizeof(f64), 8u);

  EXPECT_EQ(sizeof(byte), 1u);

  EXPECT_LE(sizeof(iptr), sizeof(void*));
  EXPECT_LE(sizeof(uptr), sizeof(void*));
  EXPECT_LE(sizeof(ptrdiff), sizeof(decltype((int*)0 - (int*)0)));

  EXPECT_LE(sizeof(void*), sizeof(isize));
  EXPECT_LE(sizeof(void*), sizeof(usize));
}

TEST(type_test, sign)
{
  using namespace pyrite;
  EXPECT_TRUE(std::is_signed_v<i8>);
  EXPECT_TRUE(std::is_signed_v<i16>);
  EXPECT_TRUE(std::is_signed_v<i32>);
  EXPECT_TRUE(std::is_signed_v<i64>);
  EXPECT_TRUE(std::is_signed_v<f32>);
  EXPECT_TRUE(std::is_signed_v<f64>);
  EXPECT_TRUE(std::is_signed_v<isize>);
  EXPECT_TRUE(std::is_signed_v<iptr>);

  EXPECT_TRUE(std::is_unsigned_v<u8>);
  EXPECT_TRUE(std::is_unsigned_v<u16>);
  EXPECT_TRUE(std::is_unsigned_v<u32>);
  EXPECT_TRUE(std::is_unsigned_v<u64>);
  EXPECT_TRUE(std::is_unsigned_v<byte>);
  EXPECT_TRUE(std::is_unsigned_v<usize>);
  EXPECT_TRUE(std::is_unsigned_v<uptr>);
}
