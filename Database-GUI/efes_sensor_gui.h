#pragma once
#include "ez_imgui.h"

static str selected_sensor{"1"};
static const SQLite::Database db("../../Database/efes_sensor_data.db",
                                 SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
inline void draw_sensors()
{
    static bool sensors_drawn{false};
    static arr<arr<str> > sensor_list{};
    static char filter_buf[32];
    ImGui::Text("Sensors");
    ImGui::Separator();
    if (!sensors_drawn)
    {
        execute_query(db, "select sensor_id, sensor_name from sensor_info");
        sensor_list = query_result.val;
        sensors_drawn = true;
    }
    for (int row{0}; row < sensor_list.size(); ++row)
    {
        if (sensor_list[row][1].find(filter_buf))
        {
            continue;
        }
        if (ImGui::Selectable(sensor_list[row][1].c_str(), sensor_list[row][0] == selected_sensor))
        {
            selected_sensor = sensor_list[row][0];
        }
    }
    ImGui::Separator();
    ImGui::Text("Sensor ID:");
    ImGui::SameLine();
    ImGui::Text(selected_sensor.c_str());
    ImGui::Text("Filter:");
    ImGui::SameLine();
    ImGui::InputText("###", filter_buf, 32);

    if (ImGui::Button("Add Sensor"))
    {
        ImGui::OpenPopup("Add Sensor");
    }
    ImGui::SameLine();
    if (ImGui::Button("Remove Sensor"))
    {
        ImGui::OpenPopup("Remove Sensor");
    }
    ImGui::SameLine();
    if (ImGui::Button("Refresh"))
    {
        execute_query(db, "select sensor_id, sensor_name from sensor_info");
        sensor_list = query_result.val;
        sensors_drawn = false;
    }
    if (ImGui::BeginPopupModal("Add Sensor", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        static char sensor_name[32];
        static char sensor_ip[32];
        ImGui::Text("Add a New Sensor!");
        ImGui::Text("Name: ");
        ImGui::SameLine();
        ImGui::InputText("###name", sensor_name, 32);
        ImGui::Text("IP: ");
        ImGui::SameLine();
        ImGui::InputText("###ip", sensor_ip, 32);
        if (ImGui::Button("Save"))
        {
            execute_query(db, "insert into sensor_info (sensor_ip, sensor_name) values ('" + str(sensor_ip) + "', '" + str(sensor_name) + "')");
            ImGui::CloseCurrentPopup();
        }
        if (ImGui::Button("Exit"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    if (ImGui::BeginPopupModal("Remove Sensor", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Are you sure?");
        if (ImGui::Button("Yes"))
        {
            execute_query(db, "delete from sensor_info where sensor_id = " + selected_sensor + "");
            execute_query(db, "delete from sensor_reports where sensor_id = " + selected_sensor + "");
            execute_query(db, "delete from sqlite_sequence where name = 'sensor_info' ;");
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("No"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

inline void draw_sensor_plot()
{
    static int selected_plot{0};
    static int previous_plot{selected_plot};
    ImGui::RadioButton("Seconds", &selected_plot, 1);
    ImGui::SameLine();
    ImGui::RadioButton("Minutes", &selected_plot, 2);
    ImGui::SameLine();
    ImGui::RadioButton("Hours", &selected_plot, 3);
    ImGui::SameLine();
    ImGui::RadioButton("Days", &selected_plot, 4);
    if (selected_plot != previous_plot)
    {
        previous_plot = selected_plot;
    }
    ImGui::Separator();
    static arr<flt> x_val{};
    static arr<flt> y_val{};
    static auto now = std::chrono::system_clock::now();
    now = std::chrono::system_clock::now();
    static auto last_update{now};
    if (selected_plot == 1)
    {
        static arr<flt> x_ticks  {};
        static arr<const char*>  x_labels {};
        static const int label_interval{20};
        if (now - last_update > std::chrono::seconds(1))
        {
            last_update = now;
            x_val.clear();
            y_val.clear();
            x_ticks.clear();
            x_labels.clear();
            execute_query(
                db, "with descending_seconds as "
                    "(select report_datetime, sensor_temp from sensor_reports where sensor_id = " + selected_sensor +
                    " order by report_datetime desc limit 60)"
                    " select strftime('%M:%S', report_datetime), sensor_temp from descending_seconds "
                    "order by report_datetime asc;");
            for (int row{0}; row < query_result.val.size(); ++row)
            {
                x_val.push_back(row);
                y_val.push_back(cast<flt>(query_result.val[row][1]));
                if (row%label_interval == 5)
                {
                    x_ticks.push_back(cast<flt>(row));
                    x_labels.push_back(query_result.val[row][0].data());
                }
            }
        }
        if (ImPlot::BeginPlot("Seconds"))
        {
            ImPlot::SetupAxisLimits(ImAxis_X1, 0, 60, ImGuiCond_Always);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 100, ImGuiCond_Always);
            ImPlot::SetupAxisTicks(ImAxis_X1, x_ticks.data(), x_ticks.size(), x_labels.data());
            ImPlot::PlotLine("Temperature", x_val.data(), y_val.data(), x_val.size());
            ImPlot::EndPlot();
        }
    }
    if (selected_plot == 2)
    {
        static arr<flt> x_ticks  {};
        static arr<const char*>  x_labels {};
        static const int label_interval{10};
        if (now - last_update > std::chrono::seconds(1))
        {
            last_update = now;
            x_val.clear();
            y_val.clear();
            x_ticks.clear();
            x_labels.clear();
            execute_query(
                db, "with descending_minutes as "
                    "(select report_datetime, sensor_temp from sensor_reports where sensor_id = " + selected_sensor +
                    " group by strftime('%M', report_datetime)"
                    " order by report_datetime desc limit 60)"
                    " select strftime('%M:%S', report_datetime) as minutes, sensor_temp from descending_minutes "
                    "order by report_datetime asc;");
            for (int row{0}; row < query_result.val.size(); ++row)
            {
                x_val.push_back(row);
                y_val.push_back(cast<flt>(query_result.val[row][1]));
                if (row%label_interval == 5)
                {
                    x_ticks.push_back(cast<flt>(row));
                    x_labels.push_back(query_result.val[row][0].data());
                }
            }
        }
        if (ImPlot::BeginPlot("Minutes"))
        {
            ImPlot::SetupAxisLimits(ImAxis_X1, 0, 60, ImGuiCond_Always);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 100, ImGuiCond_Always);
            ImPlot::SetupAxisTicks(ImAxis_X1, x_ticks.data(), x_ticks.size(), x_labels.data());
            ImPlot::PlotLine("Temperature", x_val.data(), y_val.data(), x_val.size());
            ImPlot::EndPlot();
        }
    }
    if (selected_plot == 3)
    {
        static arr<flt> x_ticks  {};
        static arr<const char*>  x_labels {};
        static const int label_interval{10};
        if (now - last_update > std::chrono::seconds(1))
        {
            last_update = now;
            x_val.clear();
            y_val.clear();
            x_ticks.clear();
            x_labels.clear();
            execute_query(
                db, "with descending_hours as "
                    "(select report_datetime, sensor_temp from sensor_reports where sensor_id = " + selected_sensor +
                    " group by strftime('%H', report_datetime)"
                    " order by report_datetime desc limit 60)"
                    " select strftime('%H:%M', report_datetime), sensor_temp from descending_hours "
                    "order by report_datetime asc;");
            for (int row{0}; row < query_result.val.size(); ++row)
            {
                x_val.push_back(row);
                y_val.push_back(cast<flt>(query_result.val[row][1]));
                if (row%label_interval == 5)
                {
                    x_ticks.push_back(cast<flt>(row));
                    x_labels.push_back(query_result.val[row][0].data());
                }
            }
        }
        if (ImPlot::BeginPlot("Hours"))
        {
            ImPlot::SetupAxisLimits(ImAxis_X1, 0, 24, ImGuiCond_Always);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 100, ImGuiCond_Always);
            ImPlot::SetupAxisTicks(ImAxis_X1, x_ticks.data(), x_ticks.size(), x_labels.data());
            ImPlot::PlotLine("Temperature", x_val.data(), y_val.data(), x_val.size());
            ImPlot::EndPlot();
        }
    }
    if (selected_plot == 4)
    {
        static arr<flt> x_ticks  {};
        static arr<const char*>  x_labels {};
        static const int label_interval{10};
        if (now - last_update > std::chrono::seconds(1))
        {
            last_update = now;
            x_val.clear();
            y_val.clear();
            x_ticks.clear();
            x_labels.clear();
            execute_query(
                db, "with descending_days as "
                    "(select report_datetime, sensor_temp from sensor_reports where sensor_id = " + selected_sensor +
                    " group by strftime('%D', report_datetime)"
                    " order by report_datetime desc limit 60)"
                    " select strftime('%D', report_datetime), sensor_temp from descending_days "
                    "order by report_datetime asc;");
            for (int row{0}; row < query_result.val.size(); ++row)
            {
                x_val.push_back(row);
                y_val.push_back(cast<flt>(query_result.val[row][1]));
                if (row%label_interval == 5)
                {
                    x_ticks.push_back(cast<flt>(row));
                    x_labels.push_back(query_result.val[row][0].data());
                }
            }
        }
        if (ImPlot::BeginPlot("Days"))
        {
            ImPlot::SetupAxisLimits(ImAxis_X1, 0, 30, ImGuiCond_Always);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 100, ImGuiCond_Always);
            ImPlot::SetupAxisTicks(ImAxis_X1, x_ticks.data(), x_ticks.size(), x_labels.data());
            ImPlot::PlotLine("Temperature", x_val.data(), y_val.data(), x_val.size());
            ImPlot::EndPlot();
        }
    }



}