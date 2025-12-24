#define GLFW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <vector>

#include "myshader.h"
#include "convexhull.h"
#include "fileio.h"

using namespace ImGui;

GLuint vertexArray = 0;
GLuint vertexBuffer = 0;
GLuint program = 0;

float pointColor[4] = { 1.f, 1.f, 1.f, 1.f };
float hullColor[4] = { 1.f, 0.f, 0.f, 0.f };
float bgColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
float pointSize = 8.f;
float lineWidth = 3.f;
float pixelInput[2] = { 0.f, 0.f };

static int pointCountToMake = 100;
static int randomSeed = 12345;
static bool showConvexHull = false;
static bool showPointSettings = true;
static bool showStyleSettings = true;

vector<Point> userPoints;
vector<Point> hullPoints;

void mouseClickCB(GLFWwindow* window, int button, int action, int mods);
void init();
void render(GLFWwindow* window);

void mouseClickCB(GLFWwindow* window, int button, int action, int mods) {
    if (GetIO().WantCaptureMouse) return;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        
        float x = (float)xpos / (width / 2.f) - 1.f;
        float y = 1.f - (float)ypos / (height / 2.f);

        userPoints.push_back({ x, y });
    }
}

int main(void) {
    if (!glfwInit())
        return 0;

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    GLFWwindow* window = glfwCreateWindow(1200, 800, "Convex Hull Test", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }

    glfwMakeContextCurrent(window);

#ifdef _MSC_VER
    glewInit();
#endif

    glfwSetMouseButtonCallback(window, mouseClickCB);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO& io = GetIO();

    io.Fonts->AddFontDefault();
    io.FontGlobalScale = 1.5f;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");

    StyleColorsDark();
    ImGuiStyle& style = GetStyle();
    
    style.WindowRounding = 5.0f;
    style.FrameRounding = 5.0f;
    style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);

    init();

    while (!glfwWindowShouldClose(window)) {
        render(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

using namespace ImGui;

void render(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();

    float screenW = (float)width;
    float screenH = (float)height;

    SetNextWindowPos(ImVec2(0, 0));
    SetNextWindowSize(ImVec2(screenW, 40.0f));
    PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.8f));

    Begin("TopBar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    Text("Convex Hull Tool with OpenGL 4.1 Core");

    SameLine(600);
    if (Button("Import with .csv", ImVec2(180, 25)))
        importPoints("points.csv", userPoints, hullPoints, screenW, screenH);
    SameLine();
    if (Button("Export with .csv", ImVec2(180, 25)))
        exportPoints("points.csv", userPoints, screenW, screenH);

    SameLine(screenW - 150);
    TextDisabled("%zu Points", userPoints.size());
    End();

    PopStyleColor();
    PopStyleVar();

    SetNextWindowPos(ImVec2(screenW - 260, 50));
    SetNextWindowSize(ImVec2(250, 0));

    Begin("Control Panel", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    TextDisabled("Application:\n%.3f ms/frame\n(%.1f FPS)", 1000.0f / GetIO().Framerate, GetIO().Framerate);
        if (CollapsingHeader("Point Management", ImGuiTreeNodeFlags_DefaultOpen)) {

            InputInt("Seed", &randomSeed);
            SliderInt("Count", &pointCountToMake, 1, 100);

            if (Button("Make it!", ImVec2(-1, 30))) {
                userPoints.clear();
                hullPoints.clear();
                srand(randomSeed);
                for (int i = 0; i < pointCountToMake; i++) {
                    float rx = ((float)rand() / RAND_MAX) * 1.6f - 0.8f;
                    float ry = ((float)rand() / RAND_MAX) * 1.6f - 0.8f;
                    userPoints.push_back({ rx, ry });
                }
            }

            if (Button("Erase All", ImVec2(-1, 30))) {
                userPoints.clear();
                hullPoints.clear();
            }
        }

        Spacing();
        Separator();
        Spacing();

        if (CollapsingHeader("Visual Styles", ImGuiTreeNodeFlags_DefaultOpen)) {
            Text("Point Style");
            ColorEdit3("Color##1", pointColor);
            SliderFloat("Size##1", &pointSize, 1.0f, 20.0f);

            Spacing();

            Text("Hull Style");
            ColorEdit3("Color##2", hullColor);
            SliderFloat("Width##2", &lineWidth, 1.0f, 10.0f);

            Spacing();

            Text("Background Style");
            ColorEdit4("Color##3", bgColor);
        }

        Spacing();
        Separator();
        Spacing();

        Text("Add Point By Coord");
        InputFloat2("(X, Y)", pixelInput, "%.0f");
        
        if (Button("Add Point##Pixel", ImVec2(-1, 30))) {
            if (pixelInput[0] >= 0 && pixelInput[0] <= screenW &&
                pixelInput[1] >= 40.0f && pixelInput[1] <= (screenH - 70.0f))
            {
                float ndcX = (pixelInput[0] / screenW) * 2.0f - 1.0f;
                float ndcY = (pixelInput[1] / screenH) * 2.0f - 1.0f;

                // OpenGL은 Y축이 아래에서 위로 증가하지만, 
                // 픽셀 좌표(마우스 등)는 위에서 아래로 증가하는 경우가 많습니다.
                // 만약 Y축이 반전되어 찍힌다면 아래처럼 수정하세요:
                // float ndcY = 1.0f - (pixelInput[1] / screenH) * 2.0f;

                userPoints.push_back({ ndcX, ndcY });
                hullPoints.clear();
            }
            else {
                OpenPopup("Invalid Pixel Range");
            }
        }

        ImVec2 center = ImVec2(screenW * 0.5f, screenH * 0.5f);
        SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (BeginPopupModal("Invalid Pixel Range", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            Text("Input is out of screen bounds!");
            Text("Current Screen: %.0f x %.0f", screenW, screenH);
            Text("Your Input: (%.0f, %.0f)", pixelInput[0], pixelInput[1]);
            Spacing();
            Text("Valid Y Range Excepted By Top/Bottom Bars : 40 ~ %.0f", screenH - 70.f);

            Separator();
            if (Button("OK", ImVec2(120, 0))) {
                CloseCurrentPopup();
            }
            EndPopup();
        }
    End();

    SetNextWindowPos(ImVec2(0, screenH - 70.0f), ImGuiCond_Always);
    SetNextWindowSize(ImVec2(screenW, 70.0f), ImGuiCond_Always);

    PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));

    Begin("Bottom Bar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    if (Button("Get Convex Hull", ImVec2(-1, -1))) {
        hullPoints = getConvexHull(userPoints);
    }
    End();

    PopStyleColor();
    PopStyleVar();

    glUseProgram(program);
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    GLint colorLoc = glGetUniformLocation(program, "outColor");

    float axes[] = { -1, 0, 1, 0, 0, -1, 0, 1 };
    glLineWidth(1.f);
    glUniform4f(colorLoc, 0.5f, 0.5f, 0.5f, 1.0f);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axes), axes, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_LINES, 0, 4);

    if (hullPoints.size() >= 3) {
        glLineWidth(lineWidth);
        glUniform4f(colorLoc, hullColor[0], hullColor[1], hullColor[2], hullColor[3]);
        glBufferData(GL_ARRAY_BUFFER, hullPoints.size() * sizeof(Point), hullPoints.data(), GL_DYNAMIC_DRAW);
        glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)hullPoints.size());
    }

    if (!userPoints.empty()) {
        glPointSize(pointSize);
        glUniform4f(colorLoc, pointColor[0], pointColor[1], pointColor[2], pointColor[3]);
        glBufferData(GL_ARRAY_BUFFER, userPoints.size() * sizeof(Point), userPoints.data(), GL_DYNAMIC_DRAW);
        glDrawArrays(GL_POINTS, 0, (GLsizei)userPoints.size());
    }

    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
    glfwSwapBuffers(window);
}

void init() {
    program = loadShaders("shaders/shader.vs", "shaders/shader.fs");

    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);

    glBindVertexArray(0);
}