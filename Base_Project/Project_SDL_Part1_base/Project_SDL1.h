// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>

// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned frame_width = 1400; // Width of window in pixel
constexpr unsigned frame_height = 900; // Height of window in pixel
// Minimal distance of animals to the border
// of the screen
constexpr unsigned frame_boundary = 100;

// Helper function to initialize SDL
void init();

class animal {
private:
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                           // load_surface_for
  float x_;
  float y_;

public:
  animal(const std::string& file_path, SDL_Surface* window_surface_ptr);
  virtual ~animal() = default; 
  void draw() const; 
  virtual void move() = 0; 
};

// class sheep, derived from animal
class sheep : public animal {
public:
  sheep(const std::string& file_path, SDL_Surface* window_surface_ptr);
  ~sheep() override;
  void move() override;
};

// class wolf, derived from animal
class wolf : public animal {
public:
  wolf(const std::string& file_path, SDL_Surface* window_surface_ptr);
  ~wolf() override;
  void move() override;
};

// The "ground" on which all the animals live (like the std::vector
// in the zoo example).
class ground {
private:
  // Attention, NON-OWNING ptr, again to the screen
  SDL_Surface* window_surface_ptr_;

  // Some attribute to store all the wolves and sheep
  // here
  std::vector<std::shared_ptr<animal>> animals_list_;
  unsigned frame_ = 0;

public:
  //Ctor
  ground(); 
  //Dtor
  ~ground() = default; 

  // Add an animal
  void add_animal(const std::shared_ptr<animal>& animal); 

  // Refresh the screen, move animals and draw them
  void update() const ;
  //getter
  [[nodiscard]] std::vector<std::shared_ptr<animal>> getAnimals() const;
};

// The application class, which is in charge of generating the window
class application {
private:
  // The following are OWNING ptrs
  SDL_Window* window_ptr_;
  SDL_Surface* window_surface_ptr_;
  SDL_Event window_event_;

  // Other attributes here, for example an instance of ground

public:
  application(unsigned n_sheep, unsigned n_wolf); // Ctor
  ~application();                                 // dtor

  int loop(unsigned period); // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
};