#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../opengl_utils/utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>

#define USE_PEGAFOX_UTILS_IMPLEMENTATION
#include <pegafox/utils.hpp>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include "headers/globals.hpp"

#include "headers/particles.hpp"

#include "headers/player.hpp"

DirectionalLight sun(glm::vec3(0.0f, -1.0f, 0.0f));

Player player;

bool mouseGrabbed = false;
glm::vec2 mPos;

#include "headers/callback_functions.hpp"

#include "headers/graphicsSetup.hpp"

#ifndef NDEBUG
#include "headers/imguiManager.hpp"
#endif

int main() {
  graphicsSetup();

  sun.ambient = glm::vec3(0.1f);
  sun.diffuse = glm::vec3(0.8f);
  sun.specular = glm::vec3(1.0f);
  
  pf::FPS fps;

  projection = glm::perspective((float)M_PI_2, 512.0f / 512.0f, 0.1f, 100.0f);

  player.init();

  Model world("../assets/models/tail_cave.obj");
  for (uint32_t t = 1; t < 4; t++)
  {
    glTextureParameteri(t, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTextureParameteri(t, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }

  Shader worldShader("../shaders/world.vert", "", "", "", "../shaders/world.frag", true);
  glUseProgram(worldShader());
  glUniformMatrix4fv(worldShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
  
  Model boulder("../assets/models/boulder.obj");
  Shader boulderShader("../shaders/boulder.vert", "", "", "", "../shaders/boulder.frag", true);
  glUseProgram(boulderShader());
  glUniformMatrix4fv(boulderShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);

  #ifndef NDEBUG
  ImguiManager imgui;
  #endif
for (uint32_t m = 0; m < world.meshes.size(); m++)
  {
    if (
      world.meshes[m].material.ambientTexture > 0 ||
      world.meshes[m].material.bumpMap > 0 ||
      world.meshes[m].material.cubeMap > 0 ||
      world.meshes[m].material.diffuseTexture > 0 ||
      world.meshes[m].material.displacementMap > 0 ||
      world.meshes[m].material.normalMap > 0 ||
      world.meshes[m].material.specularColorTexture > 0 ||
      world.meshes[m].material.specularHighlightTexture > 0)
    {
      std::cout << "texture on mesh number " << m << '\n';
    }
  }
  while (!glfwWindowShouldClose(SCREEN)) {
    #ifndef NDEBUG
    imgui.update();
    #endif

    glm::mat4 view(1.0f);
    view = glm::lookAt(player.cam.pos, player.cam.pos + player.cam.facing, player.cam.up);
    
    player.update();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // draw ground
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    glUseProgram(worldShader());
    glUniformMatrix4fv(worldShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(worldShader.getUniform("model"), 1, GL_FALSE, &model[0][0]);

    world.draw(worldShader);

    // draw rock
    model = glm::translate(glm::mat4(1.0f), glm::vec3(3.5f, -1.0f, 3.5f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    glUseProgram(boulderShader());

    glUniform3fv(boulderShader.getUniform("dirLight.facing"), 1, &sun.direction[0]);
    glUniform3fv(boulderShader.getUniform("dirLight.ambient"), 1, &sun.ambient[0]);
    glUniform3fv(boulderShader.getUniform("dirLight.diffuse"), 1, &sun.diffuse[0]);
    glUniform3fv(boulderShader.getUniform("dirLight.specular"), 1, &sun.specular[0]);

    glUniformMatrix4fv(boulderShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(boulderShader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
    glUniform3fv(boulderShader.getUniform("viewPos"), 1, &player.cam.pos[0]);
    boulder.draw(boulderShader);

    player.draw(view);

    #ifndef NDEBUG
    imgui.draw();
    #endif
    
    glfwSwapBuffers(SCREEN);
    glfwSetWindowTitle(SCREEN, std::to_string(int(fps.get_fps())).c_str());
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
