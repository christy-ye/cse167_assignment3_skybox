#version 330 core

// This is a sample fragment shader.
out vec4 color;

uniform mat4 model;

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    bool dir;
};

uniform DirLight dirLight;

uniform struct Materials {
    
    vec3 amb;
    vec3 diff;
    vec3 spec;
    float shiny;
    
} materials;

in vec3 fragNormal;
//in vec3 fragVert;
in vec3 view_direction;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = (view_direction);
    
     //Phase 1: Directional lighting
    vec3 dirresult = CalcDirLight(dirLight, norm, viewDir);
    
    //color = vec4(1.0, 0.0, 0.0,1.0);
    color = vec4(dirresult, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightDir, normal);
    // Combine results
    vec3 ambient  = light.ambient  * materials.amb;
    vec3 diffuse  = light.diffuse  * max(dot(normal, lightDir), 0.0) * materials.diff;
    vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0.0), materials.shiny) * materials.spec;
    
    return (ambient + diffuse + specular);
}


