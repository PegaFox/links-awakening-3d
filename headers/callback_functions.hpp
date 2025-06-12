void onResize(GLFWwindow* window, int width, int height) {
  glViewport(0.0f, 0.0f, width, height);
  projection = glm::perspective((float)M_PI_2, (float)width / (float)height, 0.1f, 100.0f);
}

void mouseMoved(GLFWwindow* window, double xpos, double ypos) {
  if (!mouseGrabbed) return;

  int width;
  int height;
  glfwGetWindowSize(window, &width, &height);

  glm::mat4 rot = glm::rotate(glm::mat4(1.0f), ((float)xpos - mPos.x)*0.002f, player.cam.up);
  rot = glm::rotate(rot, ((float)ypos - mPos.y)*0.002f, glm::cross(player.cam.facing, player.cam.up));

  glm::vec3 rotated = glm::vec4(player.cam.facing, 1.0f) * rot;
  if (rotated.y < 0.99f && rotated.y > -0.99f)
    player.cam.facing = rotated;
  mPos.x = xpos;
  mPos.y = ypos;
}

void mouseClicked(GLFWwindow* window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
    mouseGrabbed = !mouseGrabbed;
    if (mouseGrabbed) {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

      double mouseX;
      double mouseY;
      glfwGetCursorPos(window, &mouseX, &mouseY);

      mPos.x = mouseX;
      mPos.y = mouseY;
    } else {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
  }
}

#ifndef NDEBUG
void onDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param) {
  std::string src_str;
	switch (source) {
	  case GL_DEBUG_SOURCE_API:
      src_str = "API";
      break;
	  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      src_str = "WINDOW SYSTEM";
      break;
	  case GL_DEBUG_SOURCE_SHADER_COMPILER:
      src_str = "SHADER COMPILER";
      break;
	  case GL_DEBUG_SOURCE_THIRD_PARTY:
      src_str = "THIRD PARTY";
      break;
	  case GL_DEBUG_SOURCE_APPLICATION:
      src_str = "APPLICATION";
      break;
	  case GL_DEBUG_SOURCE_OTHER:
      src_str = "OTHER";
      break;
	}


  std::string type_str;
  switch (type) {
  	case GL_DEBUG_TYPE_ERROR:
      type_str = "ERROR";
      break;
  	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      type_str = "DEPRECATED_BEHAVIOR";
      break;
  	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      type_str = "UNDEFINED_BEHAVIOR";
      break;
  	case GL_DEBUG_TYPE_PORTABILITY:
      type_str = "PORTABILITY";
      break;
  	case GL_DEBUG_TYPE_PERFORMANCE:
      type_str = "PERFORMANCE";
      break;
  	case GL_DEBUG_TYPE_MARKER:
      type_str = "MARKER";
      break;
  	case GL_DEBUG_TYPE_OTHER:
      type_str = "OTHER";
      break;
  }


  std::string severity_str;
  switch (severity) {
  	case GL_DEBUG_SEVERITY_NOTIFICATION:
      severity_str = "NOTIFICATION";
      break;
  	case GL_DEBUG_SEVERITY_LOW:
      severity_str = "LOW";
      break;
  	case GL_DEBUG_SEVERITY_MEDIUM:
      severity_str = "MEDIUM";
      break;
  	case GL_DEBUG_SEVERITY_HIGH:
      severity_str = "HIGH";
      break;
  }

  std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
}
#endif