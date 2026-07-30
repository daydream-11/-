#include "commands.h"
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QProcess>
#include <QSettings>
#include <QTimer>
#include <QEventLoop>

#ifdef Q_OS_WIN
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include <comdef.h>
#endif

bool cmds::moveFile(const QString &from, const QString &to)
{
    QFileInfo toInfo(to);
    QDir().mkpath(toInfo.absolutePath());

#ifdef Q_OS_WIN
    std::wstring fromStr = QDir::toNativeSeparators(from).toStdWString();
    std::wstring toStr = QDir::toNativeSeparators(to).toStdWString();

    return MoveFileExW(fromStr.c_str(), toStr.c_str(), MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING);
#else
    if (QFile::exists(to))
        QFile::remove(to);
    return QFile::rename(from, to);
#endif
}

bool cmds::copyFile(const QString &from, const QString &to)
{
    QFileInfo toInfo(to);
    QDir().mkpath(toInfo.absolutePath());

#ifdef Q_OS_WIN
    std::wstring fromStr = QDir::toNativeSeparators(from).toStdWString();
    std::wstring toStr = QDir::toNativeSeparators(to).toStdWString();

    return CopyFileW(fromStr.c_str(), toStr.c_str(), FALSE);
#else
    if (QFile::exists(to))
        QFile::remove(to);
    return QFile::copy(from, to);
#endif
}

bool cmds::removePath(const QString &path)
{
#ifdef Q_OS_WIN
    std::wstring nativePath = QDir::toNativeSeparators(path).toStdWString();
    nativePath.append(1, L'\0');

    SHFILEOPSTRUCTW fileOp;
    ZeroMemory(&fileOp, sizeof(fileOp));
    fileOp.wFunc = FO_DELETE;
    fileOp.pFrom = nativePath.c_str();

    fileOp.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI;

    return (SHFileOperationW(&fileOp) == 0);
#else
    QDir dir(path);
    return dir.removeRecursively();
#endif
}

bool cmds::applyRegFile(const QString &regFilePath)
{
    if (!QFile::exists(regFilePath))
        return false;

#ifdef Q_OS_WIN
    QString nativePath = QDir::toNativeSeparators(regFilePath);
    return startProgram("regedit.exe", QString("/s \"%1\"").arg(nativePath));
#else
    // Registry files have no meaning on macOS
    return false;
#endif
}

bool cmds::startProgram(const QString &programPath, const QString &param)
{
    QStringList arguments;
    if (!param.isEmpty())
        arguments = param.split(" ");

    return QProcess::startDetached(programPath, arguments);
}

bool cmds::createShortcut(const QString &programPath, const QString &shortcutPath)
{
#ifdef Q_OS_WIN
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    IShellLinkW* pShellLink = NULL;
    IPersistFile* pPersistFile = NULL;
    bool success = false;

    HRESULT hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&pShellLink);
    if (SUCCEEDED(hr)) {
        std::wstring nativeProgPath = QDir::toNativeSeparators(programPath).toStdWString();
        pShellLink->SetPath(nativeProgPath.c_str());

        QFileInfo fileInfo(programPath);
        std::wstring workingDir = QDir::toNativeSeparators(fileInfo.absolutePath()).toStdWString();
        pShellLink->SetWorkingDirectory(workingDir.c_str());

        QString lnkPath = shortcutPath + "\\" + fileInfo.completeBaseName() + ".lnk";

        hr = pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPersistFile);
        if (SUCCEEDED(hr)) {
            hr = pPersistFile->Save(lnkPath.toStdWString().c_str(), TRUE);
            if (SUCCEEDED(hr))
                success = true;
            pPersistFile->Release();
        }
        pShellLink->Release();
    }

    CoUninitialize();
    return success;
#else
    QFileInfo fileInfo(programPath);
    if (!fileInfo.exists())
        return false;

    QString linkPath = shortcutPath + "/" + fileInfo.completeBaseName();
    // Remove existing link/symlink if present
    if (QFile::exists(linkPath))
        QFile::remove(linkPath);

    return QFile::link(programPath, linkPath);
#endif
}

bool cmds::readReg(const QString &regPath, QString &outValue)
{
    QFileInfo fileInfo{regPath};
    QString dirPath = QDir::toNativeSeparators(fileInfo.path());
    QString keyName = fileInfo.fileName();

    qDebug() << QString{"Read register path: %1, key: %2"}.arg(dirPath, keyName);

    if (keyName.isEmpty() || keyName == "(Default)")
        keyName = "Default";

    QSettings settings{dirPath, QSettings::NativeFormat};

    if (!settings.contains(keyName))
        return false;

    outValue = settings.value(keyName).toString();
    return true;
}

bool cmds::readShortcut(const QString &shortcutPath, QString &outValue)
{
    QFileInfo fileInfo{shortcutPath};

    if (!fileInfo.exists())
        return false;

    if (fileInfo.isSymLink() || fileInfo.isShortcut()) {
        outValue = fileInfo.symLinkTarget();
        return true;
    }

    return false;
}

bool cmds::getDirPath(const QString &path, QString &outValue)
{
    QFileInfo fileInfo(path);

    if (!fileInfo.exists())
        return false;

    if (fileInfo.isFile()) {
        outValue = fileInfo.absolutePath();
        return true;
    }

    if (fileInfo.isDir()) {
        outValue = fileInfo.absoluteFilePath();
        return true;
    }

    return false;
}

#ifdef Q_OS_WIN

#include <windows.h>
#include <tlhelp32.h>

static DWORD getPidByName(const QString &processName)
{
    DWORD pid = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W processEntry;
        processEntry.dwSize = sizeof(processEntry);
        if (Process32FirstW(snapshot, &processEntry)) {
            do {
                if (processName.toStdWString() == processEntry.szExeFile) {
                    pid = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32NextW(snapshot, &processEntry));
        }
        CloseHandle(snapshot);
    }
    return pid;
}

bool cmds::waitForProcessByName(const QString &processName, const QString &waitMode, QString &outVar)
{
    DWORD pid = getPidByName(processName);
    HANDLE hProcess = NULL;

    if (pid != 0)
        hProcess = OpenProcess(SYNCHRONIZE | PROCESS_QUERY_INFORMATION, FALSE, pid);

    if (hProcess == NULL) {
        if (waitMode == "normal") {
            outVar = "0";
            return true;
        } else if (waitMode == "force") {
            return false;
        }
        return false;
    }

    QEventLoop loop;
    QTimer timer;
    bool isExited = false;
    DWORD exitCode = 0;

    QObject::connect(&timer, &QTimer::timeout, &timer, [&]() {
        DWORD waitResult = WaitForSingleObject(hProcess, 0);
        if (waitResult == WAIT_OBJECT_0) {
            if (GetExitCodeProcess(hProcess, &exitCode))
                outVar = QString::number(exitCode);
            else
                outVar = "-1";
            isExited = true;
            loop.quit();
        }
    });

    timer.start(100);
    loop.exec();
    timer.stop();

    CloseHandle(hProcess);
    return isExited;
}

#else // Q_OS_MAC / Unix

static int getPidByName(const QString &processName)
{
    QProcess process;
    process.start("pgrep", QStringList() << "-x" << processName);
    process.waitForFinished();
    QString output = QString::fromUtf8(process.readAll()).trimmed();
    if (output.isEmpty())
        return 0;
    return output.toInt();
}

bool cmds::waitForProcessByName(const QString &processName, const QString &waitMode, QString &outVar)
{
    int pid = getPidByName(processName);

    if (pid == 0) {
        if (waitMode == "normal") {
            outVar = "0";
            return true;
        } else if (waitMode == "force") {
            return false;
        }
        return false;
    }

    // "force" mode: terminate the process
    if (waitMode == "force") {
        QProcess killProc;
        killProc.start("kill", QStringList() << QString::number(pid));
        killProc.waitForFinished();
        outVar = QString::number(killProc.exitCode());
        return killProc.exitCode() == 0;
    }

    // "normal" mode: poll until process exits
    QEventLoop loop;
    QTimer timer;
    bool isExited = false;

    QObject::connect(&timer, &QTimer::timeout, &timer, [&]() {
        // kill -0 checks if process exists without sending a signal
        QProcess checkProc;
        checkProc.start("kill", QStringList() << "-0" << QString::number(pid));
        checkProc.waitForFinished();
        if (checkProc.exitCode() != 0) {
            outVar = "0";
            isExited = true;
            loop.quit();
        }
    });

    timer.start(100);
    loop.exec();
    timer.stop();

    return isExited;
}

#endif
