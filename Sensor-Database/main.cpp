#include <SQLiteCpp/SQLiteCpp.h>
#include "ez_sqlite.h"
#include "ez_time.h"
#include "ez_random.h"
#include <cpr/cpr.h>
#include <thread>
#include <string>

std::string clean_number(const std::string& value) {
    std::string clean;
    for (char c : value) {
        if (isdigit(c) || c == '.') {
            clean += c;
        }
    }
    return clean;
}
[[noreturn]] int main()
{
    const SQLite::Database db("../../Database/efes_sensor_data.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    execute_query(db,
                  "create table if not exists sensor_info ("
                  "    sensor_id integer primary key autoincrement, "
                  "    sensor_name varchar(255),"
                  "    sensor_ip varchar(255) unique"
                  ");"
    );

    execute_query(db,
                  "create table if not exists sensor_reports ("
                  "    sensor_id integer, "
                  "    report_datetime text, "
                  "    sensor_temp float, "
                  "    primary key (sensor_id, report_datetime), "
                  "    foreign key (sensor_id) references sensor_info(sensor_id)"
                  ");"
    );
    try
    {
        execute_query(db, "PRAGMA journal_mode=WAL;");
    } catch (...)
    {
    }
    std::vector<std::string> sensor_id_list {};
    std::vector<std::string> sensor_ip_list {};
    auto now{std::chrono::system_clock::now()};
    auto last_update{now};
    std::string current_datetime{};
    while (true)
    {
        now = std::chrono::system_clock::now();
        if (now - last_update > std::chrono::seconds(5))
        {
            last_update = now;
            execute_query(db, "select sensor_id,sensor_ip from sensor_info");
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            sensor_id_list.clear();
            sensor_ip_list.clear();
            for (const auto& row: result.val)
            {
                sensor_id_list.push_back(row[0]);
                sensor_ip_list.push_back("http://" + row[1] +"/");
            }
        }
        current_datetime = get_current_datetime();
        for (int i {0}; i < sensor_id_list.size(); ++i)
        {
            cpr::Response r = cpr::Get(cpr::Url{sensor_ip_list[i]});
            execute_query(db, "insert into sensor_reports (sensor_id, report_datetime, sensor_temp)"
                              " values (" + sensor_id_list[i] + ", '" + current_datetime + "', " + clean_number(r.text) + ");"
            );
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

