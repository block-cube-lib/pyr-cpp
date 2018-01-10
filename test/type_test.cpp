#include <type_traits>

#include <pyrite/config/type.hpp>

#include "gtest/gtest.h"

TEST(type_test, type_size)
{
  using namespace pyrite;
  EXPECT_EQ(sizeof(i8), 1);
  EXPECT_EQ(sizeof(i16), 2);
  EXPECT_EQ(sizeof(i32), 4);
  EXPECT_EQ(sizeof(i64), 8);

  EXPECT_EQ(sizeof(u8), 1);
  EXPECT_EQ(sizeof(u16), 2);
  EXPECT_EQ(sizeof(u32), 4);
  EXPECT_EQ(sizeof(u64), 8);

  EXPECT_EQ(sizeof(f32), 4);
  EXPECT_EQ(sizeof(f64), 8);

  EXPECT_EQ(sizeof(byte), 1);

  EXPECT_EQ(sizeof(ipointer), sizeof(void*));
  EXPECT_EQ(sizeof(upointer), sizeof(void*));
  EXPECT_EQ(sizeof(pointer_diff), sizeof(void*));

  EXPECT_TRUE(sizeof(void*) <= sizeof(isize));
  EXPECT_TRUE(sizeof(void*) <= sizeof(usize));
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
  EXPECT_TRUE(std::is_signed_v<ipointer>);

  EXPECT_TRUE(std::is_unsigned_v<u8>);
  EXPECT_TRUE(std::is_unsigned_v<u16>);
  EXPECT_TRUE(std::is_unsigned_v<u32>);
  EXPECT_TRUE(std::is_unsigned_v<u64>);
  EXPECT_TRUE(std::is_unsigned_v<byte>);
  EXPECT_TRUE(std::is_unsigned_v<usize>);
  EXPECT_TRUE(std::is_unsigned_v<upointer>);
}
