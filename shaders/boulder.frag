#version 460 core
out vec4 FragColor;

struct Material {
  sampler2D normalMap;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};
uniform Material material;

struct DirLight {
  vec3 facing;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
uniform DirLight dirLight;

struct PointLight {    
  vec3 position;
    
  float constant;
  float linear;
  float quadratic;  

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};  
#define NR_POINT_LIGHTS 0
//uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform vec3 viewPos;

in vec3 fragPos;
in vec2 texCoord;
in mat3 TBN;

vec3 norm = normalize(TBN * (texture(material.normalMap, texCoord).rgb * 2.0 - 1.0));
vec3 viewDir = normalize(viewPos - fragPos);

vec3 calcDirLight(DirLight light);

//vec3 calcPointLight(PointLight light);

void main() {
  /*
  // falloff variables
  float distance;
  float attenuation = 1.0;

  // ambient
  vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, texCoord));

  // diffuse
  vec3 norm = normalize(normal);
  vec3 lightDir;
  if (light.pos.w > 0.0f) {
    lightDir = normalize(light.pos.xyz - fragPos);
    distance = length(light.pos.xyz - fragPos);
    attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
  } else {
    lightDir = normalize(-light.pos.xyz);
  }
  float diffuseValue = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * diffuseValue * vec3(texture(material.texture_diffuse1, texCoord));

  // specular
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, texCoord));

  // spotlight
  float theta = dot(lightDir, normalize(-light.facing));
  float epsilon = light.innerCutoff - light.outerCutoff;
  float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
  
  FragColor = vec4(ambient*attenuation + diffuse*intensity*attenuation + specular*intensity*attenuation, 1.0);
  */

  vec3 result = calcDirLight(dirLight);

  //for (int point = 0; point < NR_POINT_LIGHTS; point++) {
  //  result += calcPointLight(pointLights[point], norm, viewDir);
  //}

  FragColor = vec4(result, 1.0);
}

vec3 calcDirLight(DirLight light) {
  // ambient
  vec3 ambient = light.ambient * material.ambient/*vec3(texture(material.texture_diffuse1, texCoord)1.0, 1.0, 1.0)*/;

  // diffuse
  vec3 lightDir = normalize(-light.facing);

  float diffuseValue = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * diffuseValue * material.diffuse/*vec3(texture(material.texture_diffuse1, texCoord))*/;

  // specular
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess) * diffuseValue;

  vec3 specular = light.specular * spec * material.specular/*vec3(texture(material.texture_specular1, texCoord))*/;
  
  return (ambient + diffuse + specular);
}

/*vec3 calcPointLight(PointLight light) {
  // falloff variables
  float dis = length(light.pos - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * (dis * dis));

  // ambient
  vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, texCoord));

  // diffuse
  vec3 lightDir = normalize(light.pos - fragPos);
  float diffuseValue = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * diffuseValue * vec3(texture(material.texture_diffuse1, texCoord));

  // specular
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, texCoord));
  
  return ambient*attenuation + diffuse*attenuation + specular*attenuation;
}*/