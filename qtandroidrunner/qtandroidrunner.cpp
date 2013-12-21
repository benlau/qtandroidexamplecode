/*
 * Author Ben Lau
 * Website: https://github.com/benlau
 */

#include <QCoreApplication>
#include <QtCore>
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include "qtandroidrunner.h"

#define JCLASS_Name "com/github/qt/QtRunner"

static QtAndroidRunner *m_instance = 0;

class QtAndroidRunnerPriv {
public:
    QMutex mutex;
    QQueue<QRunnable*> queue;
    jclass clazz;
    jmethodID tick;

    QtAndroidRunnerPriv() {
        QAndroidJniEnvironment env;

        clazz = env->FindClass(JCLASS_Name);

        /* QAndroidJniObject only works for
         * core library and cached classes like
         * QtActivity / QtApplication.
         *
         * Therefore, it need to use the raw API
         * and must be executed within the JNI_onLoad()
         * call.
         *
         */

        if (!clazz)
        {
            qCritical() << "Can't find class : " << JCLASS_Name << ". Did init() be called within JNI_onLoad?";
        } else {

            tick = env->GetStaticMethodID(clazz,"post","()V");
            if (tick ==0) {
                qCritical() << "Failed to obtain the method : tick";
            }

            JNINativeMethod methods[] =
            {
                {"invoke", "()V", (void *)&QtAndroidRunnerPriv::invoke},
            };

            // Register the native methods.
            int numMethods = sizeof(methods) / sizeof(methods[0]);
            if (env->RegisterNatives(clazz, methods, numMethods) < 0) {
                if (env->ExceptionOccurred()) {
                    env->ExceptionDescribe();
                    env->ExceptionClear();
                    qCritical() << "Exception in native method registration";
                }
            }

        }
    }


    static void invoke() {
        QRunnable *runnable = 0;

        m_instance->d->mutex.lock();
        if (m_instance->d->queue.size() > 0 ) {
            runnable = m_instance->d->queue.dequeue();
        }
        m_instance->d->mutex.unlock();

        if (runnable) {
            runnable->run();
            if (runnable->autoDelete()) {
                delete runnable;
            }
        }

    }

};

void QtAndroidRunner::init(){
    QtAndroidRunner::instance();
}

QtAndroidRunner *QtAndroidRunner::instance()
{
    if (m_instance == 0) {
        QCoreApplication* app = QCoreApplication::instance();
        m_instance = new QtAndroidRunner(app);
    }

    return m_instance;
}

void QtAndroidRunner::start(QRunnable *runnable)
{
    d->mutex.lock();
    d->queue.append(runnable);
    d->mutex.unlock();

    QAndroidJniEnvironment env;
    env->CallStaticVoidMethod(d->clazz,d->tick);
}

QtAndroidRunner::QtAndroidRunner(QObject *parent) :
    QObject(parent)
{
    d = new QtAndroidRunnerPriv;
}

QtAndroidRunner::~QtAndroidRunner(){
    delete d;
}
