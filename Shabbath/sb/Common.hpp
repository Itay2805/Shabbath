#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <vector>
#include <cstdint>
#include <iostream>
#include <string>
#include <memory>

#define SB_MODULE(mod) namespace sb { namespace mod {
#define SB_MODULE_END } }

#define SB_SUBMODULE(mod, sub) namespace sb { namespace mod { namespace sub {
#define SB_SUBMODULE_END } } }
