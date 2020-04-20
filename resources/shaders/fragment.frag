#version 430 core
/** Outputs */
layout(location = 0) out vec4 out_color;

struct SpotLight {
  vec3 position;
  vec3 direction;
  float cutOff;
  float outerCutOff;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

/** Inputs */    
layout(location = 0) in vec3 normal;
layout(location = 1) in vec2 vs_texcoords;
layout(location = 2) in vec3 fragPos;

/** Texture sampler */
layout(binding = 0) uniform sampler2D texture_diffuse;
uniform SpotLight spotLight;

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
  vec3 norm = normalize(normal);
  vec3 viewDir = normalize(-fragPos);

  vec3 result = CalculateSpotLight(spotLight, norm, fragPos, viewDir);

  out_color = vec4(result, 1.0);
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  vec3 lightDir = normalize(light.position - fragPos);
  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
  // attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
  // spotlight intensity
  float theta = dot(lightDir, normalize(-light.direction));
  float epsilon = light.cutOff - light.outerCutOff;
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

  vec3 ambient = light.ambient * texture(texture_diffuse, vs_texcoords).rgb;
  vec3 diffuse = light.diffuse * diff * texture(texture_diffuse, vs_texcoords).rgb;
  vec3 specular = light.specular * spec * texture(texture_diffuse, vs_texcoords).rgb;
  ambient *= attenuation * intensity;
  diffuse *= attenuation * intensity;
  specular *= attenuation * intensity;
  return (ambient + diffuse + specular);
}