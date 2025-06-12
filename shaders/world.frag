#version 460 core
out vec4 FragColor;

struct Material
{
  //vec3 ambient;
  vec3 diffuse;
  //vec3 specular;
  //vec3 emission;
  //float emissiveIntensity;
  //float specWeight;
  //float refract;
  //float reflectiveness;
  //bool useAmbientTexture;
  //sampler2D ambientTexture;
  bool useDiffuseTexture;
  sampler2D diffuseTexture;
  //bool useSpecularColorTexture;
  //sampler2D specularColorTexture;
  //bool useSpecularHighlightTexture;
  //sampler2D specularHighlightTexture;
  //bool useBumpMap;
  //sampler2D bumpMap;
  //bool useNormalMap;
  //sampler2D normalMap;
  //bool useDisplacementMap;
  //sampler2D displacementMap;
  //bool useCubeMap;
  //sampler3D cubeMap;
};

uniform Material material;

in vec2 texCoord;

void main() {
  FragColor = vec4(material.diffuse, 1.0);

  if (material.useDiffuseTexture)
  {
    FragColor *= texture(material.diffuseTexture, texCoord);
  }
}
