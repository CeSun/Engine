#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in int BoneNum;
layout (location = 4) in int BoneId[4];
layout (location = 5) in float BoneWeight[4];

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out mat3 TBN;

uniform mat4 model;
uniform mat4 view_model;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 worldarea;
uniform mat4 TransForm[100];
uniform int TransFormNum;

out vec3 debug;

void main()
{
	/*
	vec3 finalpos = vec3( 0.0 );

	for ( int i = 0; i < BoneNum; i++ )
	{
		finalpos += vec3(TransForm[BoneId[i]] * vec4(aPos,1.0)) * BoneWeight[i];
	}
	*/

	mat4 BoneTransform = TransForm[BoneId[0]] * BoneWeight[0];
    BoneTransform += TransForm[BoneId[1]] * BoneWeight[1];
    BoneTransform += TransForm[BoneId[2]] * BoneWeight[2];
    BoneTransform += TransForm[BoneId[3]] * BoneWeight[3];
	vec4 PosL = BoneTransform * vec4(aPos, 1.0);
	debug = PosL.xyz;
    Normal = mat3(transpose(inverse(model))) * aNormal;  
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	gl_Position = worldarea * projection * view_model * PosL; // vec4(finalpos, 1.0f);
}