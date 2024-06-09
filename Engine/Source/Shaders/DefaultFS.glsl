#version 330 core

out vec4 FragColor;

in vec3 FragPos;      // Input fragment position from vertex shader
in vec3 Normal;       // Input normal vector from vertex shader
in vec2 TexCoord;     // Input normal vector from vertex shader
in vec3 VertexColor;  // Input vertex color from vertex shader

struct SCamera 
{
    vec3 Position;
};

struct SMaterial 
{
    float Shininess;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct SDirectionalLight
{
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct SPointLight 
{
    vec3 Position;
    
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    float Constant;
    float Linear;
    float Quadratic;
};

uniform sampler2D TexSampleDiffuse;
uniform sampler2D TexSampleNormal;
uniform SPointLight PointLights[128];
uniform SCamera Camera;
uniform bool bDrawTriangle = false;
SMaterial Material;
SDirectionalLight DirectionalLight;

uniform int PointLightCounter;

vec3 CalculateDirectionalLight(SDirectionalLight InDirectionalLight, vec3 Normal, vec3 ViewDirection)
{
    vec3 LightDirection = normalize(-InDirectionalLight.Direction);

    // Diffuse
    float DiffuseStrength = max(dot(Normal, LightDirection), 0.0);

    // Specular
    vec3 ReflectDirection = reflect(-LightDirection, Normal);
    float SpecularStrength = pow(max(dot(ViewDirection, ReflectDirection), 0.0), Material.Shininess);

    vec3 Ambient = InDirectionalLight.Ambient * Material.Ambient;
    vec3 Diffuse = InDirectionalLight.Diffuse * DiffuseStrength * Material.Diffuse;
    vec3 Specular = InDirectionalLight.Diffuse * SpecularStrength * Material.Specular;

    return (Ambient + Diffuse + Specular);
}

vec3 CalculatePointLight(SPointLight InPointLight, vec3 InNormal, vec3 ViewDirection) 
{
    vec3 LightDirection = normalize(InPointLight.Position - FragPos);

    // Diffuse
    float DiffuseStrength = max(dot(InNormal, LightDirection), 0.0);

    // Specular
    vec3 ReflectDirection = reflect(LightDirection, InNormal);
    float SpecularStrength = pow(max(dot(ViewDirection, ReflectDirection), 0.0), Material.Shininess);

    // Attenuation
    float distance    = length(InPointLight.Position - FragPos);
    float attenuation = 1.0 / (InPointLight.Constant + InPointLight.Linear * distance + InPointLight.Quadratic * (distance * distance));    

    vec3 Ambient = InPointLight.Ambient * Material.Ambient;
    vec3 Diffuse = InPointLight.Diffuse * DiffuseStrength * Material.Diffuse;
    vec3 Specular = InPointLight.Diffuse * SpecularStrength * Material.Specular;
    Ambient *= attenuation;
    Diffuse *= attenuation;
    Specular *= attenuation;

    return (Ambient + Diffuse + Specular);
}

// Gold Noise ©2015 dcerisano@standard3d.com
// - based on the Golden Ratio
// - uniform normalized distribution
// - fastest static noise generator function (also runs at low precision)
// - use with indicated fractional seeding method. 
float PHI = 1.61803398874989484820459;  // Φ = Golden Ratio   
float gold_noise(in vec2 xy, in float seed)
{
    return fract(tan(distance(xy*PHI, xy)*seed)*xy.x);
}


// Simple hash function to generate a predictable pseudo-random color
vec3 hash(int seed)
{
    float r = fract(sin(float(seed) * 12.9898) * 13758.5453);
    float g = fract(sin(float(seed) * 78.233) * 43758.5453);
    float b = fract(sin(float(seed) * 93.9898) * 9738.5453);
    return vec3(r, g, b);
}


void main() 
{
    // Initialize material properties
    Material.Shininess = 32.0;
    Material.Ambient = vec3(0.1, 0.1, 0.1); // Dark grey ambient color
    Material.Diffuse = vec3(0.8, 0.8, 1.0); // Red diffuse color
    Material.Specular = vec3(1.0, 1.0, 1.0); // White specular highlights

    // Initialize directional light properties
    DirectionalLight.Direction = normalize(vec3(-0.2, -1.0, -0.3)); // Light direction
    DirectionalLight.Ambient = vec3(0.2, 0.2, 0.2); // Ambient light color
    DirectionalLight.Diffuse = vec3(0.5, 0.5, 0.5); // Diffuse light color
    DirectionalLight.Specular = vec3(1.0, 1.0, 1.0); // Specular light color

    /* Properties */
    vec3 Normal = normalize(Normal);
    vec3 ViewDirection = normalize(Camera.Position - FragPos);

    vec3 Color = vec3(0);

    Color += CalculateDirectionalLight(DirectionalLight, Normal, ViewDirection);

    for (int Index = 0; Index < PointLightCounter + 1; Index++) 
    {
        Color += CalculatePointLight(PointLights[Index], Normal, ViewDirection);
    }

    vec4 TexColorDiffuse = texture(TexSampleDiffuse, TexCoord);
    vec4 TexColorNormal = texture(TexSampleNormal, TexCoord);
   
    
    if (bDrawTriangle) 
    {
        vec3 color = hash(gl_PrimitiveID); // Use the texture coordinates as the seed
        FragColor = vec4(color, 1.0); // Set the fragment color
    }
    else 
    {
        FragColor = vec4(Color, 1.0);
    }
}