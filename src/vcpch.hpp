#pragma once

// stl 
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <array>
#include <vector>

// deps
#include <glad/glad.h>
#include <glm/common.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/ext.hpp>

#include <SFML/Window.hpp>

// proj
#include "utils/Shader.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Renderer.hpp"
#include "engine/Engine.hpp"