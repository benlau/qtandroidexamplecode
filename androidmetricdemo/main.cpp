/* Author: Ben Lau (https://github.com/benlau) */

#include <QtGui/QGuiApplication>
#include <QtCore>
#include <QQuickItem>
#include <QQmlContext>
#include <QVariantMap>
#include "qtquick2applicationviewer.h"
#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QAndroidJniObject>
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;

    QVariantMap androidContext;
    androidContext["density"] = 1.0;

#ifdef Q_OS_ANDROID
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject resource = activity.callObjectMethod("getResources","()Landroid/content/res/Resources;");
    QAndroidJniObject metrics = resource.callObjectMethod("getDisplayMetrics","()Landroid/util/DisplayMetrics;");
    androidContext["density"] = metrics.getField<float>("density");
#endif

    viewer.setMainQmlFile(QStringLiteral("qml/androidmetricdemo/splash.qml"));
    viewer.showExpanded();

    QQuickItem *root = viewer.rootObject();
    QMetaObject::invokeMethod(root,"init",Qt::QueuedConnection,
                              Q_ARG(QVariant,androidContext));

    return app.exec();
}
