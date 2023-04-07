#pragma once

#include <QWidget>
#include <memory>

struct FileTagManagerPrivate;

enum class AppPaths {
    AppDataRootLocation,
    ConfigDataLocation,
    LogInfoLocation,
};

class FileTagManager : public QWidget {
public:
    explicit FileTagManager(QWidget* parent = nullptr);
    virtual ~FileTagManager() override;

    void checkOrInitialize() noexcept;

public:
    static std::string appLocation(AppPaths path);

private:
    std::unique_ptr<FileTagManagerPrivate> d;
};
