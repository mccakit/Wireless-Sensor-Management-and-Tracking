#include "GLFW/glfw3.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "implot.h"
#include "ez_cpp.h"
#include "ez_imgui.h"
#include "ez_serialport.h"
#include "ez_sqlite.h"
#include "ez_time.h"
#include "efes_sensor_gui.h"
int main()
{
    init();

    while (!glfwWindowShouldClose(window))
    {
        begin_frame();

        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
        ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
        ImGui::Begin("Main", nullptr,
                     ImGuiWindowFlags_NoDecoration |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoBringToFrontOnFocus);

        ImGui::BeginTable("Grid", 2);
        ImGui::TableNextColumn();
        draw_sensors();
        ImGui::TableNextColumn();
        draw_sensor_plot();
        ImGui::EndTable();
        ImGui::End();

        render_frame();
    }

    cleanup();

    return 0;
}

