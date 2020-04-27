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
in vec3 FragPos;  
in mat3 TBN;


in vec3 Normal;  
  
// ����
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
// ���������
uniform vec3 viewPos; 
// ���ղ���
uniform LightParam lightParam[10];
// ��Դ����
uniform int lightNum;

// ƽ�й�
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

// ���Դ
vec3 CalcPointLight(LightParam lightp)
{
   // ������
   float ambientStrength = 0.1;
   vec3 ambient = ambientStrength * lightp.color;

   // ������
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightp.position - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightp.color;
   float distance = length(lightp.position - FragPos);
   float attenuation = 1.0 / (lightp.constant + lightp.linear * distance + lightp.quadratic * (distance * distance));
   // ���淴��
   float specularStrength = 0.5;
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);  
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
   vec3 specular = specularStrength * spec * lightp.color;

   attenuation = 1.0;

   return (attenuation * ambient + attenuation * diffuse + attenuation * specular);
}

// �۽���Դ
vec3 CalcSpotLight(LightParam lightp)
{
    vec3 lightDir = normalize(lightp.position - FragPos);
    
    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-lightp.direction)); 
    
    if(theta > lightp.cutOff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
    {    
       
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

   
        vec3 result = diffuse + specular;
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
    FragColor = vec4(result,1.0) * texture(texture_diffuse1, TexCoord);
}