//
// Created by tridoz on 22/05/26.
//

#include "../hpp/SliderSelector.hpp"

SliderSelector::SliderSelector() {
    this->textures.clear();
    this->rects.clear();
    this->slider_rect = {};
    this->slider_texture = nullptr;
    this->max_value = 0;
    this->min_value = 0;
    this->max_value_x = 0;
    this->min_value_x = 0;
    this->step = 0;
}
