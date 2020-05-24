#include <jni.h>
#include "gtest/gtest.h"

#include "main.h"

TEST(SampleTest, AssertionTrue) {
    ASSERT_EQ(1, 1);
}

TEST(SampleTest, TestSampleMethod) {
    ASSERT_EQ(1, test());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

extern "C" JNIEXPORT jint JNICALL
Java_com_amoseui_ruffjni_nativetest_NativeTest_runTest(
        JNIEnv*,
        jobject) {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
