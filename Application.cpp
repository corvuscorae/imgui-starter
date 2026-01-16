#include "Application.h"
#include "imgui/imgui.h"
#include <iostream>
#include <vector>
#include <cstring>

namespace ClassGame
{
    //
    // our global variables
    //
    bool show_game_log = true;
    bool show_imgui_demo = false;
    bool show_log_demo = false;

    struct LogItem
    {
        const char *level;
        const char *dat;
        const char *type = NULL;
        ImVec4 color;

        LogItem(const char *_level, const char *_dat, ImVec4 _col)
        {
            level = _level;
            dat = _dat;
            color = _col;
        }

        LogItem(const char *_level, const char *_dat, const char *_type, ImVec4 _col)
        {
            level = _level;
            dat = _dat;
            type = _type;
            color = _col;
        }

        std::string print()
        {
            std::string message = "[" + std::string(level) + "] ";

            if (type)
            {
                message += "[" + std::string(type) + "] ";
            }

            message += dat;

            return message;
        }
    };

    // singleton pattern class for logging
    class Logger
    {
    private:
        Logger() = default;
        std::vector<LogItem> log;

    public:
        int log_size = 0;

        const char *level[3] = {
            "INFO",
            "WARN",
            "ERROR"
        };

        const ImVec4 color[3] = {
            ImVec4(1,1,1,1),
            ImVec4(1,1,0,1),
            ImVec4(1,0,0,1)
        };

        static Logger &GetInstance()
        {
            static Logger instance;

            return instance;
        }

        void LogInfo(const char *message, int lvl = 0)
        {
            // TEMP: test code
            LogItem new_item(level[lvl], message, color[lvl]);
            log.push_back(new_item);

            std::cout << new_item.print() << std::endl;
            log_size++;
        }

        void LogGameEvent(const char *message, int lvl = 0)
        {
            // TEMP: test code
            LogItem new_item(level[lvl], message, "GAME", color[lvl]);
            log.push_back(new_item);

            std::cout << new_item.print() << std::endl;
            log_size++;
        }

        void clear()
        {
            log.clear();
            log_size = 0;
        }

        LogItem get(int i)
        {
            return log.at(i);
        }

        std::string print_last()
        {
            return log.back().print();
        }

        std::string print(int i)
        {
            return log.at(i).print();
        }
    };

    // Initialize logging system
    Logger &logger = Logger::GetInstance();

    //
    // game starting point
    // this is called by the main render loop in main.cpp
    //

    void GameStartUp()
    {
        logger.LogInfo("Game started successfully");
        logger.LogGameEvent("Application initialized");
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
        ImGui::Begin("Game Control");

        ImGui::Text("This is the game control panel");

        // BUTTONS
        if (ImGui::Button("Log Event"))
        {
            logger.LogGameEvent("This is a test event.", 0);
        }
        ImGui::SameLine();
        if (ImGui::Button("Log Game Warn"))
        {
            logger.LogGameEvent("This is a test game warning.", 1);
        }
        ImGui::SameLine();
        if (ImGui::Button("Log Game Error"))
        {
            logger.LogGameEvent("This is a test game error.", 2);
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
                logger.LogInfo("This is test info.", 0);
            }
            ImGui::SameLine();
            if (ImGui::Button("Test Warn"))
            {
                logger.LogInfo("This is a test warning.", 1);
            }
            ImGui::SameLine();
            if (ImGui::Button("Test Error"))
            {
                logger.LogInfo("This is a test error.", 2);
            }

            for (int i = 0; i < logger.log_size; i++)
            {
                ImVec4 text_color = logger.get(i).color;
                ImGui::TextColored(text_color, logger.print(i).c_str());
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
