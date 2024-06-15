#version 330 core

in vec2 TexCoord;
in vec3 FragPos;
in mat3 TBN;

out vec4 FragColor;

uniform sampler2D albedo;
uniform sampler2D ao;
uniform sampler2D normalTex;
uniform sampler2D roughness;
uniform sampler2D metalness;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

const float PI = 3.14159265359;

// Function to calculate the Normal Distribution Function (NDF)
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

// Function to calculate the Fresnel Equation
vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

// Function to calculate the Geometry function
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

void main()
{
    // Sample textures
    vec3 albedo2 = texture(albedo, TexCoord).rgb;
    float ao2 = texture(ao, TexCoord).r; // Sample the red channel for AO
    vec3 normalTexSample = texture(normalTex, TexCoord).rgb;
    float roughness2 = texture(roughness, TexCoord).r;
    float metalness2 = texture(metalness, TexCoord).r;

    // Transform normal from [0,1] to [-1,1]
    vec3 normal = normalize(TBN * (normalTexSample * 2.0 - 1.0));

    // Lighting calculations
    vec3 N = normal;
    vec3 V = normalize(viewPos - FragPos);
    vec3 L = normalize(lightPos - FragPos);
    vec3 H = normalize(V + L);

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(N, H, roughness2);
    float G = GeometrySmith(N, V, L, roughness2);
    vec3 F0 = vec3(0.04); // Base reflectivity for non-metals
    F0 = mix(F0, albedo2, metalness2);
    vec3 F = FresnelSchlick(max(dot(H, V), 0.0), F0);

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metalness2;

    vec3 numerator = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // Avoid division by zero
    vec3 specular = numerator / denominator;

    vec3 Lo = (kD * albedo2 / PI + specular) * lightColor * max(dot(N, L), 0.0);

    // Calculate distance and attenuation
    float distance = length(lightPos - FragPos);
    float attenuation = 1.0 / (distance * distance);

    // Apply attenuation to the light contribution
    Lo *= attenuation;

    // Ambient lighting (including ambient occlusion)
    vec3 ambient = vec3(0.03) * albedo2 * ao2;

    vec3 finalColor = ambient + Lo;
    FragColor = vec4(finalColor, 1.0);
}
