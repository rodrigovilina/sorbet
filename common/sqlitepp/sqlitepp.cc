#include "sqlitepp.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"

namespace sorbet::sqlitepp {

std::string SqliteTable::generateCreateStmt(const std::string name, const SqliteSchema schema) {
    return absl::StrCat("CREATE TABLE ", name, schema.toString(), ";");
}

void SqliteDb::generateInsertStmt(SqliteTable &table) {
    std::string qmarks = "(";
    for (int i = 0; i < table.schema.columns.size() - 1; i++) {
        absl::StrAppend(&qmarks, "?,");
    }
    absl::StrAppend(&qmarks, "?)");
    auto query =
        absl::StrCat("INSERT INTO ", table.tableName, " ", table.schema.toStringOnlyNames(), " VALUES ", qmarks, ";");
    std::fprintf(stdout, "%s\n", query.c_str());
    if (sqlite3_prepare_v2(db, query.c_str(), query.length() + 1, &table.insertStmt, NULL) != SQLITE_OK) {
        std::fprintf(stdout, "ERROR PREPARING STATEMENT\n");
    }
}

void SqliteDb::create(const SqliteTable table) {
    simpleExec(table.createStmt);
}

void SqliteDb::insert(SqliteTable &table, const std::vector<std::variant<int, double, std::string>> &values) {
    for (int i = 0; i < table.schema.columns.size(); i++) {
        auto colType = table.schema.columns[i].dataType;
        auto value = values[i];
        switch (colType) {
            case Integer:
                sqlite3_bind_int(table.insertStmt, i + 1, std::get<int>(value));
                break;
            case Real:
                sqlite3_bind_double(table.insertStmt, i + 1, std::get<double>(value));
                break;
            case Text:
                sqlite3_bind_text(table.insertStmt, i + 1, std::get<std::string>(value).c_str(),
                                  std::get<std::string>(value).length(), SQLITE_STATIC);
                break;
            case Blob:
            case Null:
                break;
        }
    }

    if (auto rc = sqlite3_step(table.insertStmt) != SQLITE_DONE) {
        std::fprintf(stdout, "ERROR EXECUTING INSERT %d\n", rc);
    } else {
        std::fprintf(stdout, "INSERT SUCCESS %d\n", rc);
    }
    if (auto rc = sqlite3_reset(table.insertStmt) != SQLITE_OK) {
        std::fprintf(stdout, "ERROR EXECUTING RESET %d\n", rc);
    }
    if (auto rc = sqlite3_clear_bindings(table.insertStmt) != SQLITE_OK) {
        std::fprintf(stdout, "ERROR EXECUTING CLEAR_BINDINGS %d\n", rc);
    }
}
void SqliteDb::simpleExec(const std::string &query) {
    char *errMsg;
    auto rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }
}

} // namespace sorbet::sqlitepp
