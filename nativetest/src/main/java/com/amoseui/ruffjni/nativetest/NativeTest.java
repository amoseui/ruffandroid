package com.amoseui.ruffjni.nativetest;

public class NativeTest {

    public native int runTest();

    static {
        System.loadLibrary("main_unittest");
    }
}
