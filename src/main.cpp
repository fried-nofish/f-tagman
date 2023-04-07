#include "app.h"

#include <QApplication>
#include <glog/logging.h>
#include <memory>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    //! setup logger
    google::InitGoogleLogging(argv[0]);
    google::SetLogFilenameExtension(".txt");
    google::SetStderrLogging(google::GLOG_WARNING);
    FLAGS_log_dir = FileTagManager::appLocation(AppPaths::LogInfoLocation);
    FLAGS_alsologtostderr  = true;
    FLAGS_colorlogtostderr = true;

    //! first-start-up initialize
    auto w = std::make_unique<FileTagManager>();
    w->checkOrInitialize();

    //! TODO: initialize local data

    w->show();
    return app.exec();
}
