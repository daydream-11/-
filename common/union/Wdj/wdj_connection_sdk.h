// Copyright (c) 2013 The Wandoujia Authors. All rights reserved.
#ifndef PLATFORM_WDJ_CONNECTION_WDJ_CONNECTION_SDK_H_
#define PLATFORM_WDJ_CONNECTION_WDJ_CONNECTION_SDK_H_

// 连接引擎事件列表
#define WDJ_EVENT_DEVICE_LIST_CHANGED  "device.list.changed"
#define WDJ_EVENT_DEVICE_STATE_CHANGED "device.state.changed"
#define WDJ_EVENT_INSTALL_APK_COMPLETE "install.apk.complete"
#define WDJ_EVENT_FILE_TRANSFER_COMPLETE "file.transfer.complete"
#define WDJ_EVENT_FILE_TRANSFER_UPDATE "file.transfer.update"
#define WDJ_EVENT_ADB_SHELL_EXEC_COMPLETE "adb.shell.complete"

#define ENGINE_EVENT_BROADCAST_MSG_NAME L"WDJConnEngineOnEvent"

namespace wdj {
namespace connection {

// usb连接引擎状态(engine error code)
enum {
  EE_READY = 0,
  EE_CONFIG_DOWNLOAD_FAILED,
  EE_PACKAGE_DOWNLOAD_FAILED,
  EE_PACKAGE_UNZIP_FAILED
};

// 连接状态枚举(connection state), for state()
typedef enum {
  CS_GENERAL_ERROR = 0,
  CS_SUCCESS = 2,
  CS_OFFLINE = -10,
  CS_ADB_DEBUG_CLOSE = 10,
  CS_DOWNLOADING_DRIVER = 13,
  CS_DOWNLOAD_DRIVER_FAILED = -14,
  CS_INSTALL_DRIVER = 14,  // 安装驱动失败会有一个负值
  CS_INSTALL_DRIVER_SUCCESS = 104,
  CS_DOWNLOAD_DRIVER_SUCCESS = 105,
};

// 第三方需要实现的接口
class Application {
 public:
  Application() {}
  virtual ~Application() {}
 public:
  virtual const char* get_third_name() const = 0;
  virtual const char* get_third_key() const = 0;
  // settings
  virtual bool need_default_wizard() { return false; }
};

// 所有接口的基类
class WDJInterface {
 public:
  WDJInterface() {}
  virtual ~WDJInterface() {}
};

// 事件相关接口
class WDJEvent {
 public:
  WDJEvent() {}
  virtual ~WDJEvent() {}
  virtual const char* event_name() const = 0;
  virtual bool QueryEventInfo(const char* event_info_name, void** event_info_pointer) const = 0;
};

class WDJEventHandler : public WDJInterface {
 public:
  WDJEventHandler() {}
  virtual ~WDJEventHandler() {}
  virtual void OnEvent(const WDJEvent* event) = 0;
};

// 连接服务
class WDJConnection : public WDJInterface {
 public:
  static const char* interface_name() { return "WDJConnection"; }
  WDJConnection() {}
  virtual ~WDJConnection() {}

  virtual void ConnectDevice(const char* device_id) = 0;
  virtual void DisconnectDevice(const char* device_id) = 0;
};

class WDJAndroidDeviceInfo : public WDJInterface {
 public:
  WDJAndroidDeviceInfo() {}
  virtual ~WDJAndroidDeviceInfo() {}
  virtual const char* device_id() const = 0;
  virtual const char* display_name() const = 0;
  virtual const char* adb_name() const = 0;
  virtual const char* disk() const = 0;
  virtual const char* usb_guide_url() const = 0;
  virtual bool is_plugin() const = 0;
  virtual bool is_connected() const = 0;
  virtual int state() const = 0;
  virtual const WDJAndroidDeviceInfo* next_device() const = 0;
};

// 应用安装服务
enum ApkInstallLocation {
  kAUTO          = 0,
  kFORCE_MEMORY  = 1,
  kPREFER_SDCARD = 2,
  kFORCE_SDCARD  = 3,
  kPREFER_MEMORY = 4,
};

class WDJApkService : public WDJInterface {
 public:
  static const char* interface_name() { return "WDJApkService"; }
  WDJApkService() {}
  virtual ~WDJApkService() {}
  virtual int InstallApk(const char* device_id, const wchar_t* apk_path, const ApkInstallLocation install_location, bool overwrite, bool recommend_wdj) = 0;
};

class WDJApkInstallResult : public WDJInterface {
 public:
  WDJApkInstallResult() {}
  virtual ~WDJApkInstallResult() {}
  virtual int job_id() const = 0;
  virtual const char* device_id() const = 0;
  virtual bool is_success() const = 0;
  virtual const char* error_info() const = 0;
};

// 文件传输服务
class WDJFileTransferService : public WDJInterface {
 public:
  static const char* interface_name() { return "WDJFileTransferService"; }
  WDJFileTransferService() {}
  virtual ~WDJFileTransferService() {}
  virtual int PushFile(const char* device_id, const wchar_t* local_file_path, const wchar_t* device_file_path, bool overwrite) = 0;
};

// adb shell服务
class WDJAdbShellService : public WDJInterface {
 public:
  static const char* interface_name() { return "WDJAdbShellService"; }
  WDJAdbShellService() {}
  virtual ~WDJAdbShellService() {}
  virtual int ShellExec(const char* device_id, const char* command_line) = 0;
};

class WDJFileTransferEvent : public WDJInterface {
 public:
  WDJFileTransferEvent() {}
  virtual ~WDJFileTransferEvent() {}
  virtual int progress() const = 0;
  virtual int speed() const = 0;
  virtual int job_id() const = 0;
};

class WDJFileTransferResult : public WDJInterface {
 public:
  WDJFileTransferResult() {}
  virtual ~WDJFileTransferResult() {}
  virtual bool is_success() const = 0;
  virtual int job_id() const = 0;
  virtual const char* error_info() const = 0;
};

class WDJShellExecResult : public WDJInterface {
 public:
  WDJShellExecResult() {}
  virtual ~WDJShellExecResult() {}
  virtual int job_id() const = 0;
  virtual bool is_success() const = 0;
  virtual const char* output() const = 0;
};

// 连接引擎内核对象
class WDJCoreInterface {
 public:
  WDJCoreInterface() {}
  virtual ~WDJCoreInterface() {}
  virtual void RegisterConnectionEventHandler(const char* event_name, WDJEventHandler* event_handler) = 0;
  virtual void UnRegisterConnectionEventHandler(const char* event_name, WDJEventHandler* event_handler) = 0;
  virtual bool QueryInterface(const char* interface_name, WDJInterface** interface_pointer) = 0;
};

template <class T>
bool WDJGetService(T** service_pointer) {
  WDJCoreInterface* core = NULL;
  if (!fnQueryWDJCore(&core)) {
    return false;
  }
  WDJInterface* service = NULL;
  if (!core->QueryInterface(T::interface_name(), &service)) {
    return false;
  }
  (*service_pointer) = static_cast<T*>(service);
  return true;
}

}
}

#endif  // PLATFORM_WDJ_CONNECTION_WDJ_CONNECTION_SDK_H_
