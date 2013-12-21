package com.github.qt;

import android.view.View;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;
import android.content.Context;
import android.app.Activity;
import org.qtproject.qt5.android.QtNative;
import java.lang.String;

/* QtRunner - A helper class for QtAndroidRunner to execute action on UI thread
 */

public class QtRunner {

    public QtRunner() {
    }

    /* Post a request to invoke an action on UI thread
     *
     */

    public static void post() {
        Activity activity = QtNative.activity();
        Runnable runnable = new Runnable () {
            public void run() {
                invoke();
            };
        };

        activity.runOnUiThread(runnable);
    }

    private static native void invoke();
}
