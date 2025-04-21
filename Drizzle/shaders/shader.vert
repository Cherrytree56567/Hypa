#version 450
#extension GL_EXT_buffer_reference : require

layout (location = 0) out vec3 outColor;
layout (location = 1) out vec2 outUV;
layout (location = 2) out vec3 normal;
layout (location = 3) out vec3 worldPos;
layout (location = 4) flat out int isSky;

struct Vertex {

	vec3 position;
	float uv_x;
	vec3 normal;
	float uv_y;
	vec4 color;
}; 

layout(buffer_reference, std430) readonly buffer VertexBuffer { 
	Vertex vertices[];
};

//push constants block
layout( push_constant ) uniform constants
{	
	mat4 proj_matrix;
	mat4 view_matrix;
	mat4 model_matrix;
	int isSkyBox;
	VertexBuffer vertexBuffer;
} PushConstants;

void main() 
{	
	Vertex v = PushConstants.vertexBuffer.vertices[gl_VertexIndex];

	gl_Position = PushConstants.proj_matrix * PushConstants.view_matrix * PushConstants.model_matrix * vec4(v.position, 1.0);
	outColor = v.color.xyz;
	outUV.x = v.uv_x;
	outUV.y = v.uv_y;
	normal = v.normal;
	worldPos = v.position;
	isSky = PushConstants.isSkyBox;
}
