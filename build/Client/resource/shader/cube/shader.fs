#version 330 core
out vec4 FragColor;

struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

struct LightParam {
    int lighttype;
    vec3 position;
    vec3 color;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;  
  
// 纹理
uniform sampler2D texture1;
// 摄像机坐标
uniform vec3 viewPos; 
// 光照参数
uniform LightParam lightParam[10];
// 光源数量
uniform int lightNum;

// 平行光
vec3 CalcDirLight(LightParam lightp)
{
    
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightp.color;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-lightp.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightp.color;
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightp.color;

    return (  ambient +  diffuse +   specular);
}

// 点光源
vec3 CalcPointLight(LightParam lightp)
{
   // 环境光
   float ambientStrength = 0.1;
   vec3 ambient = ambientStrength * lightp.color;

   // 漫反射
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightp.position - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightp.color;
   float distance = length(lightp.position - FragPos);
   float attenuation = 1.0 / (lightp.constant + lightp.linear * distance + lightp.quadratic * (distance * distance));
   // 镜面反射
   float specularStrength = 0.5;
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);  
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
   vec3 specular = specularStrength * spec * lightp.color;

   attenuation = 1.0;

   return (attenuation * ambient + attenuation * diffuse + attenuation * specular);
}

// 聚焦光源
vec3 CalcSpotLight(LightParam lightp)
{
    vec3 lightDir = normalize(lightp.position - FragPos);
    
    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-lightp.direction)); 
    
    if(theta > lightp.cutOff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
    {    
        // 环境光
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightp.color;
        
        // diffuse 
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightp.color; 
        
        // specular
        float specularStrength = 1.0;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 99);
        vec3 specular = specularStrength * spec * lightp.color; 
        
        float epsilon   = lightp.cutOff - lightp.outerCutOff;
        float intensity = clamp((theta - lightp.outerCutOff) / epsilon, 0.0, 1.0);    


        // attenuation
        float distance    = length(lightp.position - FragPos);
        float attenuation = 1.0 / (lightp.constant + lightp.linear * distance + lightp.quadratic * (distance * distance));    

   
        vec3 result = ambient + diffuse + specular;
        return result;
    }
    else 
    {
      return vec3(0.0);
    }

}


void main()
{
    vec3 result = vec3(0.0);
    for (int i = 0; i < lightNum; i++) {
        if (lightParam[i].lighttype == 1) {
           result += CalcPointLight(lightParam[i]);
        }
        else if (lightParam[i].lighttype == 2) {
           result += CalcSpotLight(lightParam[i]);
        }
        else if (lightParam[i].lighttype == 3) {
           result += CalcDirLight(lightParam[i]);
        } else {
           result = vec3(0.0);
        }
 
    }
    FragColor = vec4(result,1.0) * texture(texture1, TexCoord);
}