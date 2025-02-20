#version 410 core
out vec4 frag_colour;

in vec3 norm;
in vec3 frag_pos;
in vec2 texture_coord;

flat in int material_index;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    int diffuse_map;
    int specular_map;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 view_pos;

uniform DirectionalLight directional_light;
uniform PointLight point_lights[4];
uniform int num_point_lights;

uniform sampler2D textures[10];
uniform Material materials[10];

vec3 calculate_directional_light(DirectionalLight light, vec3 normal, vec3 view_direction) {
    Material material = materials[material_index];

    vec3 instance_ambient = material.ambient;
    vec3 instance_diffuse = material.diffuse;
    if (material.diffuse_map >= 0) {
        instance_ambient = vec3(texture(textures[material.diffuse_map], texture_coord));
        instance_diffuse = vec3(texture(textures[material.diffuse_map], texture_coord));
    }

    vec3 instance_specular = material.specular;
    if (material.specular_map >= 0) {
        instance_specular = vec3(texture(textures[material.specular_map], texture_coord));
    }

    vec3 light_direction = normalize(-light.direction);
    vec3 halfway_direction = normalize(light_direction + view_direction);

    // Calculate diffuse lighting
    float diff = max(dot(normal, light_direction), 0.0);


    float spec = 0.0;
    spec = pow(max(dot(halfway_direction, normal), 0.0), material.shininess);

    vec3 ambient = light.ambient * instance_ambient;
    vec3 diffuse = light.diffuse * diff * instance_diffuse;
    vec3 specular = light.specular * spec * instance_specular;

    // Combine result
    return (ambient + diffuse + specular);
}

vec3 calculate_point_light(PointLight light, vec3 normal, vec3 fragment_position, vec3 view_direction) {
    Material material = materials[material_index];

    vec3 instance_ambient = material.ambient;
    vec3 instance_diffuse = material.diffuse;
    if (material.diffuse_map >= 0) {
        instance_ambient = vec3(texture(textures[material.diffuse_map], texture_coord));
        instance_diffuse = vec3(texture(textures[material.diffuse_map], texture_coord));
    }

    vec3 instance_specular = material.specular;
    if (material.specular_map >= 0) {
        instance_specular = vec3(texture(textures[material.specular_map], texture_coord));
    }


    vec3 light_direction = normalize(light.position - fragment_position);
    vec3 halfway_direction = normalize(light_direction + view_direction);

    // diffuse shading
    float diff = max(dot(normal, light_direction), 0.0);

    float spec = 0.0;
    spec = pow(max(dot(normal, halfway_direction), 0.0), material.shininess);


    // attenuation
    float distance = length(light.position - fragment_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));


    vec3 ambient = light.ambient * instance_ambient * attenuation;
    vec3 diffuse = light.diffuse * diff * instance_diffuse * attenuation;
    vec3 specular = light.specular * spec * instance_specular * attenuation;

    return (ambient + diffuse + specular);
}

void main()
{

    vec3 normal = normalize(norm);
    vec3 view_dir = normalize(view_pos - frag_pos);

    vec3 result = calculate_directional_light(directional_light, normal, view_dir);

    for (int i = 0; i < num_point_lights; i++) {
        result += calculate_point_light(point_lights[i], normal, frag_pos, view_dir);
    }

    //vec3 result = (ambient + diffuse + specular);

    frag_colour = vec4(result, 1.0f);
}

