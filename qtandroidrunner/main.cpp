#include <QtGui/QGuiApplication>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <jni.h>
#include "qtandroidrunner.h"
#include "qtquick2applicationviewer.h"

/// Create webview on top of Qt surface
class WebViewInitializer : public QRunnable {

public:
    void run() {
        // Example code to create WebView using C++ method.
        // However, it is not recommended to construct
        // everything using C++. It is very troublesome.
        // It just show how can you execute code with
        // Android application UI thread
        QAndroidJniEnvironment env;

        QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative",
                                                                               "activity", "()Landroid/app/Activity;");
        QAndroidJniObject webView("android/webkit/WebView",
                                  "(Landroid/content/Context;)V",
                                   activity.object<jobject>());

        QAndroidJniObject frameLayout = activity.callObjectMethod("findViewById","(I)Landroid/view/View;",
                                                                  0x01020002); // Hard coded value of android.R.id.content
        QAndroidJniObject layout("android/widget/RelativeLayout",
                                  "(Landroid/content/Context;)V",
                                   activity.object<jobject>());

        QAndroidJniObject params = QAndroidJniObject("android/view/ViewGroup$LayoutParams",
                                    "(II)V",
                                    (int) 0xffffffff,
                                    (int) 0xffffffff);

        layout.callMethod<void>("addView",
                                "(Landroid/view/View;Landroid/view/ViewGroup$LayoutParams;)V",
                                webView.object<jobject>(),
                                params.object<jobject>());

        frameLayout.callMethod<void>("addView",
                                     "(Landroid/view/View;Landroid/view/ViewGroup$LayoutParams;)V",
                                     layout.object<jobject>(),
                                     params.object<jobject>());

        QAndroidJniObject url = QAndroidJniObject::fromString("http://qt-project.org");

        webView.callMethod<void>("loadUrl","(Ljava/lang/String;)V",url.object<jstring>());

        if (env->ExceptionOccurred()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }

    }
};

JNIEXPORT
jint
JNI_OnLoad(JavaVM* vm, void*) {
    Q_UNUSED(vm);
    QtAndroidRunner::init();

    return JNI_VERSION_1_6;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/qtandroidrunner/main.qml"));
    viewer.showExpanded();

    QtAndroidRunner *runner = QtAndroidRunner::instance();
    runner->start(new WebViewInitializer());

    return app.exec();
}
