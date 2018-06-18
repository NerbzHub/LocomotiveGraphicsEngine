#include "Mesh.h"
#include "gl_core_4_5.h"
#include <vector>


Mesh::~Mesh()
{

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialise(unsigned int vertexCount,
	const Vertex* vertices,
	unsigned int indexCount /* = 0 */,
	unsigned int* indices /* = nullptr*/)
{
	assert(vao == 0);

	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex),
		vertices, GL_STATIC_DRAW);

	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), 0);

	// enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE,
		sizeof(Vertex), (void*)16);

	// enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)32);

	// bind indices if there are any
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);
		// bind vertex buffer

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		// fill vertex buffer

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		triCount = indexCount / 3;
	}
	else
		triCount = vertexCount / 3;

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::initialiseQuad()
{
	// check that the mesh is not initialized already
	assert(vao == 0);

	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// define 6 vertices for 2 triangles
	Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };

	// define tex coords
	vertices[0].texCoord = { 0, 1 }; // bottom left
	vertices[1].texCoord = { 1, 1 }; // bottom right
	vertices[2].texCoord = { 0, 0 }; // top left
	vertices[3].texCoord = { 0, 0 }; // top left
	vertices[4].texCoord = { 1, 1 }; // bottom right
	vertices[5].texCoord = { 1, 0 }; // top right


	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex),
		vertices, GL_STATIC_DRAW);

	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), 0);

	// enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE,
		sizeof(Vertex), (void*)16);

	// enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)32);

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// quad has 2 triangles
	triCount = 2;
}

//void Mesh::initialiseCircle(const glm::vec3 & center, float radius, unsigned int segments)
//{
//	// ensure that I have put in a transform.
//	//assert(transform != nullptr);
//
//	assert(&center != nullptr);
//	assert(radius != 0);
//	assert(segments != 0);
//
//
//	float segmentSize = (2 * glm::pi<float>()) / segments;
//	unsigned int vertexCount = segments + 1;
//	std::vector<Vertex> vertVec;
//	Vertex midPoint;
//	midPoint.position = glm::vec4(center.x, center.y, 0.0f, 0.0f);
//	vertVec.push_back(midPoint);
//
//	float angle = 0;
//	for (int i = 0;i < segmentSize; angle += segmentSize, i++)
//	{
//		glm::vec4 segmentDirection = glm::vec4(sinf(i * segmentSize), 0, cosf(i * segmentSize), 0);
//
//		Vertex vert;
//		vert.position = glm::vec4(center, 1) + (segmentDirection * radius);
//		vertVec.push_back(vert);
//
//
//		// calculates the two outer verts
//		//glm::vec2 outerVec1(sinf(i * segmentSize) * radius, cosf(i * segmentSize) * radius);
//		//glm::vec2 outerVec2(sinf((i + 1) * segmentSize) * radius, cosf((i + 1) * segmentSize) * radius);
//		//
//		//// if transform is not nullptr
//		//if (transform != nullptr)
//		//{
//		//	
//		//	outerVec1 = glm::vec2((*transform * glm::vec4(outerVec1, 0, 0)));
//		//	outerVec2 = glm::vec2((*transform * glm::vec4(outerVec2, 0, 0)));
//		//}
//		//
//		//// assigns the vertices into the vector.
//		//vertVec[i].position = glm::vec4(outerVec1.x, outerVec1.y, 0.0f, 0.0f);
//		//vertVec[i+1].position = glm::vec4(outerVec2.x, outerVec2.y, 0.0f, 0.0f);
//	}
//
//	// todo: figure out how to get the vertices into an array so that i can use them in the index buffer.
//
//	// use a vector.data for the size of the indices
//
//	std::vector<unsigned int> indices;
//
//	for (unsigned int i = 1; i < segments; i++)
//	{
//		// 012, 023, 034, 045, 056.
//		indices.push_back(0);
//		indices.push_back(i);
//		indices.push_back(i + 1);
//	}
//
//	initialise(vertexCount, vertVec.data(), segments, indices.data());
//
//}

//void Mesh::initialiseCylinder(glm::vec3 & center, float radius, float height, unsigned int segments, glm::mat4* transform)
//{
//	glm::vec3 tmpCenter = transform != nullptr ? glm::vec3((*transform)[3]) + center : center;
//
//
//}

void Mesh::draw()
{
	glBindVertexArray(vao);

	// using indices or just vertices?
	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount,
			GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
}