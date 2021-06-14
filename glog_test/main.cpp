#include <iostream>
#include "glog/logging.h"

int main(int argc, char** argv) {
    google::InitGoogleLogging("glog test main.cpp");
    google::SetLogFilenameExtension("log_");
    //会输出导致程序结束的信号,和google::InstallFailureWriter(&FatalMessageDump); 配合使用，可以在程序出现严重错误时将详细的错误信息打印出来
    google::InstallFailureSignalHandler(); //注册一下即可。默认是打印到stderr中，可以通过InstallFailureWriter更改输出目标。
//     google::InstallFailureWriter(&FatalMessageDump);
    
    google::SetLogDestination(google::INFO, "log/"); // 把日志同时记录文件，最低级别为INFO，此时全部输出

    // 通过GFLAGS来设置参数，更多选项可以在logging.cc里面查询
    // 日志等级分为INFO, WARNING, ERROR, FATAL,如果是FATAL级别这直接运行报错
    FLAGS_stderrthreshold = google::INFO;    //INFO, WARNING, ERROR都输出，若为google::WARNING，则只输出WARNING, ERROR
    //google::SetStderrLogging(google::GLOG_INFO);
    FLAGS_colorlogtostderr = true;  //log为彩色
    //FLAGS_logbufsecs = 0;  // Set log output speed(s)
	//FLAGS_max_log_size = 1024;  // Set max log file size
	//FLAGS_stop_logging_if_full_disk = true;  // If disk is full

    //基本用法：INFO，WAINING，ERROR
    LOG(INFO) << "Hello GLOG";                // << " cookies";
    LOG(WARNING) << "warning test";    // 会输出一个Warning日志
    LOG(ERROR) << "error test";        // 会输出一个Error日志
    LOG(FATAL) << "fatal";   // Logging a FATAL message terminates the program (after the message is logged)!
    // 类似assert的功能
    CHECK(access(argv[2], 0) != -1) << "No such file: "<<argv[2];

    //常见用法1：如果满足一定条件，输出错误log，退出程序
    if(1){
        LOG(ERROR) << "No image files for detection";
    }

    //常见用法2：glog提供VLOG宏来提供自定义打印等级的功能.Verbose
    //可以通过命令行"--v=n",来控制VLOG的输出,VLOG(x),x<=n的情况,VLOG会输出,否则不输出.v默认为0,所以默认情况下VLOG(-1),VLOG(0)能够输出.
    //通常把调试的LOG设为1,这样在默认情况下不输出
    VLOG(-1) << "VLOG(-1) message.";
    VLOG(0) << "VLOG(0) message.";
    VLOG(1) << "VLOG(1) message.";
    VLOG(2) << "VLOG(2) message.";
    VLOG(3) << "VLOG(3) message.";

    //常见用法3：
    // 如果工程为Debug模式,下面信息会输出,如果是release模式,下面信息不会输出.
    DLOG(INFO) << "DLOG:Debug Mode Message!";

    //不常见用法4：条件输出
    LOG_IF(INFO, 89 > 4) << "89 > 4";

    //不常见用法5：频率输出，本质上是通过google::COUNTER这个计数机实现的
    LOG(INFO) << "Found " << google::COUNTER <<std::endl;
    for (int i = 0; i < 4; i++)
    {
        LOG_EVERY_N(ERROR, 5) << "每隔5次输出一次 " << i;
        LOG_FIRST_N(ERROR, 2) << "前两次输出 " << i;
        LOG_IF_EVERY_N(WARNING, 1 < 2, 2) << "条件输出+频率" << google::COUNTER;
    }

    google::ShutdownGoogleLogging();  //关闭log服务
    
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
