﻿#pragma once

#include <qtimer.h>
#include <qwidget.h>

#include "createroomwindow.h"
#include "roominfomationwindow.h"
#include "ui_homewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class HomeWindowClass;
};
QT_END_NAMESPACE

class HomeWindow : public QWidget {
  Q_OBJECT

 public:
  CreateRoomWindow *createRoomWindow;
  RoomInfomationWindow *roomInfomationWindow;

  HomeWindow(QWidget *parent = nullptr);
  ~HomeWindow() { delete ui; }

  void setAccountInfomation(quint64 id,
                            const QString &nickname); /* 设置账户信息 */

 private:
  Ui::HomeWindowClass *ui;

  int mode; /* 0为单人模式, 1为双人对战, 2为三人对战, 3为四人对战 */
  QTimer *errorShowTimer;

  void setMode(int m);                  /* 设置模式 */
  void showError(const QString &error); /* 显示错误信息 */

 public slots:
  void onLogoffSuccess(); /* 响应登出成功 */
  void onLogoffFail(const QString &error) {
    showError(error);
  }; /* 响应登出失败 */
  void onBackFromCreateRoomWindow(int mode);
  void onBackFromRoomInfomationWindow(int mode);

 private slots:
  void onLogoffButton();    /* 响应登出按钮 */
  void onModeButton();      /* 响应模式切换按钮 */
  void onCreatRoomButton(); /* 响应创建房间按钮 */
  void onMatchRoomButton(); /* 响应匹配房间按钮 */

 signals:
  void logoffRequest(); /* 请求登出 */
  void creatRoomRequest(int w, int h, int pattern, int time,
                        int mode);    /* 请求创建房间 */
  void requireRoomRequest();          /* 请求获取房间信息 */
  void enterRoomRequest(quint64 rid); /* 请求进入房间 */
  void logoffSuccess();               /* 登出成功 */
};
