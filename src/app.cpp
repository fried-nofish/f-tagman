#include "app.h"
#include "tagdb.h"

#include <QApplication>
#include <QStandardPaths>
#include <QLayout>
#include <QListWidget>
#include <QLineEdit>
#include <glog/logging.h>
#include <filesystem>

namespace fs = std::filesystem;

struct FileTagManagerPrivate {
    std::unique_ptr<TagDB> db;
};

FileTagManager::FileTagManager(QWidget *parent)
    : QWidget(parent)
    , d(std::make_unique<FileTagManagerPrivate>()) {}

FileTagManager::~FileTagManager() = default;

void FileTagManager::checkOrInitialize() noexcept {
    const auto appDataHome = appLocation(AppPaths::AppDataRootLocation);

    auto ok = true;

    //! NOTE: as long as the AppData directory exists, the application is
    //! considered to have been initialized. if you make changes to the relevant
    //! directories and files manually, the application may crash.
    if (fs::exists(appDataHome)) {
        LOG(INFO) << "initialization already done";
    } else {
        ok &= fs::create_directories(appDataHome);
        ok &= fs::create_directories(appLocation(AppPaths::ConfigDataLocation));
        ok &= fs::create_directories(appLocation(AppPaths::LogInfoLocation));

        LOG(INFO) << "create directories for AppData storage";
        LOG_IF(ERROR, !ok) << "directories creation failed";
    }

    if (ok) { d->db = std::make_unique<TagDB>(appDataHome + "/tag.db"); }
}

std::string FileTagManager::appLocation(AppPaths path) {
    const auto root =
        QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);

    auto utf8Bytes = root.toUtf8();
    auto rootPath  = fs::path(reinterpret_cast<char8_t *>(utf8Bytes.data()));

    switch (path) {
        case AppPaths::AppDataRootLocation: {
            return rootPath.generic_string();
        } break;
        case AppPaths::ConfigDataLocation: {
            rootPath.concat(u8"/Data");
            return rootPath.generic_string();
        } break;
        case AppPaths::LogInfoLocation: {
            rootPath.concat(u8"/Data/Log");
            return rootPath.generic_string();
        } break;
        default: {
        } break;
    }
}
