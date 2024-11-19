#pragma once

/// Returns a number between `min` (included) and `max` (excluded).
int random_int(int min, int max);

/// Returns a number between `min` and `max`.
float random_float(float min, float max);

bool true_with_probability(float probability_of_beeing_true);

/// A seed defines the sequence of random numbers that will be generated afterwards by `random_int()` and `random_float()`.
/// For example if you call `set_random_seed(0);` at the beginning of your `main` function, your program will always generate the same sequence of random numbers.
void set_random_seed(int seed);