#include "tagdb.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <glog/logging.h>
#include <array>
#include <string_view>
#include <filesystem>

namespace fs = std::filesystem;

struct TagDBPrivate {
    QSqlDatabase db;
    bool         avalaible{false};

    TagDBPrivate()
        : db{QSqlDatabase::addDatabase("QSQLITE")} {}
};

TagDB::TagDB(std::string_view target)
    : d(std::make_unique<TagDBPrivate>()) {
    const auto dbPath   = QString::fromStdString(std::string{target});
    const auto needInit = !fs::exists(target);

    d->db.setDatabaseName(dbPath);

    if (!d->db.isValid()) {
        LOG(ERROR) << "driver for tag database '"
                   << d->db.driverName().toStdString() << "' is not available";
        return;
    }

    d->db.open();
    if (d->db.isOpenError()) {
        LOG(ERROR) << "failed opening tag database: "
                   << d->db.lastError().text().toStdString();
        return;
    }

    LOG(INFO) << "tag database opened";

    if (!needInit) {
        d->avalaible = true;
        return;
    }

    const auto initialized = initialize();

    d->avalaible = initialized;
}

TagDB::~TagDB() {
    LOG(INFO) << "shutdown tag database";

    d->db.close();

    LOG_IF(WARNING, d->db.isOpen()) << "cannot close tag database: "
                                    << d->db.lastError().text().toStdString();

    LOG(INFO) << "application quited";
}

bool TagDB::avalaible() const {
    return d->avalaible;
}

bool TagDB::initialize() {
    std::array<QString, 2> queryList{
        R"(
		CREATE TABLE TAG_INFO (
			hash INTEGER PRIMARY KEY,
			tag VARCHAR(32) NOT NULL,
			base INTEGER,
			note TEXT
		);)",
        R"(
		CREATE TABLE RESOURCE_INDEX (
			url	VARCHAR(256) NOT NULL,
			digest CHAR(40),
			tag_list TEXT
		);)"};

    QSqlQuery sql;

    for (const auto& query : queryList) {
        sql.prepare(query);
        if (!sql.exec()) {
            LOG(ERROR) << "cannot initialize tag database: "
                       << sql.lastError().text().toStdString();
            return false;
        }
    }

    return true;
}
