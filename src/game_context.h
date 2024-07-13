#pragma once
#include <glad/glad.h>

#include <array>
#include <iostream>
constexpr unsigned int window_width = 1920;
constexpr unsigned int window_height = 1080;
constexpr unsigned int tile_size = 20;
constexpr unsigned int tile_width_count = window_width / tile_size;
constexpr unsigned int tile_height_count = window_height / tile_size;

extern const char* compute_shader_source;

struct GameContext {
  void Init() {
    // init input_grid
    glCreateBuffers(1, &input_grid);
    glNamedBufferData(
        input_grid,
        sizeof(unsigned int) * (tile_width_count * tile_height_count), nullptr,
        GL_DYNAMIC_DRAW);

    // init output_grid
    glCreateBuffers(1, &output_grid);
    glNamedBufferData(
        output_grid,
        sizeof(unsigned int) * (tile_width_count * tile_height_count), nullptr,
        GL_DYNAMIC_DRAW);

    // init compute shader program
    int success;
    char info_log[512];
    unsigned int compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute_shader, 1, &compute_shader_source, NULL);
    glCompileShader(compute_shader);

    glGetShaderiv(compute_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(compute_shader, 512, NULL, info_log);
      std::cout << "ERROR::SHADER::COMPUTE::COMPILATION_FAILED\n"
                << info_log << std::endl;
    }

    compute_shader_program = glCreateProgram();
    glAttachShader(compute_shader_program, compute_shader);
    glLinkProgram(compute_shader_program);
    glGetProgramiv(compute_shader_program, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(compute_shader_program, 512, NULL, info_log);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                << info_log << std::endl;
    }
    glDeleteShader(compute_shader);
  }

  void SetCellState(int x, int y, bool state) {
    if (x >= 0 && x < tile_width_count && y >= 0 && y < tile_height_count) {
      unsigned int one = state ? 1 : 0;
      glNamedBufferSubData(input_grid,
                           sizeof(unsigned int) * (y * tile_width_count + x),
                           sizeof(unsigned int), &one);
    } else {
      std::cerr << "Out of Range\n";
    }
  }
  void Update() {
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, input_grid);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, output_grid);

    glUseProgram(compute_shader_program);
    glDispatchCompute(tile_width_count, tile_height_count,
                      1);  // 指定如何 Dispatch（分解給 tile_height_count *
                           // tile_width_count 個核心）並且立即開始執行
    // 確保所有計算完成
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    // 更新 grid_data
    std::swap(input_grid, output_grid);
  }

  void Clear() {
    glClearBufferSubData(
        GL_SHADER_STORAGE_BUFFER, GL_R32UI, 0,
        sizeof(unsigned int) * (tile_width_count * tile_height_count),
        GL_RED_INTEGER, GL_UNSIGNED_INT, nullptr);
  }

  unsigned int input_grid;   // SSBO
  unsigned int output_grid;  // SSBO
  unsigned int compute_shader_program;

  bool running = true;
  int time_interval = 300;
};

extern GameContext context;