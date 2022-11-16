// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <stdio.h>
#include <vector>
#include <ctime>
void init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("init():" + std::string(SDL_GetError()));

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
    throw std::runtime_error("init(): SDL_image could not initialize! "
                             "SDL_image Error: " +
                             std::string(IMG_GetError()));
}


SDL_Surface* load_surface_for(const std::string& path, SDL_Surface* window_surface_ptr) {

  if (!window_surface_ptr){
    std::cout << "Error : window surface ptr is invalid" << std::endl;
    return (nullptr);
  }

  SDL_Surface* surf = SDL_ConvertSurface(IMG_Load(path.c_str()), window_surface_ptr->format, 0);
  if (!surf){
    std::cout << "Error during creation of surface." << std::endl;
    return (nullptr);
  }

  return (surf);
}

//Ctor            
animal::animal(const std::string &file_path, SDL_Surface *window_surface_ptr){
    
    image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    if (image_ptr_ == nullptr)
        throw std::runtime_error("animal::animal(): " + std::string(SDL_GetError()));
    
    // Set random position of the animal
    x_ = rand() % (frame_width - frame_boundary - image_ptr_->w) + frame_boundary;
    y_ = rand() % (frame_height - frame_boundary - image_ptr_->h) + frame_boundary;
};

void animal::draw() const
{
    if (window_surface_ptr_ == nullptr || image_ptr_ == nullptr){
      std::cout << "One of the following pointers is null : window_surface_ptr || image_ptr";
      return;
    }

    SDL_Rect frame;
    frame.x = x_;
    frame.y = y_;
    SDL_BlitSurface(image_ptr_, nullptr, window_surface_ptr_, &frame);
};

//CLASS SHEEP
sheep::sheep(const std::string& file_path, SDL_Surface* window_surface_ptr) : animal(file_path, window_surface_ptr){}

void sheep::move(){

  bool left_border = false;
  bool right_border = false;
  bool top_border = false;
  bool bot_border = false;

  //todo
}

sheep::~sheep(){
    SDL_FreeSurface(image_ptr_);
    std::cout << "A sheep was eaten" << std::endl;
};


//CLASS WOLF
wolf::wolf(const std::string& file_path, SDL_Surface* window_surface_ptr) : animal(file_path, window_surface_ptr){}

void wolf::move(){

  bool left_border = false;
  bool right_border = false;
  bool top_border = false;
  bool bot_border = false;

  //todo
}

wolf::~wolf() {
  SDL_FreeSurface(image_ptr_);
  std::cout << "A wolf has escaed" << std::endl;
}

// CLASS GROUND
ground::ground() : animals_list_{std::vector<std::shared_ptr<animal>>()}{}

void ground::add_animal(const std::shared_ptr<animal>& a) {
    animals_list_.push_back(a); 
}

void ground::update() const {
    for (const auto& a : animals_list_) {
      a->move();
      a->draw();
    }
}

//Getter
std::vector<std::shared_ptr<animal>> ground::getAnimals() const {
    return animals_list_;
}



