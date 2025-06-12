struct Inventory {
  enum class Sword : int {
    None,
    Fighter,
    Koholint
  } sword = Sword::None;
  enum class Shield : int {
    None,
    Fighter,
    Mirror
  } shield = Shield::None;
  int bombs = 0;
  bool bow = false;
  int arrows = 30;
  bool hookshot = false;
  int magicPowder = 0;
  bool magicRod = false;
  struct Ocarina {
    bool ocarina = false;
    bool balladOfTheWindFish = false;
    bool manbosMambo = false;
    bool songOfSoul = false;
  } ocarina;

  struct PegasusBoots {
    bool equipped = false;

    uint8_t timer = 0;
    ParticleGenerator particles;
  } pegasusBoots;

  struct Boomerang {
    bool equipped = false;

    float animationStage = 0.0f;

    Model boomerang;
    Shader boomerangShader;
  } boomerang;
  
  enum class PowerBracelet : int {
    None,
    L1,
    L2
  } powerBracelet = PowerBracelet::None;
  bool rocsFeather = false;
  bool shovel = false;
  bool flippers = false;
  int goldLeaf = 0;
  bool medicine = false;
  int secretSeashell = 0;
  bool mushroom = false;
  enum class Tunic : int {
    Green,
    Red,
    Blue
  } tunic = Tunic::Green;
  enum class TradingItem : int {
    None,
    YoshiDoll,
    Ribbon,
    DogFood,
    Bananas,
    Stick,
    Honeycomb,
    Pineapple,
    Hibiscus,
    Letter,
    Broom,
    FishingHook,
    MermaidNecklace,
    MermaidScale,
    MagnifyingLens
  } tradingItem = TradingItem::None;

  enum class Holdable {
    None,
    Sword,
    Shield,
    Bombs,
    Boomerang,
    Bow,
    Hookshot,
    MagicPowder,
    MagicRod,
    Ocarina,
    Shovel
  };

  Holdable slots[10];

  Holdable leftHand;
  Holdable rightHand;
};

class Player {
  public:
    #ifndef NDEBUG
    Inventory inventory;
    
    float gravity = 0.005f;
    float accelleration = 0.01f;
    float deceleration = 0.2f;
    float ground = -1.25f;
    #endif
    Camera cam;
    glm::vec3 posVel = glm::vec3(0.0f);

    Player() {
      cam.pos = glm::vec3(-9.5f, -0.25f, 0.5f);
    }

    void init() {
      inventory.pegasusBoots.particles.load(0, 30);
      
      inventory.boomerang.boomerang.load("../assets/models/boomerang.obj");
      inventory.boomerang.boomerangShader.load("../shaders/boomerang.vert", "", "", "", "../shaders/boomerang.frag", true);
      glUseProgram(inventory.boomerang.boomerangShader());
      glUniformMatrix4fv(inventory.boomerang.boomerangShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
    }

    void update() {
      move();

      updateMedicine();

      updateFeather();

      updateBoots();

      updateBoomerang();

      oldFacing = cam.facing;
    }

    void draw(const glm::mat4& view) {
      inventory.pegasusBoots.particles.draw(view);

      if (inventory.boomerang.equipped && (inventory.leftHand == Inventory::Holdable::Boomerang || inventory.rightHand == Inventory::Holdable::Boomerang)) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.25f-(inventory.leftHand == Inventory::Holdable::Boomerang)*0.5f, -0.15f + sin(inventory.boomerang.animationStage)*0.01f, -0.4f));
        model = glm::rotate(model, (float)-M_PI_2, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        glUseProgram(inventory.boomerang.boomerangShader());

        glUniformMatrix4fv(inventory.boomerang.boomerangShader.getUniform("model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(inventory.boomerang.boomerangShader.getUniform("view"), 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);
        inventory.boomerang.boomerang.draw(inventory.boomerang.boomerangShader);
      }
    }
  private:
    #ifdef NDEBUG
    Inventory inventory;

    float gravity = 0.005f;
    float accelleration = 0.01f;
    float deceleration = 0.2f;
    float ground = -1.0f;
    #endif

    bool touchingGround = true;

    glm::vec3 oldFacing;

    int maxHealth = 6;
    int health = 6;
    unsigned int rupees;

    void move() {

      if (cam.pos.y + posVel.y < ground+1.0f) {
        posVel.y = 0.0f;
        cam.pos.y = ground+1.0f;
        touchingGround = true;
      } else {
        touchingGround = false;
      }

      cam.pos += posVel;
      posVel.x *= 1.0f - deceleration;
      posVel.z *= 1.0f - deceleration;
      posVel.y -= gravity;

      if (glfwGetKey(SCREEN, GLFW_KEY_W) == GLFW_PRESS) {
        posVel += glm::normalize(cam.facing * glm::vec3(1.0f, 0.0f, 1.0f)) * accelleration;
      }
      if (glfwGetKey(SCREEN, GLFW_KEY_S) == GLFW_PRESS) {
        posVel -= glm::normalize(cam.facing * glm::vec3(1.0f, 0.0f, 1.0f)) * accelleration;
      }
      if (glfwGetKey(SCREEN, GLFW_KEY_A) == GLFW_PRESS) {
        posVel -= glm::normalize(glm::cross(cam.facing, cam.up) * glm::vec3(1.0f, 0.0f, 1.0f)) * accelleration;
      }
      if (glfwGetKey(SCREEN, GLFW_KEY_D) == GLFW_PRESS) {
        posVel += glm::normalize(glm::cross(cam.facing, cam.up) * glm::vec3(1.0f, 0.0f, 1.0f)) * accelleration;
      }
    }

    void updateBoomerang() {
      if (inventory.boomerang.equipped) {
        inventory.boomerang.animationStage += glm::length(glm::vec3(posVel.x, 0.0, posVel.z))*3.0f;
      }
    }

    void updateMedicine() {
      if (inventory.medicine && health <= 0) {
        inventory.medicine = 0;
        health = maxHealth;
      }
    }

    void updateFeather() {
      if (touchingGround && inventory.rocsFeather && glfwGetKey(SCREEN, GLFW_KEY_SPACE) == GLFW_PRESS) {
        posVel.y = 0.1f;
      }
    }

    void updateBoots() {
      if (inventory.pegasusBoots.equipped && glfwGetKey(SCREEN, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        if (inventory.pegasusBoots.timer == 60) {
          posVel += glm::normalize(cam.facing * glm::vec3(1.0f, 0.0f, 1.0f)) * 0.1f;

          if (glm::dot(glm::normalize(glm::vec2(cam.facing.x, cam.facing.z)), glm::normalize(glm::vec2(oldFacing.x, oldFacing.z))) < 0.9f) {
             inventory.pegasusBoots.timer = 0;
          }
        } else {
          inventory.pegasusBoots.timer++;
          accelleration = 0.0f;
          posVel.y += -0.02 + (inventory.pegasusBoots.timer%2)*0.04;
        }
      } else {
        inventory.pegasusBoots.timer = 0;

        accelleration = 0.005f;
      }

      if (inventory.pegasusBoots.timer != 0U && touchingGround) {
        inventory.pegasusBoots.particles.generating = true;
      } else {
        inventory.pegasusBoots.particles.generating = false;
      }

      inventory.pegasusBoots.particles.pos = cam.pos;
      inventory.pegasusBoots.particles.pos.y -= 1.0f;
      inventory.pegasusBoots.particles.update();
      if (inventory.pegasusBoots.particles.particles.size() > 0) {
        inventory.pegasusBoots.particles.particles.back().pos.x += inventory.pegasusBoots.particles.particles.back().velocity.x*10.0f;
        inventory.pegasusBoots.particles.particles.back().pos.z += inventory.pegasusBoots.particles.particles.back().velocity.z*10.0f;
      }
    }
};