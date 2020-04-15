#version 430 core
/** Outputs */
layout(location = 0) out vec4 out_color;

/** Inputs */    
layout(location = 0) in vec3 normal;
layout(location = 1) in vec2 vs_texcoords;
layout(location = 2) in vec3 fragPos;

/** Texture sampler */
layout(binding = 0) uniform sampler2D texture_diffuse;
layout(location = 4) uniform vec3 lightPos;
layout(location = 5) uniform vec3 spotDir;
layout(location = 6) uniform float innerCutOff;
layout(location = 7) uniform float outerCutOff;
layout(location = 8) uniform vec3 viewPos;

void main()
{
  vec3 lightDir = normalize(lightPos - fragPos);
  
  float ambientStrength = 0.1;
  
  float theta = dot(lightDir, normalize(-spotDir));
  float epsilon   = innerCutOff - outerCutOff;
  float intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);    
         
  vec3 norm = normalize(normal);
  float diff = max(dot(norm, lightDir), 0.0);

  float specularStrength = 0.5;
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);  

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);

  diff *= intensity;
  specular *= intensity;

  out_color = vec4(texture(texture_diffuse, vs_texcoords).rgb * (ambientStrength + diff + specular), 1.0);
}