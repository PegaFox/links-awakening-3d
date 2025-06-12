#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

class ImguiManager {
  public:

    ImguiManager() {
      // imgui
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO(); (void)io;
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    
      ImGui::StyleColorsDark();
    
      ImGui_ImplGlfw_InitForOpenGL(SCREEN, true);
      ImGui_ImplOpenGL3_Init("#version 460 core");
    }

    void update() {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      if (ImGui::Begin("settings")) {
        if (ImGui::Button("Player")) playerWindow = true;
        if (ImGui::Button("Light")) sunlightWindow = true;
      } ImGui::End();

      if (playerWindow) {
        if (ImGui::Begin("Player", &playerWindow)) {
          ImGui::DragFloat3("Position", &player.cam.pos[0], 0.001f);
          ImGui::DragFloat("Gravity", &player.gravity, 0.001f, -1.0f, 1.0f);
          ImGui::DragFloat("Accelleration", &player.accelleration, 0.001f, 0.0f, 1.0f);
          ImGui::DragFloat("Deceleration", &player.deceleration, 0.001f, 0.0f, 1.0f);
          ImGui::DragFloat("Ground", &player.ground, 0.001f);
          ImGui::ListBox("Sword", (int*)&player.inventory.sword, swordOptions, 3);
          ImGui::ListBox("Shield", (int*)&player.inventory.shield, shieldOptions, 3);
          ImGui::DragInt("Bombs", &player.inventory.bombs, 0.2f, 0, 60);
          ImGui::Checkbox("Boomerang", &player.inventory.boomerang.equipped);
          ImGui::Checkbox("Bow", &player.inventory.bow);
          ImGui::DragInt("Arrows", &player.inventory.arrows, 0.2f, 0, 60);
          ImGui::Checkbox("Hookshot", &player.inventory.hookshot);
          ImGui::DragInt("Magic powder", &player.inventory.magicPowder, 0.2f, 0, 40);
          ImGui::Checkbox("Magic rod", &player.inventory.magicRod);
          if (ImGui::BeginListBox("Ocarina")) {
            ImGui::Checkbox("Ocarina", &player.inventory.ocarina.ocarina);
            ImGui::Checkbox("Ballad of the wind fish", &player.inventory.ocarina.balladOfTheWindFish);
            ImGui::Checkbox("Manbo's mambo", &player.inventory.ocarina.manbosMambo);
            ImGui::Checkbox("Song of soul", &player.inventory.ocarina.songOfSoul);
            ImGui::EndListBox();
          }
          ImGui::Checkbox("Pegasus boots", &player.inventory.pegasusBoots.equipped);
          ImGui::ListBox("Power Bracelet", (int*)&player.inventory.powerBracelet, braceletOptions, 3);
          ImGui::Checkbox("Roc's feather", &player.inventory.rocsFeather);
          ImGui::Checkbox("Shovel", &player.inventory.shovel);
          ImGui::Checkbox("Flippers", &player.inventory.flippers);
          ImGui::DragInt("Gold leaves", &player.inventory.goldLeaf, 0.05f, 0, 5);
          ImGui::Checkbox("Medicine", &player.inventory.medicine);
          ImGui::DragInt("Secret seashell", &player.inventory.secretSeashell, 0.1f, 0, 26);
          ImGui::Checkbox("Mushroom", &player.inventory.mushroom);
          ImGui::ListBox("Tunic", (int*)&player.inventory.tunic, tunicOptions, 3);
          ImGui::ListBox("Left hand", (int*)&player.inventory.leftHand, handOptions, 11);
          ImGui::ListBox("Right hand", (int*)&player.inventory.rightHand, handOptions, 11);
          ImGui::ListBox("Trading sequence item", (int*)&player.inventory.tradingItem, tradingSequenceOptions, 15);
        }
        ImGui::End();
      }

      if (sunlightWindow) {
        if (ImGui::Begin("Light", &sunlightWindow)) {
          //ImGui::DragFloat3("Material Ambient", &boulder.meshes[0].material.ambient[0], 0.001f, 0.0f, 1.0f);
          //ImGui::DragFloat3("Material Diffuse", &boulder.meshes[0].material.diffuse[0], 0.001f, 0.0f, 1.0f);
          //ImGui::DragFloat3("Material Specular", &boulder.meshes[0].material.specular[0], 0.001f, 0.0f, 1.0f);
          //ImGui::DragFloat("Material Shininess", &boulder.meshes[0].material.specWeight, 1.0f, 0.0f, 1000.0f);
          ImGui::DragFloat3("Light Direction", &sun.direction[0], 0.001f, -1.0f, 1.0f);
          ImGui::DragFloat3("Light Ambient", &sun.ambient[0], 0.001f, 0.0f, 1.0f);
          ImGui::DragFloat3("Light Diffuse", &sun.diffuse[0], 0.001f, 0.0f, 1.0f);
          ImGui::DragFloat3("Light Specular", &sun.specular[0], 0.001f, 0.0f, 1.0f);
        } ImGui::End();
      }

      ImGui::Render();
    }

    void draw() {
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

  private:

    bool playerWindow = false;
    bool sunlightWindow = false;
    const char* swordOptions[3] = {"None", "Fighter sword", "Seashell sword"};
    const char* shieldOptions[3] = {"None", "Fighter shield", "Mirror shield"};
    const char* braceletOptions[3] = {"None", "L1", "L2"};
    const char* tunicOptions[3] = {"Green", "Red mail", "Blue mail"};
    const char* handOptions[11] = {
      "None",
      "Sword",
      "Shield",
      "Bombs",
      "Boomerang",
      "Bow",
      "Hookshot",
      "Magic powder",
      "Magic rod",
      "Ocarina",
      "Shovel"
    };
    const char* tradingSequenceOptions[15] = {
      "None",
      "YoshiDoll",
      "Ribbon",
      "DogFood",
      "Bananas",
      "Stick",
      "Honeycomb",
      "Pineapple",
      "Hibiscus",
      "Letter",
      "Broom",
      "FishingHook",
      "MermaidNecklace",
      "MermaidScale",
      "MagnifyingLens"
    };
};