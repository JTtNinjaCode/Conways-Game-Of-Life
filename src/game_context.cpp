#include "game_context.h"

const char *compute_shader_source = R"(
    #version 460
    const int width_grid_count = 1920 / 20;
    const int height_grid_count = 1080 / 20;

    // Define the width, height, and depth of a work group; multiplying these values gives the total number of invocations inside it
    layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

    layout(std430, binding = 0) buffer InputGrid {
        uint input_grid[width_grid_count * height_grid_count];
    };

    layout(std430, binding = 1) buffer OutputGrid {
        uint output_grid[width_grid_count * height_grid_count];
    };

    int index(int x, int y) {
        if (x < 0) x += width_grid_count;
        if (y < 0) y += height_grid_count;

        if (x >= width_grid_count) x -= width_grid_count;
        if (y >= height_grid_count) y -= height_grid_count;

        return y * width_grid_count + x;
    }

    void main() {
        int index_x = int(gl_WorkGroupID.x);
        int index_y = int(gl_WorkGroupID.y);

        int count = 0;
        if (input_grid[index(index_x - 1, index_y - 1)] == 1) {
            count += 1;
        }
        if (input_grid[index(index_x - 1, index_y + 0)] == 1) {
            count += 1;
        }
        if (input_grid[index(index_x - 1, index_y + 1)] == 1) {
            count += 1;
        }
        if (input_grid[index(index_x + 0, index_y - 1)] == 1) {
            count += 1;
        }
        if (input_grid[index(index_x + 0, index_y + 1)] == 1) {
            count += 1;
        }
        if (input_grid[index(index_x + 1, index_y - 1)] == 1) {
            count += 1;
        }
        if (input_grid[index(index_x + 1, index_y + 0)] == 1) {
            count += 1;
        }
        if (input_grid[index(index_x + 1, index_y + 1)] == 1) {
            count += 1;
        }

        if (count == 2 || count == 3) {
            if (input_grid[index(index_x, index_y)] == 0 && count == 3) {
                output_grid[index(index_x, index_y)] = 1;
            } else {
                output_grid[index(index_x, index_y)] = input_grid[index(index_x, index_y)];
            }
        } else {
            output_grid[index(index_x, index_y)] = 0;
        }
    }
)";

GameContext context;