class Particle {
  public:

    uint32_t age;
    glm::vec3 pos;
    glm::vec3 velocity;

    Particle(Shader* shader, glm::vec3 pos, glm::vec3 velocity, uint32_t lifespan) : shader{shader}, pos{pos}, velocity{velocity}, age{lifespan} {

    }

    void update() {
      velocity.y -= 0.01f;
      velocity *= 0.99f;

      if (pos.y + velocity.y < -1.0f) {
        velocity = glm::vec3(0.0f);
      }

      pos += velocity;

      age--;
    }

  private:

    Shader* shader;
};

class ParticleGenerator {
  public:

    std::vector<Particle> particles;

    glm::vec3 pos;
    bool generating = true;

    ParticleGenerator() {
      speed = 0;
      lifespan = 0;
    }

    ParticleGenerator(uint32_t speed, uint32_t lifespan) {
      load(speed, lifespan);
    }

    void load(uint32_t speed, uint32_t lifespan) {
      this->speed = speed;
      this->lifespan = lifespan;

      particleShader.load(vertexShaderCode, "", "", "", fragmentShaderCode, false);

      glGenBuffers(1, &VBO);
      glGenVertexArrays(1, &VAO);

      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBindVertexArray(VAO);

      glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float) * (lifespan / (speed+1)), nullptr, GL_DYNAMIC_DRAW);
      
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4*sizeof(float), nullptr);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(3*sizeof(float)));
      glEnableVertexAttribArray(1);
    }

    void update() {

      if (timer == 0) {
        if (generating) {
          glm::vec3 vel = glm::normalize(glm::vec3(rand() - (RAND_MAX*0.5f), rand(), rand() - (RAND_MAX*0.5f))) * 0.1f;
          particles.push_back(Particle(&particleShader, pos, vel, lifespan));
        }
        timer = speed;
      } else {
        timer--;
      }

      for (std::vector<Particle>::iterator p = particles.begin(); p < particles.end(); p++) {
        p->update();

        if (p->age == 0U) {
          particles.erase(p);
        }
      }
    }

    void draw(const glm::mat4& view) {
      float particleInfo[particles.size() * 4];

      for (uint p = 0; p < particles.size(); p++) {
        particleInfo[p*4] = particles[p].pos.x;
        particleInfo[p*4 + 1] = particles[p].pos.y;
        particleInfo[p*4 + 2] = particles[p].pos.z;

        particleInfo[p*4 + 3] = particles[p].age/2.0f;
      }

      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferSubData(GL_ARRAY_BUFFER, 0, particles.size() * 4 * sizeof(float), particleInfo);

      glUseProgram(particleShader());
      // glGetUniformLocation returns -1 for both of these
      glUniformMatrix4fv(particleShader.getUniform("projection"), 1, GL_FALSE, &projection[0][0]);
      glUniformMatrix4fv(particleShader.getUniform("view"), 1, GL_FALSE, &view[0][0]);
      glBindVertexArray(VAO);
      glDrawArrays(GL_POINTS, 0, particles.size());
    }
  private:

    uint32_t speed;
    uint32_t timer = 0;

    uint32_t lifespan;

    std::string vertexShaderCode = "\
      #version 460 core \n\
      layout (location = 0) in vec3 aPos;\
      layout (location = 1) in float aStrength;\
      \
      uniform mat4 view;\
      uniform mat4 projection;\
      \
      void main() {\
        vec4 v = view * vec4(aPos, 1.0);\
        \
        gl_PointSize = aStrength / (-v.z);\
        gl_Position = projection * v;\
      }\
    ";

    std::string fragmentShaderCode = "\
      #version 460 core \n\
      out vec4 FragColor;\
      \
      void main() {\
        FragColor = vec4(0.795, 0.637, 0.338, 1.0);\
        //FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n\
      }\
    ";

    Shader particleShader;

    uint32_t VBO;
    uint32_t VAO;
};