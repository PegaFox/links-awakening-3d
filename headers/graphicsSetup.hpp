void graphicsSetup() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  SCREEN = glfwCreateWindow(512, 512, "Zelda", NULL, NULL);

  if (SCREEN == NULL) {
    //std::cerr << "Window load failed\n";
    //return -1;
    throw "Window load failed";
  }
  glfwMakeContextCurrent(SCREEN);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    //std::cerr << "Failed to initialize GLAD\n";
    //return -2;
    throw "Failed to initialize GLAD";
  }

  glViewport(0.0f, 0.0f, 512.0f, 512.0f);
  glClearColor(0.2f, 0.6f, 1.0f, 1.0f);
  
  #ifndef NDEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(onDebugMessage, nullptr);
  #endif

  glfwSetFramebufferSizeCallback(SCREEN, onResize);
  glfwSetCursorPosCallback(SCREEN, mouseMoved);
  glfwSetMouseButtonCallback(SCREEN, mouseClicked);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_MULTISAMPLE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glEnable(GL_FRAMEBUFFER_SRGB);
}