#version 450

layout(binding = 0) uniform UniformBufferObject 
{
    mat4 view;
    mat4 proj;
} ubo;

layout(push_constant) uniform constants
{
    vec4 colour;
    mat4 model;
} pushConstants;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec4 fragColour;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    gl_Position = ubo.proj * ubo.view * pushConstants.model * vec4(inPosition, 1.0);
    fragColour = pushConstants.colour;
    fragTexCoord = inTexCoord;
}