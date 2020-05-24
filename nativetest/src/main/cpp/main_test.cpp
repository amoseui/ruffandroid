#include <android/log.h>
#include <jni.h>
#include <gtest/gtest.h>

#include "main.h"

#define LOG_TAG "MAIN_TEST"
#define LOGUNK(...) __android_log_print(ANDROID_LOG_UNKNOWN, LOG_TAG, __VA_ARGS__)
#define LOGDEF(...) __android_log_print(ANDROID_LOG_DEFAULT, LOG_TAG, __VA_ARGS__)
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_FATAL_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGS(...) __android_log_print(ANDROID_SILENT_ERROR, LOG_TAG, __VA_ARGS__)

// As we are the native side of an Android app, we don't have any 'console', so
// gtest's standard output goes nowhere.
// Instead, we inject an "EventListener" in gtest and then we print the results
// using LOG, which goes to adb logcat.
class AndroidLogPrinter : public ::testing::EmptyTestEventListener {
 public:
  void Init(int argc, char** argv);

  // EmptyTestEventListener
  virtual void OnTestProgramStart(
      const ::testing::UnitTest& unit_test) override;
  virtual void OnTestStart(const ::testing::TestInfo& test_info) override;
  virtual void OnTestPartResult(
      const ::testing::TestPartResult& test_part_result) override;
  virtual void OnTestEnd(const ::testing::TestInfo& test_info) override;
  virtual void OnTestProgramEnd(const ::testing::UnitTest& unit_test) override;
};

void AndroidLogPrinter::Init(int argc, char** argv) {
  // InitGoogleTest must be called befure we add ourselves as a listener.
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();
  // Adds a listener to the end.  Google Test takes the ownership.
  listeners.Append(this);
}

void AndroidLogPrinter::OnTestProgramStart(
    const ::testing::UnitTest& unit_test) {
  LOGE("[ START      ] %d", unit_test.test_to_run_count());
}

void AndroidLogPrinter::OnTestStart(const ::testing::TestInfo& test_info) {
  LOGE("[ RUN      ] %s.%s", test_info.test_case_name(), test_info.name());
}

void AndroidLogPrinter::OnTestPartResult(
    const ::testing::TestPartResult& test_part_result) {
  LOGE("%s in %s:%d\n%s\n",
      test_part_result.failed() ? "*** Failure" : "Success",
      test_part_result.file_name(),
      test_part_result.line_number(),
      test_part_result.summary());
}

void AndroidLogPrinter::OnTestEnd(const ::testing::TestInfo& test_info) {
  LOGE("%s %s.%s",
      test_info.result()->Failed() ? "[  FAILED  ]" : "[       OK ]",
      test_info.test_case_name(), test_info.name());
}

void AndroidLogPrinter::OnTestProgramEnd(
    const ::testing::UnitTest& unit_test) {
  LOGE("[ END      ] %d", unit_test.successful_test_count());
}

TEST(SampleTest, AssertionTrue) {
    ASSERT_EQ(1, 1);
}

TEST(SampleTest, TestSampleMethod) {
    ASSERT_EQ(1, test());
}

int main(int argc, char **argv) {
    AndroidLogPrinter* log = new AndroidLogPrinter();
    log->Init(argc, argv);
    return RUN_ALL_TESTS();
}

extern "C" JNIEXPORT jint JNICALL
Java_com_amoseui_ruffjni_nativetest_NativeTest_runTest(
        JNIEnv*,
        jobject) {
    return main(0, nullptr);
}

