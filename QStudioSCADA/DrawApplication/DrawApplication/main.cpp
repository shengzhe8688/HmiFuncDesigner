﻿#include <QApplication>
#include <QMessageBox>
#include "MainWindow.h"
#include "ConfigUtils.h"
#include "DrawListUtils.h"
#include "PluginManager.h"
#include "ProjectData.h"
#include "qtsingleapplication.h"

/**
 * @brief qMain
 * @param argc
 * @param argv argv[0]--application name,
 *             argv[1]--project path,
 *             argv[2]--project name,
 *             argv[3]--graph page name,
 * @return
 */
int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    QtSingleApplication app(argc, argv); // 程序单实例运行

    if (app.isRunning())
    {
        return !app.sendMessage("start " + app.applicationDirPath());
    }

    QString szProjPath = "";
    QString szProjName = "";
    QString szGraphPageName = "";

    if(argc == 4) {
        szProjPath = argv[1];
        szProjName = argv[2];
        szGraphPageName = argv[3];
    } else {
        QMessageBox::information(Q_NULLPTR, "提示", "画面编辑程序只能由工程管理器调用！");
        return 0;
    }

    // 加载元素插件
    PluginManager::getInstance()->loadPlugin();

    MainWindow mainWin(szProjPath, szProjName, szGraphPageName);
    mainWin.openGraphPage(szProjPath, szProjName, szGraphPageName);
    app.setActivationWindow(&mainWin);
    mainWin.show();

    int ret = app.exec();

    // 释放插件
    PluginManager::getInstance()->releasePlugin();

    return ret;
}
