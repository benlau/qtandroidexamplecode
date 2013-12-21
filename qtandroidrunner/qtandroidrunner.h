/*
 * Author Ben Lau
 * Website: https://github.com/benlau
 */

#ifndef QTANDROIDRUNNER_H
#define QTANDROIDRUNNER_H

#include <QObject>
#include <QMutex>
#include <QRunnable>
#include <QQueue>

class QtAndroidRunnerPriv;

/// Schedule to execute code on Android application UI Thread
/**
 * @brief The QtAndroidRunner class
 */
class QtAndroidRunner : public QObject
{
    Q_OBJECT

public:
    ~QtAndroidRunner();

    /// Initialize the QAndroidRunner
    /**
     * @remark It should be called within JNI_OnLoad
     */
    static void init();

    /// Returns the global QAndroidRunner instance.
    static QtAndroidRunner* instance();

public slots:
    /// Schedule to execute QRunnable on Android application UI thread
    /**
     * @param runnable
     * @remarks  If the current thread is the UI thread, then the action is executed immediately.
     *
     * Note that the runner takes ownership of the runnable if runnable->autoDelete() returns true, and the runnable will be deleted automatically by the runner after the runnable->run() returns.
     */
    void start(QRunnable * runnable);

private:
    explicit QtAndroidRunner(QObject *parent = 0);

    QtAndroidRunnerPriv* d;
    friend class QtAndroidRunnerPriv;
};

#endif // QTANDROIDRUNNER_H
