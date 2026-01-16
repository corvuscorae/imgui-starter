#include "Application.h"
#include "imgui/imgui.h"
#include "Logger.h"

namespace ClassGame
{
    //
    // our global variables
    //
    bool show_game_panel = true;
    bool show_game_log = true;
    bool show_imgui_demo = false;
    bool show_log_demo = false;

    bool log_to_console = true;
    bool log_to_file = false;

    // Initialize logging system
    Logger &logger = Logger::GetInstance();

    //
    // game starting point
    // this is called by the main render loop in main.cpp
    //
    void GameStartUp()
    {
        logger.Log("Game started successfully");
        logger.Log("Application initialized", logger.INFO, logger.GAME);
    }

    //
    // game render loop
    // this is called by the main render loop in main.cpp
    //
    void RenderGame()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::DockSpaceOverViewport();

        //-- GAME CONTROL WINDOW --//
        ImGui::Begin("Game Control", &show_game_panel, ImGuiWindowFlags_MenuBar);

        ImGui::Text("This is the game control panel");

        // MENU
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("log options"))
            {
                if(ImGui::MenuItem("console", "", &log_to_console)){
                    logger.ToggleConsoleLog(log_to_console);
                }
                if (ImGui::MenuItem("file", "")) { 
                    logger.WriteLogToFile();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // BUTTONS
        if (ImGui::Button("Log Event"))
        {
            logger.Log("This is a test event.", logger.INFO, logger.GAME);
        }
        ImGui::SameLine();
        if (ImGui::Button("Log Game Warn"))
        {
            logger.Log("This is a test game warning.", logger.WARN, logger.GAME);
        }
        ImGui::SameLine();
        if (ImGui::Button("Log Game Error"))
        {
            logger.Log("This is a test game error.", logger.ERROR, logger.GAME);
        }

        // FRAMERATE
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        // TOGGLE WINDOWS
        ImGui::Checkbox("Game Log", &show_game_log);
        ImGui::Checkbox("Demo Window", &show_imgui_demo);      
        ImGui::Checkbox("Imgui Log Demo", &show_log_demo);

        ImGui::End();

         //--- GAME LOG WINDOW ---//
        if(show_game_log){
            ImGui::Begin("Game Log", &show_game_log);

            // BUTTONS
            if (ImGui::Button("Clear"))
            {
                logger.clear(); // ???
            }
            ImGui::SameLine();
            if (ImGui::Button("Test Info"))
            {
                logger.Log("This is test info.");
            }
            ImGui::SameLine();
            if (ImGui::Button("Test Warn"))
            {
                logger.Log("This is a test warning.", logger.WARN);
            }
            ImGui::SameLine();
            if (ImGui::Button("Test Error"))
            {
                logger.Log("This is a test error.", logger.ERROR);
            }

            // PRINT LOG ITEMS
            if(log_to_console){
                for (int i = 0; i < logger.log_size; i++)
                {
                    ImVec4 text_color = logger.get(i).color;
                    ImGui::TextColored(text_color, logger.print(i).c_str());
                }
            }

            ImGui::End();
        }

        //-- DEMO WINDOW --//
        if(show_imgui_demo){
            ImGui::ShowDemoWindow(&show_imgui_demo);
        }

        //-- LOG DEMO WINDOW --//
        if(show_log_demo){
            ImGui::Begin("ImGui Log Demo", &show_log_demo);

            // BUTTONS
            ImGui::LogButtons();

            if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("Hello, world!");
                ImGui::LogFinish();
            }

            if (ImGui::Button("Close Me")){
                show_log_demo = false;
            }
            
            ImGui::End();
        }
    }

    //
    // end turn is called by the game code at the end of each turn
    // this is where we check for a winner
    //
    void EndOfTurn()
    {
    }
}
