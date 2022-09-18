#include <gtest/gtest.h>

#include <potentia/math/quat/Quaternion.h>


TEST(Quaternion, HandleChainableSettingCorrectly) {
  ASSERT_TRUE(Quaternion::Identity().Equal(Quaternion::Identity()));
}
