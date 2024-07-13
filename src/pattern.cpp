#include "pattern.h"

#include "game_context.h"

constexpr unsigned int middle_x = tile_width_count / 2;
constexpr unsigned int middle_y = tile_height_count / 2;

void Block() {
  context.Clear();
  context.SetCellState(middle_x + 0, middle_y + 0, true);
  context.SetCellState(middle_x + 0, middle_y + 1, true);
  context.SetCellState(middle_x + 1, middle_y + 0, true);
  context.SetCellState(middle_x + 1, middle_y + 1, true);
}

void BeeHive() {
  context.Clear();
  context.SetCellState(middle_x + 0, middle_y - 1, true);
  context.SetCellState(middle_x + 0, middle_y + 1, true);
  context.SetCellState(middle_x + 1, middle_y - 1, true);
  context.SetCellState(middle_x + 1, middle_y + 1, true);
  context.SetCellState(middle_x - 1, middle_y + 0, true);
  context.SetCellState(middle_x + 2, middle_y + 0, true);
}

void Loaf() {
  context.Clear();
  context.SetCellState(middle_x + 0, middle_y - 2, true);
  context.SetCellState(middle_x - 1, middle_y - 1, true);
  context.SetCellState(middle_x + 1, middle_y - 1, true);
  context.SetCellState(middle_x - 2, middle_y - 0, true);
  context.SetCellState(middle_x + 1, middle_y - 0, true);
  context.SetCellState(middle_x - 1, middle_y + 1, true);
  context.SetCellState(middle_x + 0, middle_y + 1, true);
}

void Boat() {
  context.Clear();
  context.SetCellState(middle_x + 0, middle_y + 1, true);
  context.SetCellState(middle_x + 0, middle_y - 1, true);
  context.SetCellState(middle_x + 1, middle_y + 0, true);
  context.SetCellState(middle_x - 1, middle_y + 0, true);
  context.SetCellState(middle_x - 1, middle_y + 1, true);
}

void Tub() {
  context.Clear();
  context.SetCellState(middle_x + 0, middle_y + 1, true);
  context.SetCellState(middle_x + 0, middle_y - 1, true);
  context.SetCellState(middle_x + 1, middle_y + 0, true);
  context.SetCellState(middle_x - 1, middle_y + 0, true);
}

void Blinker() {
  context.Clear();
  context.SetCellState(middle_x + 0, middle_y + 1, true);
  context.SetCellState(middle_x + 0, middle_y + 0, true);
  context.SetCellState(middle_x + 0, middle_y - 1, true);
}

void Toad() {
  context.Clear();
  context.SetCellState(middle_x - 2, middle_y - 1, true);
  context.SetCellState(middle_x - 1, middle_y - 1, true);
  context.SetCellState(middle_x - 0, middle_y - 1, true);
  context.SetCellState(middle_x - 1, middle_y + 0, true);
  context.SetCellState(middle_x + 0, middle_y + 0, true);
  context.SetCellState(middle_x + 1, middle_y + 0, true);
}

void Beacon() {
  context.Clear();
  context.SetCellState(middle_x - 1, middle_y - 1, true);
  context.SetCellState(middle_x - 1, middle_y - 2, true);
  context.SetCellState(middle_x - 2, middle_y - 1, true);
  context.SetCellState(middle_x - 2, middle_y - 2, true);
  context.SetCellState(middle_x + 0, middle_y + 0, true);
  context.SetCellState(middle_x + 0, middle_y + 1, true);
  context.SetCellState(middle_x + 1, middle_y + 0, true);
  context.SetCellState(middle_x + 1, middle_y + 1, true);
}

void Pulsar() {
  context.Clear();
  context.SetCellState(middle_x + 2, middle_y + 1, true);
  context.SetCellState(middle_x + 3, middle_y + 1, true);
  context.SetCellState(middle_x + 1, middle_y + 2, true);
  context.SetCellState(middle_x + 3, middle_y + 2, true);
  context.SetCellState(middle_x + 5, middle_y + 2, true);
  context.SetCellState(middle_x + 1, middle_y + 3, true);
  context.SetCellState(middle_x + 2, middle_y + 3, true);
  context.SetCellState(middle_x + 5, middle_y + 3, true);
  context.SetCellState(middle_x + 6, middle_y + 3, true);
  context.SetCellState(middle_x + 7, middle_y + 3, true);
  context.SetCellState(middle_x + 2, middle_y + 5, true);
  context.SetCellState(middle_x + 3, middle_y + 5, true);
  context.SetCellState(middle_x + 3, middle_y + 6, true);
  context.SetCellState(middle_x + 3, middle_y + 7, true);

  context.SetCellState(middle_x - 2, middle_y + 1, true);
  context.SetCellState(middle_x - 3, middle_y + 1, true);
  context.SetCellState(middle_x - 1, middle_y + 2, true);
  context.SetCellState(middle_x - 3, middle_y + 2, true);
  context.SetCellState(middle_x - 5, middle_y + 2, true);
  context.SetCellState(middle_x - 1, middle_y + 3, true);
  context.SetCellState(middle_x - 2, middle_y + 3, true);
  context.SetCellState(middle_x - 5, middle_y + 3, true);
  context.SetCellState(middle_x - 6, middle_y + 3, true);
  context.SetCellState(middle_x - 7, middle_y + 3, true);
  context.SetCellState(middle_x - 2, middle_y + 5, true);
  context.SetCellState(middle_x - 3, middle_y + 5, true);
  context.SetCellState(middle_x - 3, middle_y + 6, true);
  context.SetCellState(middle_x - 3, middle_y + 7, true);

  context.SetCellState(middle_x + 2, middle_y - 1, true);
  context.SetCellState(middle_x + 3, middle_y - 1, true);
  context.SetCellState(middle_x + 1, middle_y - 2, true);
  context.SetCellState(middle_x + 3, middle_y - 2, true);
  context.SetCellState(middle_x + 5, middle_y - 2, true);
  context.SetCellState(middle_x + 1, middle_y - 3, true);
  context.SetCellState(middle_x + 2, middle_y - 3, true);
  context.SetCellState(middle_x + 5, middle_y - 3, true);
  context.SetCellState(middle_x + 6, middle_y - 3, true);
  context.SetCellState(middle_x + 7, middle_y - 3, true);
  context.SetCellState(middle_x + 2, middle_y - 5, true);
  context.SetCellState(middle_x + 3, middle_y - 5, true);
  context.SetCellState(middle_x + 3, middle_y - 6, true);
  context.SetCellState(middle_x + 3, middle_y - 7, true);

  context.SetCellState(middle_x - 2, middle_y - 1, true);
  context.SetCellState(middle_x - 3, middle_y - 1, true);
  context.SetCellState(middle_x - 1, middle_y - 2, true);
  context.SetCellState(middle_x - 3, middle_y - 2, true);
  context.SetCellState(middle_x - 5, middle_y - 2, true);
  context.SetCellState(middle_x - 1, middle_y - 3, true);
  context.SetCellState(middle_x - 2, middle_y - 3, true);
  context.SetCellState(middle_x - 5, middle_y - 3, true);
  context.SetCellState(middle_x - 6, middle_y - 3, true);
  context.SetCellState(middle_x - 7, middle_y - 3, true);
  context.SetCellState(middle_x - 2, middle_y - 5, true);
  context.SetCellState(middle_x - 3, middle_y - 5, true);
  context.SetCellState(middle_x - 3, middle_y - 6, true);
  context.SetCellState(middle_x - 3, middle_y - 7, true);
}

void Pentadecathlon() {
  context.Clear();
  context.SetCellState(middle_x - 1, middle_y + 0, true);
  context.SetCellState(middle_x - 0, middle_y + 0, true);
  context.SetCellState(middle_x + 1, middle_y + 0, true);
  context.SetCellState(middle_x - 1, middle_y + 2, true);
  context.SetCellState(middle_x - 0, middle_y + 2, true);
  context.SetCellState(middle_x + 1, middle_y + 2, true);
  context.SetCellState(middle_x - 0, middle_y + 3, true);
  context.SetCellState(middle_x - 0, middle_y + 4, true);
  context.SetCellState(middle_x - 1, middle_y + 5, true);
  context.SetCellState(middle_x - 0, middle_y + 5, true);
  context.SetCellState(middle_x + 1, middle_y + 5, true);

  context.SetCellState(middle_x - 1, middle_y - 1, true);
  context.SetCellState(middle_x - 0, middle_y - 1, true);
  context.SetCellState(middle_x + 1, middle_y - 1, true);
  context.SetCellState(middle_x - 1, middle_y - 3, true);
  context.SetCellState(middle_x - 0, middle_y - 3, true);
  context.SetCellState(middle_x + 1, middle_y - 3, true);
  context.SetCellState(middle_x - 0, middle_y - 4, true);
  context.SetCellState(middle_x - 0, middle_y - 5, true);
  context.SetCellState(middle_x - 1, middle_y - 6, true);
  context.SetCellState(middle_x - 0, middle_y - 6, true);
  context.SetCellState(middle_x + 1, middle_y - 6, true);
}

void Glider() {
  context.Clear();
  context.SetCellState(middle_x - 1, middle_y - 1, true);
  context.SetCellState(middle_x + 0, middle_y - 1, true);
  context.SetCellState(middle_x + 1, middle_y - 1, true);
  context.SetCellState(middle_x + 1, middle_y + 0, true);
  context.SetCellState(middle_x + 0, middle_y + 1, true);
}

void LightWeightSpaceship() {
  context.Clear();
  context.SetCellState(middle_x - 1, middle_y - 2, true);
  context.SetCellState(middle_x + 0, middle_y - 2, true);
  context.SetCellState(middle_x + 1, middle_y - 2, true);
  context.SetCellState(middle_x + 2, middle_y - 2, true);
  context.SetCellState(middle_x - 2, middle_y - 1, true);
  context.SetCellState(middle_x + 2, middle_y - 1, true);
  context.SetCellState(middle_x + 2, middle_y + 0, true);
  context.SetCellState(middle_x - 2, middle_y + 1, true);
  context.SetCellState(middle_x + 1, middle_y + 1, true);
}

void MiddleWeightSpaceship() {
  context.Clear();
  context.SetCellState(middle_x - 2, middle_y - 2, true);
  context.SetCellState(middle_x - 1, middle_y - 2, true);
  context.SetCellState(middle_x + 0, middle_y - 2, true);
  context.SetCellState(middle_x + 1, middle_y - 2, true);
  context.SetCellState(middle_x + 2, middle_y - 2, true);
  context.SetCellState(middle_x - 3, middle_y - 1, true);
  context.SetCellState(middle_x + 2, middle_y - 1, true);
  context.SetCellState(middle_x + 2, middle_y - 0, true);
  context.SetCellState(middle_x - 3, middle_y + 1, true);
  context.SetCellState(middle_x + 1, middle_y + 1, true);
  context.SetCellState(middle_x - 1, middle_y + 2, true);
}

void HeavyWeightSpaceship() {
  context.Clear();
  context.SetCellState(middle_x - 2, middle_y - 2, true);
  context.SetCellState(middle_x - 1, middle_y - 2, true);
  context.SetCellState(middle_x - 0, middle_y - 2, true);
  context.SetCellState(middle_x + 1, middle_y - 2, true);
  context.SetCellState(middle_x + 2, middle_y - 2, true);
  context.SetCellState(middle_x + 3, middle_y - 2, true);
  context.SetCellState(middle_x - 3, middle_y - 1, true);
  context.SetCellState(middle_x + 3, middle_y - 1, true);
  context.SetCellState(middle_x + 3, middle_y - 0, true);
  context.SetCellState(middle_x - 3, middle_y + 1, true);
  context.SetCellState(middle_x + 2, middle_y + 1, true);
  context.SetCellState(middle_x - 1, middle_y + 2, true);
  context.SetCellState(middle_x + 0, middle_y + 2, true);
}