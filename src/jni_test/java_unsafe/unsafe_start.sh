#!/bin/sh
tradePortalPID=0
MODULE_PATH=.
APP_MAIN=UnsafeTest

APP_JAVA_GC_PRINT="-XX:+PrintGCDetails -XX:+PrintGCTimeStamps -XX:+PrintGCDateStamps -XX:+PrintHeapAtGC -XX:MaxDirectMemorySize=32m -Dsun.reflect.inflationThreshold=0 -Xloggc:$MODULE_PATH/data_gc.log"
APP_JAVA_GC="-XX:+UseG1GC -XX:SurvivorRatio=8 -XX:MaxGCPauseMillis=100 -XX:ParallelGCThreads=8 -XX:+HeapDumpOnOutOfMemoryError -XX:HeapDumpPath=$MODULE_PATH/data_dump"
APP_JAVA_OPTS="-server -Xms128m -Xmx128m -Xss512k -XX:MetaspaceSize=32m -XX:MaxMetaspaceSize=32m -XX:NativeMemoryTracking=detail"

getTradeProtalPID(){
    javaps=`$JAVA_HOME/bin/jps -l | grep $APP_MAIN`
    if [ -n "$javaps" ]; then
        tradePortalPID=`echo $javaps | awk '{print $1}'`
    else
        tradePortalPID=0
    fi
}

start(){
    getTradeProtalPID
    echo "==============================================================================================="
    if [ $tradePortalPID -ne 0 ]; then
        echo "$APP_MAIN already started(PID=$tradePortalPID)"
        echo "==============================================================================================="
    else
        echo -n "Starting $APP_MAIN \n"
        $JAVA_HOME/bin/java -Djava.ext.dirs=.:lib $APP_JAVA_OPTS $APP_JAVA_GC $APP_JAVA_GC_PRINT $APP_MAIN
        getTradeProtalPID
        if [ $tradePortalPID -ne 0 ]; then
            echo "(PID=$tradePortalPID)...[Success]"
            echo "==============================================================================================="
        else
            echo "[Failed]"
            echo "==============================================================================================="
        fi
    fi
}

start