// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include <chrono>

#include "game_context.h"
#include "pattern.h"

const char* vertex_shader_source = R"(
        #version 460 core
        layout(location = 0) in vec3 pos;
        void main() {
            gl_Position = vec4(pos, 1.0);
        }
    )";

const char* fragment_shader_source = R"(
        #version 460 core
        out vec4 frag_color;

        layout(std430, binding = 0) buffer GridData {
            uint grid_data[];
        };

        const unsigned int width_grid_count = 1920 / 20;
        const unsigned int height_grid_count = 1080 / 20;

        unsigned int grid_x = uint(gl_FragCoord.x) / 20;
        unsigned int grid_y = uint(gl_FragCoord.y) / 20;

        unsigned int mod_x = uint(gl_FragCoord.x) % 20;
        unsigned int mod_y = uint(gl_FragCoord.y) % 20;

        void main() {
            if (mod_x == 0 || mod_y == 0 || grid_data[grid_y * width_grid_count + grid_x] == 1) {
                frag_color = vec4(0.0, 0.0, 0.0, 1.0);
            } else {
                frag_color = vec4(1.0, 1.0, 1.0, 1.0);
            }
        }
    )";

static void glfw_error_callback(int error, const char* description) {
  std::cerr << "GLFW Error %d: %s\n" << error << description;
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
  if (!ImGui::GetIO().WantCaptureMouse) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
      context.SetCellState((int)xpos / 20,
                           (int)(window_height - ypos - 20) / 20, true);
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) ==
               GLFW_PRESS) {
      context.SetCellState((int)xpos / 20,
                           (int)(window_height - ypos - 20) / 20, false);
    }
  }
}

static void GLAPIENTRY opengl_debug_callback(GLenum source, GLenum type,
                                             GLuint id, GLenum severity,
                                             GLsizei length,
                                             const GLchar* message,
                                             const void* user_param) {
  if (severity == GL_DEBUG_SEVERITY_HIGH) {
    std::cerr << "Severity: HIGH" << std::endl;
    std::cerr << "OpenGL Debug Message (" << id << "): " << message
              << std::endl;
  } else if (severity == GL_DEBUG_SEVERITY_MEDIUM) {
    std::cerr << "Severity: MEDIUM" << std::endl;
    std::cerr << "OpenGL Debug Message (" << id << "): " << message
              << std::endl;
  } else if (severity == GL_DEBUG_SEVERITY_LOW) {
    std::cerr << "Severity: LOW" << std::endl;
    std::cerr << "OpenGL Debug Message (" << id << "): " << message
              << std::endl;
  } else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
  }
}

class Timer {
 public:
  void Start() { start_time = std::chrono::high_resolution_clock::now(); }

  long long ElapsedMilliseconds() const {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);
    return duration.count();
  }

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

Timer timer;

int main(int, char**) {
  if (!glfwInit()) return 1;

  const char* glsl_version = "#version 460";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

  // Create window with graphics context
  GLFWwindow* window = glfwCreateWindow(
      window_width, window_height, "Conway's Game of Life", nullptr, nullptr);
  if (window == nullptr) return 1;

  glfwSetErrorCallback(glfw_error_callback);
  glfwSetCursorPosCallback(window, cursor_pos_callback);

  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);

  int version = gladLoadGL();
  if (version == 0) {
    std::cout << "Failed to initialize OpenGL context\n";
    return -1;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad;             // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Viewport
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(opengl_debug_callback, nullptr);

  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  int success;
  char info_log[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << info_log << std::endl;
  }

  unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << info_log << std::endl;
  }

  unsigned int shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << info_log << std::endl;
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  static const float vertices_data[] = {-1.0f, 1.0f,  0.0f, -1.0f, -1.0f, 0.0f,
                                        1.0f,  -1.0f, 0.0f, -1.0f, 1.0f,  0.0f,
                                        1.0f,  -1.0f, 0.0f, 1.0f,  1.0f,  0.0f};

  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_data), vertices_data,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  context.Init();
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static auto last = timer.ElapsedMilliseconds();
    static long long accumulate_time = 0;

    auto new_time = timer.ElapsedMilliseconds();
    if (context.running) {
      accumulate_time += new_time - last;
    }
    last = new_time;
    if (accumulate_time > context.time_interval) {
      accumulate_time -= context.time_interval;
      context.Update();
    }

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    {
      ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Once);
      ImGui::Begin("Panel", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
      ImGui::SliderInt("Time Interval(ms)", &context.time_interval, 10, 300);
      ImVec2 button_size{105, 0};

      if (ImGui::Button(context.running ? "Pause" : "Start", button_size)) {
        context.running = !context.running;
      }
      ImGui::SameLine();
      if (ImGui::Button("Clear", button_size)) {
        context.Clear();
      }
      ImGui::SeparatorText("How to Play");
      ImGui::BulletText("Use the left mouse button to add cells.");
      ImGui::BulletText("Use the right mouse button to remove cells.");
      ImGui::BulletText(
          "Use the buttons in the Patterns section to showcase some basic "
          "examples.");

      ImGui::SeparatorText("Patterns");
      // Still Lifes
      if (ImGui::Button("Block", button_size)) Block();
      ImGui::SameLine();
      if (ImGui::Button("BeeHive", button_size)) BeeHive();
      ImGui::SameLine();
      if (ImGui::Button("Loaf", button_size)) Loaf();
      ImGui::SameLine();
      if (ImGui::Button("Boat", button_size)) Boat();
      ImGui::SameLine();
      if (ImGui::Button("Tub", button_size)) Tub();
      // Oscillators
      if (ImGui::Button("Blinker", button_size)) Blinker();
      ImGui::SameLine();
      if (ImGui::Button("Toad", button_size)) Toad();
      ImGui::SameLine();
      if (ImGui::Button("Beacon", button_size)) Beacon();
      ImGui::SameLine();
      if (ImGui::Button("Pulsar", button_size)) Pulsar();
      ImGui::SameLine();
      if (ImGui::Button("Pentadecathlon", button_size)) Pentadecathlon();
      // Spaceships
      if (ImGui::Button("Glider", button_size)) Glider();
      ImGui::SameLine();
      if (ImGui::Button("LWSS", button_size)) LightWeightSpaceship();
      ImGui::SameLine();
      if (ImGui::Button("MWSS", button_size)) MiddleWeightSpaceship();
      ImGui::SameLine();
      if (ImGui::Button("HWSS", button_size)) HeavyWeightSpaceship();

      ImGui::End();
    }

    glUseProgram(shader_program);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, context.input_grid);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}