#include "systemdetection.h"

#ifdef Q_OS_WIN

#include <windows.h>
#include<cstdlib>
#include<cstring>
#include <regex>
#include <fstream>
#include <filesystem>
#include "QProcess"
#include "QCoreApplication"
#include "QFile"
#include "QThread"
std::string  runCMD(const std::string & command){
    // 管道句柄
    HANDLE hReadPipe, hWritePipe;
    SECURITY_ATTRIBUTES sa;

    // 设置安全属性
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE; // 允许子进程继承管道
    sa.lpSecurityDescriptor = NULL;

    // 创建管道
    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
        std::cerr << "Failed to create pipe." << std::endl;
        Logger::instance().log("Error:\nFailed to create pipe.");
        return "";
    }

    // 设置启动信息
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW; // 使用标准句柄和显示窗口
    si.wShowWindow = SW_HIDE; // 隐藏窗口
    si.hStdOutput = hWritePipe; // 将标准输出重定向到写入端
    si.hStdError = hWritePipe;  // 可选：将标准错误也重定向到写入端

    // 创建子进程
    if (CreateProcessA(
            NULL,                            // 使用应用程序的路径
            const_cast<LPSTR>(command.c_str()), // 命令行参数
            NULL,                            // 进程的安全属性
            NULL,                            // 线程的安全属性
            TRUE,                            // 继承标志
            0,                               // 创建标志
            NULL,                            // 使用父进程的环境
            NULL,                            // 使用父进程的当前目录
            &si,                             // 指向启动信息结构的指针
            &pi                              // 指向进程信息结构的指针
    )) {

        // 关闭写入端，不再使用
        CloseHandle(hWritePipe);

        // 读取输出
        std::string output;
        char buffer[4096];
        DWORD bytesRead;

        while (ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
            buffer[bytesRead] = '\0'; // 以空字符结尾
            output += buffer; // 添加到输出字符串
        }

        // 等待进程结束
        WaitForSingleObject(pi.hProcess, INFINITE);

        // 关闭句柄
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        CloseHandle(hReadPipe);

        return output; // 返回输出字符串
    } else {
        std::cerr << "Failed to execute command: " << GetLastError() << std::endl;
        CloseHandle(hWritePipe);
        CloseHandle(hReadPipe);
        return "";
    }
}


QString readFilteredTextFile(const QString &filePath, const QString &filter) {
    QString result;  // 用于存储结果的 QString
    QFile file(filePath);  // 创建 QFile 对象

    // 打开文件
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
        return result;  // 返回空字符串
    }

    QTextStream in(&file);  // 创建 QTextStream 用于读取文件

    // 逐行读取文件
    while (!in.atEnd()) {
        QString line = in.readLine();  // 读取一行

        // 如果行中包含过滤字符串，则跳过
        if (line.contains(filter)) {
            continue;
        }

        // 将有效行添加到结果中
        result += line + "\n";  // 使用换行符分隔行
    }

    file.close();  // 关闭文件
    return result;  // 返回结果
}

std::string runPowerShellCommand(const std::string file) {
    QString dir = QCoreApplication::applicationDirPath();
    // PowerShell 命令
    QString command = R"(Start-Process cmd.exe -ArgumentList '/c  )"+ dir+"/windebugger/cdb.exe -z " + QString::fromStdString(file) +  R"( -c "!analyze -v;q" > )" + dir+ R"(/output.txt 2>&1' -Verb RunAs)";

    qDebug()<<command;
    // 创建 QProcess 对象
    QProcess process;

    // 设置 PowerShell 路径
    QString powershellPath = "C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe";

    // 启动 PowerShell 进程
    process.start(powershellPath, QStringList() << "-Command" << command);

    // 等待进程完成
    if (!process.waitForFinished()) {
        qDebug() << "Process failed to finish:" << process.errorString();
        return "";
    }
    QThread::sleep(2); // 等待2秒
    QString filePath = dir+"/output.txt";  // 你的文件路径
    QString filter = "**";  // 需要跳过的字符串

    // 读取过滤后的文件内容
    QString filteredContent = readFilteredTextFile(filePath, filter);

    Logger::instance().log(filteredContent);

    QFile file1(filePath);  // 创建 QFile 对象

    // 检查文件是否存在
    if (file1.exists()) {
        // 尝试删除文件
        if (file1.remove()) {
            qDebug() << "File deleted successfully:" << filePath;
        } else {
            qDebug() << "Failed to delete file:" << file1.errorString();
        }
    } else {
        qDebug() << "File does not exist:" << filePath;
    }

    return filteredContent.toStdString();
}

std::string runCDBProcessWithOutput(const std::string file) {
    std::string output;
    // 创建用于捕获输出的管道
    HANDLE hRead, hWrite;
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE }; // 允许继承句柄
    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
        Logger::instance().log("Error:\n Failed to create pipe for output redirection.");
        std::cerr << "Failed to create pipe for output redirection." << std::endl;
        return "";
    }

    // 初始化 STARTUPINFO 结构体，设置标准输出到管道
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;  // 使用 SW_HIDE 标志
    si.hStdOutput = hWrite;
    si.hStdError = hWrite; // 将错误输出也重定向到管道
    ZeroMemory(&pi, sizeof(pi));

    // 定义 CDB 命令
    const std::string cdbCommand = "windebugger\\cdb.exe -z " +file + "  -c \"!analyze -v; q\"";

    // CreateProcess 的参数必须是可写的
    char commandBuffer[1024];
    strcpy_s(commandBuffer, sizeof(commandBuffer), cdbCommand.data());

    // 创建进程
    if (!CreateProcessA(NULL, commandBuffer, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "CreateProcess failed with error: " << GetLastError() << std::endl;
        return "";
    }

    // 关闭写入端句柄，防止死锁
    CloseHandle(hWrite);

    // 读取管道中的输出
    char buffer[4096];
    DWORD bytesRead;
    while (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0'; // null-terminate the string
        output += buffer; // 输出到控制台
    }

    // 等待进程结束
    WaitForSingleObject(pi.hProcess, INFINITE);

    // 获取并打印进程的退出代码
    DWORD exitCode;
    if (GetExitCodeProcess(pi.hProcess, &exitCode)) {
        std::cout << "CDB process exited with code: " << exitCode << std::endl;
    } else {
        std::cerr << "Failed to get exit code. Error: " << GetLastError() << std::endl;
    }

    // 关闭句柄
    CloseHandle(hRead);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return output;
}

std::vector<std::string> split(const std::string& input,
                               const std::string& regex)
{

    std::regex re(regex);
    std::sregex_token_iterator first {input.begin(), input.end(), re, -1}, last;
    return {first, last};
}

std::string trim(std::string & s){
    if(s.empty())
        return s;
    s.erase(0,s.find_first_not_of(' '));
    s.erase(0,s.find_first_not_of('\t'));
    s.erase(s.find_last_not_of(' ')+1);
    s.erase(s.find_last_not_of('\t')+1);
    return s;
}

// 获取指定目录下的所有文件名
std::vector<std::string> getFilesInDirectory(const std::string& directoryPath) {
    std::vector<std::string> files;

    // 构造搜索路径，搜索目录下的所有文件
    std::string searchPath = directoryPath + "\\*";

    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to find files in directory: " << directoryPath << std::endl;
        return files;
    }

    // 循环查找目录中的文件
    do {
        const std::string fileName =findFileData.cFileName;
        // 排除 "." 和 ".." 目录
        if (fileName != "." && fileName != "..") {
            files.push_back( directoryPath + "\\" +fileName);
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    // 关闭搜索句柄
    FindClose(hFind);

    return files;
}

SystemDetection::SystemDetection() {

}

void SystemDetection::storageDriverVersion() {
    int argn = 4;
    std::string deviceidList = runCMD("wmic path  Win32_PnPEntity get deviceid");
//    std::cout << deviceidList;

    if (deviceidList.empty()) {
        std::cerr << R"(wmic command run error)";
        return;
    }
    deviceIdVec.clear();
    std::vector<std::string> vec = split(deviceidList, "\r\r\n");
    for (std::string &str: vec) {
        trim(str);
        deviceIdVec.push_back(str);
    }

    std::string driverDataList = runCMD(
            "wmic path  Win32_PnPSignedDriver get deviceid,devicename,driverversion,driverdate");
    std::cout<<driverDataList;
    driverDataVec.clear();
    std::vector<std::string> vec1 = split(driverDataList, "\r\r\n");
    for (std::string &str: vec1) {
        trim(str);
        if(str.empty())
            continue;
        std::vector<std::string> t_result = split(str,"\\s{2,}");
        if (t_result.size() != argn) {
            errorVec.push_back(str);
        } else {
            driverDataVec.push_back(t_result);
        }
    }
}

std::vector<std::string> SystemDetection::scanApplicationData()
{
    std::string output = runCMD("wevtutil qe Application /q:\"*[System[(Level=2)]]\" /f:text");
//    Logger::instance().log(output);
//    std::cout<<output;
    std::vector<std::string> eventVec = split(output,"Event\\[");
    // readWindowsLogs();

    return eventVec;
}

std::vector<std::string> SystemDetection::scanSystemData()
{
    std::string output = runCMD("wevtutil qe System /q:\"*[System[(Level=2)]]\" /f:text");
//    Logger::instance().log(output);
//    std::cout<<output;
    std::vector<std::string> eventVec = split(output,"Event\\[");
    // readWindowsLogs();

    return eventVec;
}

int SystemDetection::getDriverData()
{
//    auto wbeClass = WbemmuidQuery::getPtr();
    // qDebug() << "BIOS Information:";
    // wbeClass->query("SELECT * FROM Win32_BIOS");

    // qDebug() << "\nOperating System Version:";
    // wbeClass->query("SELECT * FROM Win32_OperatingSystem");

    // qDebug() << "\nProcessor Information:";
    // wbeClass->query("SELECT * FROM Win32_Processor");

    // qDebug() << "\nBaseBoard Information:";
    // wbeClass->query("SELECT * FROM Win32_BaseBoard");

    // qDebug() << "\nMemory Information:";
    // wbeClass->query("SELECT * FROM Win32_PhysicalMemory");

    // qDebug() << "\nDisk Information:";
    // wbeClass->query("SELECT * FROM Win32_DiskDrive");

    // qDebug() << "\nVideo Controller Information:";
    // wbeClass->query("SELECT * FROM Win32_VideoController");

    // qDebug() << "\nSound Device Information:";
    // wbeClass->query("SELECT * FROM Win32_SoundDevice");

    // qDebug() << "\nNetwork Adapter Information:";
    // wbeClass->query("SELECT * FROM Win32_NetworkAdapter");
//    wbeClass->query("SELECT * FROM Win32_PnPEntity WHERE PNPClass = 'softwareComponent'");
//
//    QProcess process;
    // process.start("cmd.exe", QStringList() << "/c" << "dir");
    // process.start("powershell.exe",QStringList()<<"/c"<<"Get-WmiObject -Class CIM_PCVideoController");//显卡
    // process.start("powershell.exe",QStringList()<<"/c"<<"Get-WmiObject -Class CIM_PCVideoController| Select-Object -Property Name,AdapterRAM");//显卡内存
    // process.start("powershell.exe",QStringList()<<"/c"<<"Get-CimInstance -ClassName Win32_BIOS");//bios
    // process.start("powershell.exe",QStringList()<<"/c"<<"Get-CimInstance -ClassName Win32_Processor");//cpu
    // process.start("powershell.exe",QStringList()<<"/c"<<"Get-CimInstance -ClassName Win32_BaseBoard");//主板
    // process.start("powershell.exe",QStringList()<<"/c"<<"Get-CimInstance -ClassName Win32_PhysicalMemory");//物理内存
    // process.start("powershell.exe",QStringList()<<"/c"<<"Get-WmiObject -ClassName Win32_DiskDrive");//硬盘驱动
    // process.start("powershell.exe",QStringList()<<"/c"<<"Get-WmiObject -ClassName Win32_SoundDevice");//音频
    // process.start("powershell.exe",QStringList()<<"/c"<<"Get-WmiObject -ClassName Win32_NetworkAdapter");//网络

    std::cout<<runCMD("wmic path win32_videocontroller get name,driverversion,AdapterCompatibility");//显卡
    std::cout<<runCMD("wmic path Win32_SoundDevice get name");//声卡
    std::cout<<runCMD("wmic path Win32_BaseBoard get name");//主板
    std::cout<<runCMD("wmic path Win32_NetworkAdapter get name");//网卡
    std::cout<<runCMD("wmic path Win32_Processor get name");//cpu
    return 0;
}

int SystemDetection::getDumpData(const std::string& file) {
    std::string errList = runCDBProcessWithOutput(file);
    if(errList.empty())
        return 1;
//    std::cout<<errList;
    Logger::instance().log(errList);
    std::vector<std::string> vec = split(errList, "\\n+");
    if(lanpingMap.find(file) != lanpingMap.end()){
//        std::cout<<"已读取"<<file;
        Logger::instance().log(file);
        return 0;
    }
    std::map<std::string,std::string> dataM;
    for(std::string & str:vec){
        auto vec1 = split(str,":");
        if(vec1.size()!=2)
            continue;
        dataM.insert(std::make_pair(trim(vec1[0]),trim(vec1[1])));
    }

    lanpingMap.insert(std::make_pair(file,dataM));
    return 0;
}

void SystemDetection::scanMiniDump() {
    auto vec = getFilesInDirectory("C:\\Windows\\Minidump");
    for(auto str:vec){
        getDumpData(str);
    }
}

std::map<std::string, std::map<std::string, std::string >> SystemDetection::getLanpingMap() {
    return lanpingMap;
}

void SystemDetection::deleteSystemData() {
    runCMD("wevtutil cl System");
}

void SystemDetection::deleteApplicationData() {
    runCMD("wevtutil cl Application");
}

#else // Q_OS_WIN

// Stub implementations for non-Windows platforms

SystemDetection::SystemDetection() {}

void SystemDetection::storageDriverVersion() {
    std::cerr << "storageDriverVersion not supported on this platform" << std::endl;
}

std::vector<std::string> SystemDetection::scanApplicationData() {
    return {};
}

std::vector<std::string> SystemDetection::scanSystemData() {
    return {};
}

int SystemDetection::getDriverData() {
    return 0;
}

void SystemDetection::scanMiniDump() {}

std::map<std::string, std::map<std::string, std::string>> SystemDetection::getLanpingMap() {
    return {};
}

void SystemDetection::deleteSystemData() {}

void SystemDetection::deleteApplicationData() {}

std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
    return {};
}

std::string runCMD(const std::string &cmd) {
    return "";
}

#endif
